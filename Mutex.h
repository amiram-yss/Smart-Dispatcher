//
// Created by amiramyss on 7/1/22.
//

#ifndef OS3_MUTEX_H
#define OS3_MUTEX_H

//RAII principle implementation for p_thread_mutex

#include <csignal>

class Mutex {
private:
    pthread_mutex_t _mutex_obj;
public:
    Mutex(const Mutex&) = default;
    explicit Mutex();
    virtual ~Mutex();
    void lock();
    void unlock();
};


#endif //OS3_MUTEX_H
