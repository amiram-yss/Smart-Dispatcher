//
// Created by amiramyss on 6/8/22.
//

#ifndef OS3_BOUNDEDQUEUE_H
#define OS3_BOUNDEDQUEUE_H


#include <queue>
#include <string>
#include <bits/semaphore.h>

class BoundedQueue : public std::queue<std::string>{
private:
    pthread_mutex_t _lock;
    sem_t _empty, _full;
public:
    explicit BoundedQueue(int);
    BoundedQueue();
    void push(std::string);
    std::string pop();
};


#endif //OS3_BOUNDEDQUEUE_H
