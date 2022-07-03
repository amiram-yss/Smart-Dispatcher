//
// Created by amiramyss on 7/1/22.
//

#include <thread>
#include "mutex.h"

mutex::mutex() {
    pthread_mutex_init(&_mutex_obj, nullptr);
}

mutex::~mutex() {
    pthread_mutex_destroy(&_mutex_obj);
}

void mutex::lock() {
    pthread_mutex_lock(&_mutex_obj);
}

void mutex::unlock() {
    pthread_mutex_unlock(&_mutex_obj);
}
