//
// Created by amiramyss on 7/1/22.
//

#ifndef OS3_MUTEX_SCOPE_H
#define OS3_MUTEX_SCOPE_H

#include "mutex.h"

class
mutex_scope {
private:
    mutex &_lock;
public:
    explicit mutex_scope(mutex &lock);

    virtual ~mutex_scope();
};


#endif //OS3_MUTEX_SCOPE_H
