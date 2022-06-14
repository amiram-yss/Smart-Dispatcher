//
// Created by amiramyss on 6/8/22.
//

#include "BoundedQueue.h"
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

BoundedQueue::BoundedQueue(unsigned int capacity) : _capacity(capacity) {
    sem_init(&_full, 0 ,0);
    sem_init(&_empty,0,_capacity);
}

BoundedQueue::BoundedQueue() {
    //free(this);
    std::cerr << "Unsupported constructor implementation" << std::endl;
    throw std::exception();
}

void BoundedQueue::push(std::string str) {
    //wait as long as queue full
    sem_wait(&_empty); //empty--;
    pthread_mutex_lock(&_lock); //lock mutex
    std::queue<std::string>::push(str);
    sem_post(&_full); //full++;
    pthread_mutex_unlock(&_lock); //unlock
}

std::string BoundedQueue::pop() {
    //wait as long as there are no nodes in queue
    sem_wait(&_full); //full--
    pthread_mutex_lock(&_lock);
    /*if(this->empty())
        return nullptr;*/
    std::string t = this->front();
    std::queue<std::string>::pop();
    sem_post(&_empty); //empty++
    //removing 1 value
    pthread_mutex_unlock(&_lock);
    return t;
}
