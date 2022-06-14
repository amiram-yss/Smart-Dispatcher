#include <iostream>
#include "BoundedQueue.h"

int main() {
    auto *bq = new BoundedQueue(5);
    bq->push("hi1");
    bq->push("hi2");
    bq->push("hi3");
    bq->push("hi4");
    bq->push("hi5");
    std::cout << bq->pop() << std::endl;
    std::cout << bq->pop() << std::endl;
    std::cout << bq->pop() << std::endl;
    return 0;
}
