//
// Created by amiramyss on 6/14/22.
//

#pragma once

#include <queue>
#include <string>
#include <semaphore.h>
#include <memory>
#include "Mutex.h"
#include "MutexScope.h"
#include "Semaphore.h"

template<class T>
class UnboundedQueue {
private:
    //pthread_mutex_t _lock;
    Mutex _lock;
    //sem_t _full;
    std::queue<T> _queue;
    std::shared_ptr<Semaphore> _full;

public:
    UnboundedQueue(const UnboundedQueue<T>&) = delete;
    UnboundedQueue& operator=(const UnboundedQueue<T>&) = delete;

public:
    UnboundedQueue() : _lock(), _full(new Semaphore()) {
        //sem_init(&_full, 0, 0);
        //pthread_mutex_unlock(&_lock);
        //pthread_mutex_init(&_lock, nullptr);
    }

    //std::string pop() {
    T pop() {
        T top_var;
        //wait until there is at least 1 object in queue
        //sem_wait(&_full);
        _full->wait();
        //std::cout<<"POST POP SEM WAIT: " <<std::endl;
        // lock queue
        {
            //pthread_mutex_lock(&_lock);
            MutexScope scope(_lock);
            //do operations on queue
            top_var = _queue.front();
            _queue.pop();
            //pthread_mutex_unlock(&_lock);
        }
        //unlock queue, return upper value
        return top_var;
    };

    void push(T str) {
        // no limitation here. just lock and proceed
        {
            MutexScope scope(_lock);
            //pthread_mutex_lock(&_lock);
            //push
            _queue.push(str);
            //unlock
            //pthread_mutex_unlock(&_lock);
        }
        //sem_post(&_full); //full++
        _full->post();
        //std::cout << "SEM code " << std::to_string(x) << std::endl;
    }


    T top() {
        T str;
        {
            MutexScope scope(_lock);
            //pthread_mutex_lock(&_lock);
            if (_queue.empty())
                str = nullptr;
            else
                str = _queue.front();
            //pthread_mutex_unlock(&_lock);
        }
        return str;
    }

    ~UnboundedQueue() {
        //pthread_mutex_destroy(&_lock);
        /*sem_close(&_full);
        sem_destroy(&_full);*/
    }
};