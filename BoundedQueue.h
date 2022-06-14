//
// Created by amiramyss on 6/8/22.
//

#ifndef OS3_BOUNDEDQUEUE_H
#define OS3_BOUNDEDQUEUE_H


#include <queue>
#include <string>
#include <semaphore.h>

class BoundedQueue : public std::queue<std::string>{
private:
    pthread_mutex_t _lock;
    sem_t _empty, _full;
    unsigned int _capacity;
public:
    BoundedQueue(unsigned int capacity);
    BoundedQueue();
    void push(std::string);
    std::string pop();

    std::string top();
};


#endif //OS3_BOUNDEDQUEUE_H
