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
    // True if reporter finisher reporting.
    bool _done;

    // Reports bounded queue
    BoundedQueue<std::string> _buffer;

    /**
     * Constructor.
     * Type rendered randomly.
     */
    ReporterHandler();

    /**
     * Constructor.
     * @param data report type.
     */
    explicit ReporterHandler(ConfigurationHandler::ConfigurationItem data);

    /**
     * Make reporter make reports.
     */
    void makeReports();
};

