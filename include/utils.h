#ifndef UTILS_H
#define UTILS_H

#include <iostream>
using namespace std;

class Timer
{
    private:
        int start_time;
        int end_time;
    public:
        Timer(int start_time=0) {this->end_time = start_time;}

        void increment() { end_time++; }

        bool isComplete(int countdown) { return end_time == start_time + countdown; }

        int getEndTime()   {return end_time;}

        int getStartTime()  {return start_time;}
};




#endif