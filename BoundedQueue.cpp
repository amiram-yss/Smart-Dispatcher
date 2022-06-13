//
// Created by amiramyss on 6/8/22.
//

#include "BoundedQueue.h"
#include <iostream>
#include <pthread.h>

BoundedQueue::BoundedQueue(int capacity) {
    sem_init
}

BoundedQueue::BoundedQueue() {
    //free(this);
    std::cerr << "Unsupported constructor implementation" << std::endl;
    throw std::exception();
}

void BoundedQueue::push(std::string str) {

    pthread_mutex_lock(&_lock);
    this->push(str);
    empty--;
    full++;

}

std::string BoundedQueue::TryPop() {
    if(this->empty())
        return nullptr;
    std::string t = this->front();
    this->pop();
    return t;
}

