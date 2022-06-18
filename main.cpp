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

static pthread_mutex_t _printLock;

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
    typeSortedQueueCollection = std::vector<UnboundedQueue<std::string>>(sizeof (ReportType) - 1);
    coEditorThreadCollection = std::vector<pthread_t>(sizeof(ReportType) - 1);
    screenBuffer = BoundedQueue<std::string>(screenBufferSize);
    pthread_mutex_init(&_printLock, nullptr);
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
    //typeSortedQueueCollection[WEATHER].push("DONE");
    //typeSortedQueueCollection[NEWS].push("DONE");
}

void categorizeReport(std::string report) {
    auto type = Report::getReportType(report);
    typeSortedQueueCollection[type].push(report);
}

inline void editReport() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000000));
    //usleep(1000000);
}

void *coEditorRoutine(void *params){
    auto type = *((ReportType*)params);
    //UnboundedQueue<std::string>& queue = typeSortedQueueCollection[type];
    auto queue = &typeSortedQueueCollection[type];
    //std::cout << type << std::endl;
    auto rep = queue->pop();
    while (rep != "DONE") {
        //editReport();
        //screenBuffer.push(rep);
        //std::cout << rep << std::endl;
        rep = queue->pop();
    }
    screenBuffer.push("DONE");
}

void screenManagerRoutine() {

    int left = typeSortedQueueCollection.size();
    while (left) {
        auto res = screenBuffer.pop();
        if(res == "DONE") {
            std::cout << screenBuffer.pop() << std::endl;
            //std::cout << std::to_string(--left) << std::endl;
        }
        std::cout << "DONE" << std::endl;
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

    //pthread_create(&coEditorThreadCollection[0], nullptr, coEditorRoutine, (void *)(&reportTypes[0]));
    //pthread_create(&coEditorThreadCollection[1], nullptr, coEditorRoutine, (void *)(&reportTypes[1]));
    //pthread_create(&coEditorThreadCollection[2], nullptr, coEditorRoutine, (void *)(&reportTypes[2]));


/*    for (int i = 0; i < coEditorThreadCollection.size(); ++i) {
        auto thread = &coEditorThreadCollection[i];
        pthread_join(*thread, NULL);
    }*/

    //pthread_join(coEditorThreadCollection[0], nullptr);
    //pthread_join(coEditorThreadCollection[1], nullptr);
    //pthread_join(coEditorThreadCollection[2], nullptr);
    screenManagerRoutine();

    NULL;
}

int main(int argc, char *argv[]) {
    if(!init())
        return 1;
    routine();
    return 0;
}
