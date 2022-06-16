//
// Created by amiramyss on 6/14/22.
//

#ifndef OS3_UNBOUNDEDQUEUE_H
#define OS3_UNBOUNDEDQUEUE_H

#include <queue>
#include <string>
#include <semaphore.h>

template<class T>
class UnboundedQueue : public std::queue<T> {
private:
    pthread_mutex_t _lock;
    sem_t _full;
public:
    UnboundedQueue() {
        sem_init(&_full, 0, 0);
    }

    std::string pop(){
        //wait until there is at least 1 object in queue
        sem_wait(&_full);
        // lock queue
        pthread_mutex_lock(&_lock);
        //do operations on queue
        auto str = std::queue<T>::front();
        std::queue<T>::pop();
        //unlock queue
        pthread_mutex_unlock(&_lock);
        //return upper value
        return str;
    }

    void push(T str) {
        // no limitation here. just lock and proceed
        pthread_mutex_lock(&_lock);
        //push
        std::queue<T>::push(str);
        sem_post(&_full); //full++
        //unlock
        pthread_mutex_unlock(&_lock);
    }


    T top() {
        T str;
        pthread_mutex_lock(&_lock);
        if (std::queue<T>::empty())
            str = nullptr;
        else
            str = std::queue<T>::front();
        pthread_mutex_unlock(&_lock);
        return str;
    }

};


#endif //OS3_UNBOUNDEDQUEUE_H
