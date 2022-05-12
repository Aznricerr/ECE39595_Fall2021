#include <memory>
#include <vector>
#include "Command.h"
using namespace std;

class WorkQueue
{
private:
    vector<std::shared_ptr<Command>> queue;

public:
    WorkQueue();
    void put(shared_ptr<Command>);
    shared_ptr<Command> get();
};