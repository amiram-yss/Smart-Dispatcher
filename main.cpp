#include <iostream>
#include "BoundedQueue.h"
#include "UnboundedQueue.h"
#include "ConfigurationHandler.h"
#include "Report.h"
#include "ReporterHandler.h"

//static std::vector<ConfigurationHandler::ConfigurationItem> *configs;
static std::vector<ReporterHandler> reporterQueues;
static std::vector<pthread_t> reporterThreads;

bool init() {
    std::vector<ConfigurationHandler::ConfigurationItem> *configs = ConfigurationHandler::ReadConfig("config.txt");
    if(configs == nullptr)
        return false;
    for (auto conf : *configs) {
        reporterQueues.push_back(ReporterHandler(conf));
    }
    reporterThreads = std::vector<pthread_t>();
    reporterThreads.resize(reporterQueues.size());
    return true;
}

void *singleReporterRoutine(void *repHandler) { //ConfigurationHandler::ConfigurationItem
    auto reporter = (ReporterHandler *)repHandler;
    reporter->makeReports();
/*//    item->makeReports();
    auto a = item->_buffer.pop();
    while (!a.isEndingReport()) {
        std::cout << a <<std::endl;
        a = item->_buffer.pop();
    }
    return 0;*/
}

void routine() {
    for (int i = 0; i < /*reporterQueues.size()*/1; ++i) {
        auto thread = &reporterThreads[i];
        auto param = (void *)&reporterQueues[i];
        pthread_create(thread, NULL, &singleReporterRoutine, param);
        reporterQueues[i].makeReports();
    }

}

int main(int argc, char *argv[]) {
    init();
    routine();
    return 0;
}
