#include <iostream>
#include <chrono>
#include <memory>
#include <thread>
#include <mutex>

#include "QuickSort.h"
#include "WorkQueue.h"
#include "DotProduct.h"

#define NUMSORTS 4
#define STARTSIZE 8000

using namespace std::chrono;

void worker(WorkQueue workQ)
{
   std::shared_ptr<Command> c(workQ.get());
   while (c != nullptr)
   {
      c->execute();
      static mutex outputLock;
      std::lock_guard<std::mutex> lck(outputLock);
      (*c).identify();
      c = workQ.get();
   }
}

int main(int argc, char **args)
{
   WorkQueue workq = WorkQueue();
   int sortSize = STARTSIZE;

   for (int i = 0; i < NUMSORTS; i++)
   {
      std::shared_ptr<Command> di = std::make_shared<DotProduct>(sortSize);
      workq.put(di);
      di = std::make_shared<QuickSort>(sortSize);
      workq.put(di);
      sortSize *= 2;
   }

   auto start = high_resolution_clock::now();
   vector<thread> thread_vec;
   for (int i = 0; i < NUMSORTS; i++)
   {
      thread_vec.push_back(thread(worker, workq));
   }
   for (auto &tread : thread_vec)
   {
      tread.join();
   }

   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start).count();
   std::cout << "Execution time with 4 threads is " << duration << " microseconds\n\n";
}
