//
// Created by amiramyss on 6/15/22.
//

#ifndef OS3_REPORTERHANDLER_H
#define OS3_REPORTERHANDLER_H


#include <csignal>
#include "BoundedQueue.h"
#include "ConfigurationHandler.h"
#include "Report.h"

//Due to template, forced to implement methods in .h file.
class ReporterHandler {
private:
    unsigned int _id, _reportsNum;
public:
    BoundedQueue<Report> _buffer;
    ReporterHandler(){
        this->_id = -1;
        this->_reportsNum = -1;
    }

    ReporterHandler(ConfigurationHandler::ConfigurationItem data) : _id(data.producerId)
            , _reportsNum(data.numProducts) {
        _buffer = BoundedQueue<Report>(data.capacityQueue);
    }

    void makeReports(){
        for (int i = 0; i < _reportsNum; i++) {
            _buffer.push(Report(_id, i));
            std::cout << _buffer.top() << std::endl;
        }
        _buffer.push(Report(-1,-1));
    }
};


#endif //OS3_REPORTERHANDLER_H
