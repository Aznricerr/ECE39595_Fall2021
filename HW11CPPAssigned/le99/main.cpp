#include <iostream>
#include <thread>
#include <vector>

#include "PutWorker.h"
#include "GetWorker.h"
#include "Queue.h"

int main (int argc, char *argv[]) {
   int numThreads = 6;
   int trys = 100;
   int capacity = 5;

   std::vector<std::thread> threads;
   std::vector<PutWorker> putters;
   std::vector<GetWorker> getters;

   Queue queue(capacity); 

   for (int i = 0; i < numThreads; i++) {
      putters.push_back(PutWorker(queue));
      getters.push_back(GetWorker(queue));
      threads.push_back(std::thread(&PutWorker::put, putters[i], trys));
      threads.push_back(std::thread(&GetWorker::get, getters[i], trys));
   }

   for (int i = 0; i < numThreads*2; i++) {
      threads[i].join( );
   }

   std::cout << "takes: " << queue.getTakes( ) << ", puts: " << queue.getPuts( ) << std::endl;
}
