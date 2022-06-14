//
// Created by amiramyss on 6/14/22.
//

#include "UnboundedQueue.h"

UnboundedQueue::UnboundedQueue() {
    sem_init(&_full, 0, 0);
}

void UnboundedQueue::push(std::string str) {
    // no limitation here. just lock and proceed
    pthread_mutex_lock(&_lock);
    //push
    std::queue<std::string>::push(str);
    sem_post(&_full); //full++
    //unlock
    pthread_mutex_unlock(&_lock);
}

std::string UnboundedQueue::pop() {
    //wait until there is at least 1 object in queue
    sem_wait(&_full);
    // lock queue
    pthread_mutex_lock(&_lock);
    //do operations on queue
    auto str = std::queue<std::string>::front();
    std::queue<std::string>::pop();
    //unlock queue
    pthread_mutex_unlock(&_lock);
    //return upper value
    return str;
}

std::string UnboundedQueue::top() {
    std::string str;
    pthread_mutex_lock(&_lock);
    if(std::queue<std::string>::empty())
        str = nullptr;
    else
        str = std::queue<std::string>::front();
    pthread_mutex_unlock(&_lock);
    return str;
}

