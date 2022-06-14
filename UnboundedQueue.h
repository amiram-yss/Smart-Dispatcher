//
// Created by amiramyss on 6/14/22.
//

#ifndef OS3_UNBOUNDEDQUEUE_H
#define OS3_UNBOUNDEDQUEUE_H
#include <queue>
#include <string>
#include <semaphore.h>

class UnboundedQueue : public std::queue<std::string>{
private:
    pthread_mutex_t _lock;
    sem_t _full;
public:
    UnboundedQueue();

    std::string pop();

    void push(std::string str);

    std::string top();
};


#endif //OS3_UNBOUNDEDQUEUE_H
