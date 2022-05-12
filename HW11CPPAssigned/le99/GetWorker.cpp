#include <iostream>
#include <thread>
#include <chrono>
#include "GetWorker.h"

GetWorker::GetWorker(Queue& q) : queue(q) { } 

GetWorker::~GetWorker( ) { } //std::cout << "~GetWorker" << std::endl << std::flush;}

void GetWorker::get(int trys) {
   for (int i=0; i<trys; i++) {
      int s = queue.get( );
      std::this_thread::sleep_for(std::chrono::milliseconds(s));
   }
}
