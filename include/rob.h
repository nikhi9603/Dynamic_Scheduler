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
        vector<bool> isValid_list;

    public:
        vector<Instruction> rob_list;
        ROB(int capacity=4096);

        bool isFull();
        bool isEmpty();
        bool isValidEntry(int idx);

        pair<bool,int> addInstruction(Instruction instr);
        void retireInstructions();
};


#endif