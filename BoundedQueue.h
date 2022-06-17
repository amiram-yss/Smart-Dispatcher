//
// Created by amiramyss on 6/8/22.
//

#ifndef OS3_BOUNDEDQUEUE_H
#define OS3_BOUNDEDQUEUE_H


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
    // TODO check if do we need = 0 I mean loser.
    BoundedQueue(unsigned int capacity = 0) : _capacity(capacity), _queue() {
        sem_init(&_full, 0, 0);
        sem_init(&_empty, 0, _capacity);
        pthread_mutex_init(&_lock, nullptr);
    }

    void push(T var) {
        //wait as long as queue full
        sem_wait(&_empty); //empty--;
        pthread_mutex_lock(&_lock); //lock mutex
        _queue.push(var);
        sem_post(&_full); //full++;
        pthread_mutex_unlock(&_lock); //unlock
    }

    T pop() {
        //wait as long as there are no nodes in queue
        sem_wait(&_full); //full--
        pthread_mutex_lock(&_lock);
        /*if(this->empty())
            return nullptr;*/
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
};


#endif //OS3_BOUNDEDQUEUE_H
