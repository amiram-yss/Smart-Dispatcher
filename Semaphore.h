//
// Created by amiramyss on 8/2/22.
//

#ifndef OS3_SEMAPHORE_H
#define OS3_SEMAPHORE_H


#include <bits/semaphore.h>

class Semaphore {
private:
    sem_t _lock;
    unsigned long long _value;
public:
    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;

    Semaphore(long long value = 0);

    void wait();
    void post();

    ~Semaphore();
};


#endif //OS3_SEMAPHORE_H
