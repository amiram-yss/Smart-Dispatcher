//
// Created by amiramyss on 7/1/22.
//

#include "mutex_scope.h"

mutex_scope::mutex_scope(mutex &lock) :_lock(lock) {
    _lock.lock();
}

mutex_scope::~mutex_scope() {
    _lock.unlock();
}
