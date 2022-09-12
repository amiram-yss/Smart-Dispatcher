//
// Created by amiramyss on 8/2/22.
//

#ifndef OS3_SEMAPHORE_H
#define OS3_SEMAPHORE_H


#include <semaphore.h>
#include <iostream>

class Semaphore {
private:
    sem_t _lock;
    long long _value;
public:
    /**
     * Delete copy constructors.
     */
    Semaphore(const Semaphore&) = delete;

    /**
     * = operator overload
     * @return
     */
    Semaphore operator=(const Semaphore&) = delete;

    /**
     * Constructor.
     * @param value initialized value.
     */
    Semaphore(long long value = 0);

    /**
     * Decrease semaphore val by 1. If already 0, waits until raises.
     */
    void wait();
    /**
     * Raise val by 1.
     */
    void post();

    /**
     * Destructor.
     */
    ~Semaphore();
};


#endif //OS3_SEMAPHORE_H
