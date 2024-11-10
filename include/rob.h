#ifndef ROB_H
#define ROB_H

#include "utils.h"
#include "instruction.h"
#include<vector>

class ROB 
{
    private:
        int size,capacity;
        int head, tail;
        Counter tag_counter;

        bool isValidEntry(int idx);
    public:
        vector<Instruction> rob_list;
        ROB(int capacity);

        bool isFull();
        bool isEmpty();

        bool addInstruction(Instruction instr);
        pair<bool,Instruction> retireInstruction(Instruction instr);
};


#endif