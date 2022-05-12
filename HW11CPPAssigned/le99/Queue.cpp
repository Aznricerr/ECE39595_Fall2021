#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <iostream>

#include "Queue.h"

Queue::Queue(int cap) : capacity(cap) {}

Queue::~Queue() {}

void Queue::put(int element)
{
   std::unique_lock<std::mutex> lck(mtx);
   while (capacity == size)
      cv.wait(lck);
   queueEntries.push_back(element);
   size++;
   puts++;
   cv.notify_all();
}

int Queue::get()
{
   std::unique_lock<std::mutex> lck(mtx);
   while (size == 0)
      cv.wait(lck);
   cv.notify_all();
   if (!queueEntries.empty())
   {
      int v = queueEntries.front();
      queueEntries.pop_front();
      size--;
      takes++;
      return v;
   }
   else
   {
      return 0;
   }
}

int Queue::getTakes()
{
   return takes;
}

int Queue::getPuts()
{
   return puts;
}
