//
// Created by amiramyss on 6/15/22.
//

#include "ReporterHandler.h"

ReporterHandler::ReporterHandler() {
    this->_id = -1;
}

ReporterHandler::ReporterHandler(ConfigurationHandler::ConfigurationItem data)
    :_id(data.producerId), _reportsNum(data.numProducts) {
    _buffer = BoundedQueue(data.capacityQueue);
}

