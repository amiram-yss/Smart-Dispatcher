#include <iostream>
#include "BoundedQueue.h"
#include "UnboundedQueue.h"
#include "ConfigurationHandler.h"
#include "Report.h"
#include "ReporterHandler.h"
#include "Dispatcher.h"

//Collections
//static std::vector<ConfigurationHandler::ConfigurationItem> *configs;
static std::vector<ReporterHandler> reporterQueues;
static std::vector<pthread_t> reporterThreads;
static pthread_t dispatcher_thread;
//Dispatcher dispatcher;
UnboundedQueue<std::string> dispatcher;

// Mutex
pthread_mutex_t lock_dispatcher;
bool init() {
    std::vector<ConfigurationHandler::ConfigurationItem> *configs = ConfigurationHandler::ReadConfig("config.txt");
    if(configs == nullptr)
        return false;
    for (auto conf : *configs) {
        reporterQueues.push_back(ReporterHandler(conf));
    }
    reporterThreads = std::vector<pthread_t>();
    reporterThreads.resize(reporterQueues.size());
    dispatcher = UnboundedQueue<std::string>();
    return true;
}

void *singleReporterRoutine(void *repHandler) { //ConfigurationHandler::ConfigurationItem
    auto reporter = (ReporterHandler *)repHandler;
    reporter->makeReports();
}

void *dispatcherRoutine(void *params) {
    bool finished;
    // As long as there is at least 1 active reported
    while (1) {
        finished = true;
        //Scan each reporter
        for (int i = 0; i < reporterQueues.size(); ++i) {
            // If reporter hasn't sent done yet.
            if (reporterQueues[i]._done)
                continue;
            // Get report from reporter, _buffer is THREAD SAFE WITH MUTEX
            auto result = reporterQueues[i]._buffer.pop();
            if(result == "DONE") {
                reporterQueues[i]._done = true;
                continue;
            }
            //Atomic insertion to queue
            pthread_mutex_lock(&lock_dispatcher);
            dispatcher.push(result);
            //TODO delete
            std::cout << result << std::endl;
            pthread_mutex_unlock(&lock_dispatcher);

            finished = false;
        }
        if (finished)
            break;
    }
}

void routine() {
    for (int i = 0; i < /*reporterQueues.size()*/1; ++i) {
        auto thread = &reporterThreads[i];
        auto param = (void *)&reporterQueues[i];
        pthread_create(thread, NULL, &singleReporterRoutine, param);
//        reporterQueues[i].makeReports();
    }
    //Dispatcher dispatcher = Dispatcher(&reporterQueues);
    pthread_create(&dispatcher_thread, NULL, dispatcherRoutine , NULL);
    pthread_join(dispatcher_thread, NULL);
}

int main(int argc, char *argv[]) {
    init();
    routine();
    return 0;
}
