//
// Created by amiramyss on 8/2/22.
//

#include "Semaphore.h"

static int ctr = 0;

/**
 * Constructor.
 * @param value initialized value.
 */
Semaphore::Semaphore(long long int value) : _value(value) {
    //_value = value;
    sem_init(&_lock, 0, value);
}

/**
 * Decrease semaphore val by 1. If already 0, waits until raises.
 */
void Semaphore::wait() {
    sem_wait(&_lock);
}

/**
 * Raise val by 1.
 */
void Semaphore::post() {
    sem_post(&_lock);
}

/**
 * Destructor.
 */
Semaphore::~Semaphore() {
    sem_close(&_lock);
    sem_destroy(&_lock);
}
