//
// Created by amiramyss on 6/8/22.
//

#ifndef OS3_BOUNDEDQUEUE_H
#define OS3_BOUNDEDQUEUE_H


#include <queue>
#include <string>
#include <semaphore.h>
#include <iostream>

template <class T>
class BoundedQueue : public std::queue<T>{
private:
    pthread_mutex_t _lock;
    sem_t _empty, _full;
    unsigned int _capacity;
public:
    BoundedQueue(unsigned int capacity): _capacity(capacity) {
        sem_init(&_full, 0 ,0);
        sem_init(&_empty,0,_capacity);
    }
    BoundedQueue(){
        sem_init(&_full, 0 ,0);
        sem_init(&_empty,0,0);
        //free(this);
        /*std::cerr << "Unsupported constructor implementation" << std::endl;
        throw std::exception();*/
    }
    
    void push(T var){
        //wait as long as queue full
        sem_wait(&_empty); //empty--;
        pthread_mutex_lock(&_lock); //lock mutex
        std::queue<T>::push(var);
        sem_post(&_full); //full++;
        pthread_mutex_unlock(&_lock); //unlock
    }
    T pop(){
        //wait as long as there are no nodes in queue
        sem_wait(&_full); //full--
        pthread_mutex_lock(&_lock);
        /*if(this->empty())
            return nullptr;*/
        T t = this->front();
        std::queue<T>::pop();
        sem_post(&_empty); //empty++
        //removing 1 value
        pthread_mutex_unlock(&_lock);
        return t;
    }

    T top(){
        T str;
        pthread_mutex_lock(&_lock);
        if(std::queue<T>::empty())
            str = T();
        else
            str = std::queue<T>::front();
        pthread_mutex_unlock(&_lock);
        return str;
    }
};


#endif //OS3_BOUNDEDQUEUE_H
