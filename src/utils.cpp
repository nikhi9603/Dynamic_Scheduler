#include "utils.h"

bool InstructionTagComparator(Instruction instr1, Instruction instr2)
{
    if(instr1.ROB_tag < instr2.ROB_tag)
    {
        return true;
    }
    else
    {
        return false;
    }
}