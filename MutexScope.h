//
// Created by amiramyss on 7/1/22.
//

#ifndef OS3_MUTEXSCOPE_H
#define OS3_MUTEXSCOPE_H

#include "Mutex.h"

class
MutexScope {
private:
    Mutex &_lock;
public:
    explicit MutexScope(Mutex &lock);

    virtual ~MutexScope();
};


#endif //OS3_MUTEXSCOPE_H
