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
    bool _done;
    BoundedQueue<std::string> _buffer;
    ReporterHandler(){
        this->_id = -1;
        this->_reportsNum = -1;
        _done = false;
    }

    ReporterHandler(ConfigurationHandler::ConfigurationItem data) : _id(data.producerId)
            , _reportsNum(data.numProducts) , _done(false) {
        _buffer = BoundedQueue<std::string>(data.capacityQueue);
    }

    void makeReports(){
        for (unsigned int i = 0; i < _reportsNum; i++) {
            auto str = Report(_id, i).toString();
            _buffer.push(str);
            //std::cout << _buffer.top() << std::endl;
        }
        _buffer.push("DONE"); //Report(-1,-1)
    }
};


#endif //OS3_REPORTERHANDLER_H
