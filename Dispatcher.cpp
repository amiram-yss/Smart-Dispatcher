//
// Created by amiramyss on 6/15/22.
//

#include "Dispatcher.h"

Dispatcher::Dispatcher() {

}

Dispatcher::Dispatcher(std::vector<ReporterHandler> *reportersCollection)
:_sources(reportersCollection){
    _sources = reportersCollection;
}

void *Dispatcher::Routine(void *params) {
    bool finished;
    // As long as there is at least 1 active reported
    while (1) {
        finished = true;
        //Scan each reporter
        for (int i = 0; i < _sources->size(); ++i) {
            // If reporter hasn't sent done yet.
            if ((*_sources)[i]._done)
                continue;
            // Get report from reporter, _buffer is THREAD SAFE WITH MUTEX
            auto result = (*_sources)[i]._buffer.pop();
            if(result == "DONE") {
                (*_sources)[i]._done = true;
                continue;
            }
            //Atomic insertion to queue
            pthread_mutex_lock(&_lock);
            _buffer->push(result);
            //TODO delete
            std::cout << result << std::endl;
            pthread_mutex_unlock(&_lock);


            finished = false;
        }
        if (finished)
            break;
    }
}