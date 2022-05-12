#include "WorkQueue.h"
#include <mutex>

WorkQueue::WorkQueue()
{
    vector<shared_ptr<Command>> queue = {};
}

void WorkQueue::put(shared_ptr<Command> p)
{
    static mutex m;
    lock_guard<mutex> lock(m);
    queue.push_back(p);
}

shared_ptr<Command> WorkQueue::get()
{
    static mutex m;
    lock_guard<mutex> lock(m);
    if (queue.empty())
    {
        return nullptr;
    }
    shared_ptr<Command> &temp = queue.front();
    queue.erase(queue.begin());
    return temp;
}