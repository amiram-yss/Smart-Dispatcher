#include <iostream>
#include "BoundedQueue.h"
#include "UnboundedQueue.h"
#include "ConfigurationHandler.h"
#include "Report.h"

static std::vector<ConfigurationHandler::ConfigurationItem> *configs;
static std::vector<BoundedQueue> reporterQueues;
static std::vector<pthread_t> *reporterThreads;

bool init() {
    configs = ConfigurationHandler::ReadConfig("config.txt");
    if(configs == nullptr)
        return false;
    for (auto conf : *configs) {
        reporterQueues.push_back(BoundedQueue(conf.capacityQueue));
    }
    reporterThreads = new std::vector<pthread_t>();
    reporterThreads->resize(reporterQueues.size());
    return true;
}

void singleReporterRoutine(ConfigurationHandler::ConfigurationItem confItem) {

}

void routine() {
    for (int i = 0; i < reporterThreads->size(); i++) {

    }
}

int main(int argc, char *argv[]) {
    init();
    routine();
    return 0;
}
