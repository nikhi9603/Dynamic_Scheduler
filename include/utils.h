#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "instruction.h"
using namespace std;

struct Timer
{
    int start_time;
    int end_time;

    Timer() {start_time = -1; end_time = -1;} 
};

class Counter
{
    private:
        int cur_count;
    public:
        Counter() {cur_count = 0;}
        void increment() { cur_count++; }
        int getCurrentValue()  {return cur_count;}
};

// based on their ROB tag (ascending order)
bool InstructionTagComparator(Instruction instr1, Instruction instr2);

#endif