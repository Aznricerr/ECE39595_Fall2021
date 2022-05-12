#ifndef AUTOMOBILE_H_
#define AUTOMOBILE_H_
#include <string>

class Automobile {
    private:
        int vehID;
        float miles;
        int month; //Last Maintenance Date
        int day;
        int year;

    public:
        Automobile(int, float, int, int, int);
        int getvehID();
        float getMiles();
        int getMonth();
        int getDay();
        int getYear();
        std::string retString();
};
#endif