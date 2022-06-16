//
// Created by amiramyss on 6/15/22.
//

#ifndef OS3_DISPATCHER_H
#define OS3_DISPATCHER_H

#include "BoundedQueue.h"
#include "UnboundedQueue.h"
#include "Report.h"
#include "ReporterHandler.h"

class Dispatcher {
private:
    std::vector<ReporterHandler> *_sources;
    pthread_mutex_t _lock;
public:
    UnboundedQueue<std::string> *_buffer;

    Dispatcher();
    Dispatcher(std::vector<ReporterHandler> *reportersCollection);
    void *Routine(void*);
};


#endif //OS3_DISPATCHER_H
