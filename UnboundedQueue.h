//
// Created by amiramyss on 6/14/22.
//

#pragma once

#include <queue>
#include <string>
#include <semaphore.h>

template<class T>
class UnboundedQueue {
private:
    pthread_mutex_t _lock;
    sem_t _full;
    std::queue<T> _queue;

public:
    UnboundedQueue() : _lock(), _full() {
        sem_init(&_full, 0, 0);
        //pthread_mutex_unlock(&_lock);
        pthread_mutex_init(&_lock, nullptr);
    }

    std::string pop() {
        //wait until there is at least 1 object in queue
        sem_wait(&_full);
        // lock queue
        pthread_mutex_lock(&_lock);
        //do operations on queue
        auto str = _queue.front();
        _queue.pop();
        //unlock queue
        pthread_mutex_unlock(&_lock);
        //return upper value
        return str;
    };

    void push(T str) {
        // no limitation here. just lock and proceed
/*        auto yichs = pthread_mutex_trylock(&_lock);
        if(yichs)
            std::cout<<"oof " << yichs <<std::endl;*/
        pthread_mutex_lock(&_lock);
        //push
        _queue.push(str);
        sem_post(&_full); //full++
        //unlock
        pthread_mutex_unlock(&_lock);
    }


    T top() {
        T str;
        pthread_mutex_lock(&_lock);
        if (_queue.empty())
            str = nullptr;
        else
            str = _queue.front();
        pthread_mutex_unlock(&_lock);
        return str;
    }

};