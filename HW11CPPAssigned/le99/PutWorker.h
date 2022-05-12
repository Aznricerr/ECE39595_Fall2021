#ifndef PUTWORKER_H_
#define PUTWORKER_H_
#include <list>
#include "Queue.h"

class PutWorker {

private:
   Queue& queue;

public:
   PutWorker(Queue& q);
   virtual ~PutWorker( );
   virtual void put(int trys);
};
#endif /* PUTWORKER_H_ */
