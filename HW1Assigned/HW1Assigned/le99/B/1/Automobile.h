#ifndef AUTOMOBILE_H_
#define AUTOMOBILE_H_
#include <string>

class Automobile {
    private:
        int vehID;
        float miles;
        std::string mtnDate; //Last Maintenance Date

    public:
        Automobile(int, float, int, int, int);
        int getvehID();
        float getMiles();
        std::string getmtnDate();
};
#endif