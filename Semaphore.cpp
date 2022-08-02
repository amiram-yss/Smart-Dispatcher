//
// Created by amiramyss on 8/2/22.
//

#include "Semaphore.h"

Semaphore::Semaphore(long long int value) {
    _value = value;
    sem_init(&_lock, 0, value);
}

void Semaphore::wait() {
    sem_wait(&_lock);
}

void Semaphore::post() {
    sem_wait(&_lock);
}

Semaphore::~Semaphore() {
    sem_close(&_lock);
    sem_destroy(&_lock);
}
