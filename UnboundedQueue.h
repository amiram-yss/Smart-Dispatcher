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
    UnboundedQueue(const UnboundedQueue<T>&) = delete;
    UnboundedQueue& operator=(const UnboundedQueue<T>&) = delete;

public:
    UnboundedQueue() : _lock(), _full() {
        sem_init(&_full, 0, 0);
        //pthread_mutex_unlock(&_lock);
        pthread_mutex_init(&_lock, nullptr);
        std::cout << "THIS ADDRESS: " << this << std::endl;
        std::cout << "INITED SEM ADDRESS: " << &_full << std::endl;
    }

    //TODO destructor
    //std::string pop() {
    T pop() {
        //wait until there is at least 1 object in queue
        std::cout<<"PRE POP THIS ADDRESS: " << this << std::endl;
        std::cout<<"PRE POP SEM WAIT: " << &_full << std::endl;
        sem_wait(&_full);
        std::cout<<"POST POP SEM WAIT: " <<std::endl;
        // lock queue
        pthread_mutex_lock(&_lock);
        //do operations on queue
        auto str = _queue.front();
        _queue.pop();
        //TODO dbg

        //std::cout<< ">> UNBOUNDED POP: " << str << std::endl;

        //unlock queue
        pthread_mutex_unlock(&_lock);
        //return upper value
        //std::cout<< "!! UNBOUNDED POP: " << str << std::endl;
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
        //sem_post(&_full); //full++
        //std::cout<< ">> UNBOUNDED PUSH: " << str << std::endl;
        //unlock
        pthread_mutex_unlock(&_lock);
        //std::cout<< "!! UNBOUNDED PUSH: " << str << std::endl;
        //std::cout << "GUSH" << &_full << std::endl;
        int x = sem_post(&_full); //full++
        std::cout << "SEM code " << std::to_string(x) << std::endl;
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