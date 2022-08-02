//
// Created by amiramyss on 7/1/22.
//

#include <thread>
#include <iostream>
#include "Mutex.h"

Mutex::Mutex() {
    pthread_mutex_init(&_mutex_obj, nullptr);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&_mutex_obj);
}

void Mutex::lock() {
    pthread_mutex_lock(&_mutex_obj);
}

void Mutex::unlock() {
    pthread_mutex_unlock(&_mutex_obj);
}
