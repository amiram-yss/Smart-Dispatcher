#include <iostream>
#include "BoundedQueue.cpp"
#include "UnboundedQueue.cpp"
#include "ConfigurationHandler.h"
#include "Report.h"
#include "ReporterHandler.h"
#include <chrono>
#include <thread>

//Data
static std::vector<ReporterHandler> reporterQueues;
static std::vector<UnboundedQueue<std::string>> dispatcherQueues;
static BoundedQueue<std::string> screenBuffer;
static const ReportType reportTypes[] = {SPORTS, NEWS, WEATHER};

//Threads
static std::vector<pthread_t> reporterThreads;
static pthread_t dispatcher_thread;
static std::vector<pthread_t> coEditorThreadCollection;

/**
 * Inits all variables for program's execution.
 * @param fileName path to configuration file
 * @return True if init been successful. False o.w.
 */
bool init(std::string fileName) {
    // For good randomization.
    srand(time(NULL));
    // Read config.
    int screenBufferSize;
    std::vector<ConfigurationHandler::ConfigurationItem> *configs = ConfigurationHandler::ReadConfig(fileName, &screenBufferSize);
    // If file loading fails, return false
    if (configs == nullptr)
        return false;
    for (auto conf: *configs) {
        reporterQueues.push_back(ReporterHandler(conf));
    }
    delete configs;
    // Init threads
    reporterThreads = std::vector<pthread_t>();
    reporterThreads.resize(reporterQueues.size());
    coEditorThreadCollection = std::vector<pthread_t>(sizeof(ReportType) - 1);
    // Init queues
    dispatcherQueues = std::vector<UnboundedQueue<std::string>>(sizeof (ReportType) - 1);
    screenBuffer = BoundedQueue<std::string>(screenBufferSize);
    // Initialization success :)
    return true;
}

/**
 * Starts reporter routine.
 * @param repHandler pointer to a reporter to start his routine.
 * @return (INOP)
 */
void *singleReporterRoutine(void *repHandler) {
    auto reporter = (ReporterHandler *) repHandler;
    reporter->makeReports();
    return nullptr;
}

/**
 * Puts report in the right category's queue.
 * @param report The report to categorize.
 */
void categorizeReport(std::string report) {
    auto type = Report::getReportType(report);
    dispatcherQueues[type].push(report);
}

/**
 * Handles the execution routine of the dispatcher.
 * As long ase there are reporters who haven't finished working, keep working.
 * @param params (INOP)
 * @return (INOP)
 */
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
            categorizeReport(result);
            finished = false;
        }
        if (finished)
            break;
    }
    dispatcherQueues[SPORTS].push("DONE");
    dispatcherQueues[WEATHER].push("DONE");
    dispatcherQueues[NEWS].push("DONE");
    return nullptr;
}

/**
 * Simulates reporter edit time.
 */
void editReport() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

/**
 * Pushes news items, from categorized queues into the screen buffer.
 * @param params (INOP)
 * @return (INOP)
 */
void *coEditorRoutine(void *params){
    auto type = *((ReportType*)params);
    //UnboundedQueue<std::string>& queue = dispatcherQueues[type];
    auto queue = &dispatcherQueues[type];
    auto rep = queue->pop();
    while (rep != "DONE") {
        //Make an edit (basically nothing)..
        editReport();
        //Push to monitor buffer.
        screenBuffer.push(rep);
        //Upload next report.
        rep = queue->pop();
    }
    // All dispatcher specific queue reports are submitted, end with a DONE message.
    screenBuffer.push("DONE");
    return nullptr;
}

/**
 * Keeps pulling items from the queue, and show them.
 */
void screenManagerRoutine() {
    int left = dispatcherQueues.size();
    while (left) {
        auto res = screenBuffer.pop();
        if(res == "DONE") {
            --left;
            continue;
        }
        std::cout << res << std::endl;
    }
    std::cout << "DONE" << std::endl;
}

/**
 * Start the program.
 * Runs the threads and starts the routines of each part.
 */
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
}

int main(int argc, char *argv[]) {
    if(argc < 2 || !init(argv[1]))
        return 1;
    routine();
    return 0;
}
