//
// Created by amiramyss on 6/15/22.
//

#pragma once

#include <csignal>
#include "BoundedQueue.cpp"
#include "ConfigurationHandler.h"
#include "Report.h"

//Due to template, forced to implement methods in .h file.
class ReporterHandler {
private:
    unsigned int _id, _reportsNum;
public:
    bool _done;
    BoundedQueue<std::string> _buffer;

    ReporterHandler();

    explicit ReporterHandler(ConfigurationHandler::ConfigurationItem data);

    void makeReports();
};

