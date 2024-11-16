#include "rob.h"

ROB::ROB(int capacity)
{
    size = 0;
    this->capacity = capacity;
    head = 0;
    tail = 0;
    tag_counter = Counter();
    rob_list = vector<Instruction>(capacity, Instruction());
    isValid_list = vector<bool>(capacity, false);
}


bool ROB::isValidEntry(int idx)
{
    return isValid_list[idx];
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

// int indicates ROB index
pair<bool,int> ROB::addInstruction(Instruction instr)
{
    if(isFull())    return make_pair(false,-1);
    pair<bool, int> result;

    if(isEmpty())
    {
        head = 0;
        tail = 1;
        rob_list[0] = instr;
        rob_list[0].ROB_tag = tag_counter.getCurrentValue();
        isValid_list[0] = true;
        result.second = 0;

        tag_counter.increment();
        size++;
    }
    else
    {
        if(!isFull())
        {
            rob_list[tail] = instr;
            rob_list[tail].ROB_tag = tag_counter.getCurrentValue();
            isValid_list[tail] = true;
            result.second = tail;

            tail = (tail + 1) % capacity;
            tag_counter.increment();
            size++;
        }
        else
        {
            return make_pair(false,-1);
        }
    }

    result.first = true;
    return result;
}


void ROB::retireInstructions()
{
    while(!isEmpty())
    {
        if(rob_list[head].instr_stage == WB)
        {
            // TODO:: doubt? WB - current cycle counter end time?
            rob_list[head].timers[WB].end_time = rob_list[head].timers[WB].start_time ;  // 1 cycle  ??
            rob_list[head].print();
            isValid_list[head] = false;
            size--;
            head = (head + 1) % capacity;
        }
        else
        {
            break;
        }
    }
}