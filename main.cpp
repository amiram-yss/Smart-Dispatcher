#include <iostream>
#include "BoundedQueue.h"
#include "UnboundedQueue.h"
#include "ConfigurationHandler.h"
#include "Report.h"
#include "ReporterHandler.h"
#include <chrono>
#include <thread>


//Collections
//static std::vector<ConfigurationHandler::ConfigurationItem> *configs;
static std::vector<ReporterHandler> reporterQueues;
static std::vector<pthread_t> reporterThreads;
static pthread_t dispatcher_thread;
//Dispatcher dispatcher;
// TODO check how to do this non static
//static UnboundedQueue<std::string> dispatcher;
static std::vector<UnboundedQueue<std::string>> typeSortedQueueCollection;
static ReportType reportTypes[] = {SPORTS, NEWS, WEATHER};
static std::vector<pthread_t> coEditorThreadCollection;
int screenBufferSize;
static BoundedQueue<std::string> screenBuffer;
static pthread_t screenManagerThread;

bool init() {
    srand(time(NULL));
    std::vector<ConfigurationHandler::ConfigurationItem> *configs = ConfigurationHandler::ReadConfig("config_s.txt", &screenBufferSize);
    if (configs == nullptr)
        return false;
    for (auto conf: *configs) {
        reporterQueues.push_back(ReporterHandler(conf));
    }
    reporterThreads = std::vector<pthread_t>();
    reporterThreads.resize(reporterQueues.size());
    //dispatcher = UnboundedQueue<std::string>();
    typeSortedQueueCollection.resize(sizeof (ReportType) - 1);
    coEditorThreadCollection = std::vector<pthread_t>();
    coEditorThreadCollection.resize(sizeof(ReportType) - 1);
    screenBuffer = BoundedQueue<std::string>(screenBufferSize);
    return true;
}

void categorizeReport(std::string basicString);

void *singleReporterRoutine(void *repHandler) { //ConfigurationHandler::ConfigurationItem
    auto reporter = (ReporterHandler *) repHandler;
    reporter->makeReports();
}

void *dispatcherRoutine(void *params) {
    bool finished;
    // As long as there is at least 1 active reported
    while (true) {
        finished = true;
        //Scan each reporter
        for (auto &reporterQueue: reporterQueues) {
            // If reporter hasn't sent done yet.
            if (reporterQueue._done)
                continue;
            // Get report from reporter, _buffer is THREAD SAFE WITH MUTEX
            auto result = reporterQueue._buffer.pop();
            if (result == "DONE") {
                reporterQueue._done = true;
                continue;
            }
            //Atomic insertion to queue
            //dispatcher.push(result);
            categorizeReport(result);
            finished = false;
        }
        if (finished)
            break;
    }
    //dispatcher.push("DONE");
    typeSortedQueueCollection[SPORTS].push("DONE");
    typeSortedQueueCollection[WEATHER].push("DONE");
    typeSortedQueueCollection[NEWS].push("DONE");
}

void categorizeReport(std::string report) {
    auto type = Report::getReportType(report);
    typeSortedQueueCollection[type].push(report);
}

void editReport() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void *coEditorRoutine(void *params){
    auto type = *((ReportType*)params);
    auto queue = typeSortedQueueCollection[type];
    auto rep = queue.pop();
    while (rep != "DONE") {
        editReport();
        screenBuffer.push(rep);
        rep = queue.pop();
//        std::cout << rep << std::endl;
    }
    queue.push("DONE");
}

void screenManagerRoutine() {
   /* char doneCounter = 3;
    while (doneCounter) {
        auto report = screenBuffer.pop();
        if (report == "DONE") {
            doneCounter--;
            continue;
        }
        std::cout << report <<std::endl;
    }
    std::cout << "DONE" << std::endl;*/
    int left = 3;
    while (1) {
        auto res = screenBuffer.pop();
/*        if(res == "DONE") {
            std::cout << --left << std::endl;
        }*/
        std::cout << screenBuffer.pop() << std::endl;
    }
}

void routine() {
    for (int i = 0; i < reporterQueues.size(); ++i) {
        auto thread = &reporterThreads[i];
        auto param = (void *) &reporterQueues[i];
        pthread_create(thread, NULL, &singleReporterRoutine, param);
    }

    pthread_create(&dispatcher_thread, NULL, dispatcherRoutine, NULL);

    for (int i = 0; i < coEditorThreadCollection.size(); ++i) {
        auto thread = &coEditorThreadCollection[i];
        pthread_create(thread, NULL, coEditorRoutine, (void *)(&reportTypes[i]));
    }
    screenManagerRoutine();
    NULL;
}

int main(int argc, char *argv[]) {
    if(!init())
        return 1;
    routine();
    return 0;
}
