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

/**
 * Thread safe unlimited queue.
 * @tparam T
 */
template<class T>
class UnboundedQueue {
private:
    //pthread_mutex_t _lock;
    Mutex _lock;
    //sem_t _full;
    std::queue<T> _queue;
    std::unique_ptr<Semaphore> _full;

public:
    UnboundedQueue(const UnboundedQueue<T>&) = delete;
    UnboundedQueue& operator=(const UnboundedQueue<T>&) = delete;

public:
    /**
     * Constructor.
     */
    UnboundedQueue() : _lock(), _full(std::make_unique<Semaphore>(0)) {
        //sem_init(&_full, 0, 0);
        //pthread_mutex_unlock(&_lock);
        //pthread_mutex_init(&_lock, nullptr);
    }
    /*
    * Pop from queue.
    * @return variable at the top.
    */
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

    /**
     * Push to queue.
     * @param var
     */
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

    /**
     * See top of queue.
     * @return Top variable.
     */
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

    /**
     * Destructor.
     */
    ~UnboundedQueue() {
        //pthread_mutex_destroy(&_lock);
        /*sem_close(&_full);
        sem_destroy(&_full);*/
    }
};