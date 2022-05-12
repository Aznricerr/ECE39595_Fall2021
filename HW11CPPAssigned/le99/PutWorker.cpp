#include <iostream>
#include "PutWorker.h"
#include "Queue.h"

PutWorker::PutWorker(Queue& q) : queue(q) { }

PutWorker::~PutWorker( ) { } //std::cout << "~PutWorker" << std::endl << std::flush;}

void PutWorker::put(int trys) {
   for (int i = 0; i < trys; i++) {
      queue.put(rand( )%50);
      std::this_thread::sleep_for(std::chrono::milliseconds(rand( )%50));
   }
}
