#ifndef QUEUE_H_
#define QUEUE_H_
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>

class Queue
{

private:
    std::mutex mtx;
    std::condition_variable cv;
    std::list<int> queueEntries;
    int size = 0;
    int capacity;
    int takes = 0;
    int puts = 0;

public:
    Queue(int cap);
    virtual ~Queue();
    virtual void put(int element);
    virtual int get();
    virtual int getTakes();
    virtual int getPuts();
};
#endif /* QUEUE_H_ */
