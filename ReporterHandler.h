//
// Created by amiramyss on 6/15/22.
//

#ifndef OS3_REPORTERHANDLER_H
#define OS3_REPORTERHANDLER_H


#include <csignal>
#include "BoundedQueue.h"
#include "ConfigurationHandler.h"

class ReporterHandler {
private:
    BoundedQueue _buffer;
    unsigned int _id, _reportsNum;
public:
    ReporterHandler();
    ReporterHandler(ConfigurationHandler::ConfigurationItem data);

    void run();
};


#endif //OS3_REPORTERHANDLER_H
