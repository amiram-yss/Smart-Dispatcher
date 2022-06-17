#include <iostream>
#include "BoundedQueue.h"
#include "UnboundedQueue.h"
#include "ConfigurationHandler.h"
#include "Report.h"
#include "ReporterHandler.h"

//Collections
//static std::vector<ConfigurationHandler::ConfigurationItem> *configs;
static std::vector<ReporterHandler> reporterQueues;
static std::vector<pthread_t> reporterThreads;
static pthread_t dispatcher_thread;
//Dispatcher dispatcher;
// TODO check how to do this non static
static UnboundedQueue<std::string> dispatcher;
static std::vector<UnboundedQueue<std::string>> typeSortedQueue;
static std::vector<pthread_t> typeSortedThread

bool init() {
    std::vector<ConfigurationHandler::ConfigurationItem> *configs = ConfigurationHandler::ReadConfig("config.txt");
    if (configs == nullptr)
        return false;
    for (auto conf: *configs) {
        reporterQueues.push_back(ReporterHandler(conf));
    }
    reporterThreads = std::vector<pthread_t>();
    reporterThreads.resize(reporterQueues.size());
    dispatcher = UnboundedQueue<std::string>();
    return true;
}

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
            //pthread_mutex_lock(&lock_dispatcher);
            dispatcher.push(result);
            //TODO delete
            std::cout << result << std::endl;
            //pthread_mutex_unlock(&lock_dispatcher);

            finished = false;
        }
        if (finished)
            break;
    }
}



void routine() {
    for (int i = 0; i < reporterQueues.size(); ++i) {
        auto thread = &reporterThreads[i];
        auto param = (void *) &reporterQueues[i];
        pthread_create(thread, NULL, &singleReporterRoutine, param);
//        reporterQueues[i].makeReports();
    }
    pthread_create(&dispatcher_thread, NULL, dispatcherRoutine, NULL);
/*    for (int i = 0; i < reporterQueues.size(); ++i) {
        auto thread = &reporterThreads[i];
        pthread_join(*thread, NULL);
    }*/
    pthread_join(dispatcher_thread, NULL);

}

int main(int argc, char *argv[]) {
    init();
    routine();
    return 0;
}
