//
// Created by amiramyss on 6/8/22.
//
#pragma once

#include <queue>
#include <string>
#include <semaphore.h>
#include <iostream>
#include <memory>
#include "Mutex.h"
#include "MutexScope.h"
#include "Semaphore.h"

/**
 * Queue with fixed capacity. Thread safe.
 * @tparam T
 */

template<class T>
class BoundedQueue {
private:
    std::queue<T> _queue;
    //pthread_mutex_t _lock;
    Mutex _lock;
    //sem_t _empty, _full;
    unsigned int _capacity;
    std::shared_ptr<Semaphore> _empty;
    std::shared_ptr<Semaphore> _full;

public:
    /**
     * Constructor
     * @param capacity Queue's capacity.
     */
    BoundedQueue(unsigned int capacity = 0) :
        _capacity(capacity), _queue(), _lock() ,
        //_empty(new Semaphore(capacity)), _full(new Semaphore(0))
        _empty(std::make_shared<Semaphore>(capacity)),
        _full(std::make_shared<Semaphore>(0))
        {
    }

    /**
     * Push to queue.
     * @param var
     */
    void push(T var) {
        //wait as long as queue full
        //sem_wait(&_empty); //empty--;
        _empty->wait();
        {
            MutexScope scope(_lock);
            _queue.push(var);
            //sem_post(&_full); //full++;
            _full->post();
        }
    }

    /**
     * Pop from queue.
     * @return variable at the top.
     */
    T pop() {
        T t;
        //wait as long as there are no nodes in queue
        //sem_wait(&_full); //full--
        _full->wait();
        {
            //pthread_mutex_lock(&_lock);
            MutexScope scope(_lock);
            t = _queue.front();
            _queue.pop();

            //sem_post(&_empty); //empty++
            _empty->post();
            //removing 1 value
            //pthread_mutex_unlock(&_lock);
        }
        return t;
    }

    /**
     * See top of queue.
     * @return Top variable.
     */
    T top() {
        T str;
        //pthread_mutex_lock(&_lock);
        {
            MutexScope scope(_lock);
            if (_queue.empty())
                str = T();
            else
                str = _queue.front();
        }
        //pthread_mutex_unlock(&_lock);
        return str;
    }

    /**
     * Destructor.
     */
    ~BoundedQueue() {
        //pthread_mutex_destroy(&_lock);
        /*sem_close(&_empty);
        sem_destroy(&_empty);
        sem_close(&_full);
        sem_destroy(&_full);*//*
        delete _full;
        delete _empty;*/
    }
};