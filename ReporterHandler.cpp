//
// Created by amiramyss on 6/16/22.
//

#include "ReporterHandler.h"

/**
 * Constructor.
 */
ReporterHandler::ReporterHandler() :
        _buffer(0), _id(-1), _reportsNum(-1), _done(false) {
}

/**
 * Constructor.
 * @param data report type.
 */
ReporterHandler::ReporterHandler(ConfigurationHandler::ConfigurationItem data)
        : _buffer(data.capacityQueue),
          _id(data.producerId),
          _reportsNum(data.numProducts),
          _done(false) {
}

/**
 * Make reporter make reports.
 */
void ReporterHandler::makeReports() {
    for (unsigned int i = 0; i < _reportsNum; i++) {
        auto str = Report(_id, i).toString();
        _buffer.push(str);
        //std::cout << _buffer.top() << std::endl;
    }
    _buffer.push("DONE"); //Report(-1,-1)
}
