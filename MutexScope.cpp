//
// Created by amiramyss on 7/1/22.
//

#include "MutexScope.h"

MutexScope::MutexScope(Mutex &lock) : _lock(lock) {
    _lock.lock();
}

MutexScope::~MutexScope() {
    _lock.unlock();
}
