//
// Created by amiramyss on 8/2/22.
//

#include <semaphore.h>
#include "Semaphore.h"

Semaphore::Semaphore(long long value) {
    this->_value = value;
    sem_init(&_lock, 0, _value);
}

Semaphore::~Semaphore() {
    sem_close(&_lock);
    sem_destroy(&_lock);
}

void Semaphore::wait() {
    sem_wait(&_lock); //lock++
}

void Semaphore::post() {
    sem_post(&_lock); //lock--
}
