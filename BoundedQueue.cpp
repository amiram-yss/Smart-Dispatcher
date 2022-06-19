//
// Created by amiramyss on 6/8/22.
//

#pragma once

#include <queue>
#include <string>
#include <semaphore.h>
#include <iostream>

template<class T>
class BoundedQueue {
private:
    std::queue<T> _queue;
    pthread_mutex_t _lock;
    sem_t _empty, _full;
    unsigned int _capacity;

public:
    BoundedQueue(unsigned int capacity = 0) : _capacity(capacity), _queue() {
        sem_init(&_full, 0, 0);
        sem_init(&_empty, 0, _capacity);
        pthread_mutex_init(&_lock, nullptr);
    }

    void push(T var) {
        //wait as long as queue full
        sem_wait(&_empty); //empty--;
        {
            pthread_mutex_lock(&_lock); //lock mutex
            _queue.push(var);
            sem_post(&_full); //full++;
            pthread_mutex_unlock(&_lock); //unlock
        }

    }

    T pop() {
        //wait as long as there are no nodes in queue
        sem_wait(&_full); //full--
        pthread_mutex_lock(&_lock);

        T t = _queue.front();
        _queue.pop();

        sem_post(&_empty); //empty++
        //removing 1 value
        pthread_mutex_unlock(&_lock);
        return t;
    }

    T top() {
        T str;
        pthread_mutex_lock(&_lock);
        if (_queue.empty())
            str = T();
        else
            str = _queue.front();
        pthread_mutex_unlock(&_lock);
        return str;
    }

    ~BoundedQueue() {
        pthread_mutex_destroy(&_lock);
        sem_close(&_empty);
        sem_destroy(&_empty);
        sem_close(&_full);
        sem_destroy(&_full);
    }

};