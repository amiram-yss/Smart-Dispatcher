#include <iostream>
#include "BoundedQueue.h"
#include "UnboundedQueue.h"
#include "ConfigurationHandler.h"
#include "Report.h"

static std::vector<ConfigurationHandler::ConfigurationItem> *configs;
static std::vector<BoundedQueue> reporterQueues;
static std::vector<Report> *reporterThreads;

bool init() {
    configs = ConfigurationHandler::ReadConfig("config.txt");
    if(configs == nullptr)
        return false;
    for (auto conf : *configs) {
        reporterQueues.push_back(BoundedQueue(conf.capacityQueue));
    }
    return true;
}

void routine() {
    reporterThreads->resize(5);//TODO: resize problem
}

int main(int argc, char *argv[]) {
    init();
    routine();
    return 0;
}
