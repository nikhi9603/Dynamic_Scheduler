#include "rob.h"

ROB::ROB(int capacity)
{
    size = 0;
    this->capacity = capacity;
    head = 0;
    tail = 0;
    tag_counter = Counter();
    rob_list = vector<Instruction>(capacity, Instruction());
}


bool ROB::isValidEntry(int idx)
{
    if(idx >= 0 && idx < capacity)
    {
        if(size == 0)   return false;
        
        if(idx >= head && idx <= tail)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool ROB::isFull()
{
    if(size == capacity)    return true;
    else    return false;
}

bool ROB::isEmpty()
{
    if(size == 0)   return true;
    else    return false;
}


bool ROB::addInstruction(Instruction instr)
{
    if(isFull())    return false;
}