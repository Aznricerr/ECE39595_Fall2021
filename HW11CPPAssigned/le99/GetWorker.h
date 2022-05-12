#ifndef GETWORKER_H_
#define GETWORKER_H_
#include "Queue.h"

class GetWorker {

private:
   Queue& queue;

public:
   GetWorker(Queue& q);
   virtual ~GetWorker( );
   virtual void get(int trys);
};
#endif /* GETWORKER_H_ */
