#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include<iostream>
#include<unordered_map>
#include "utils.h"
using namespace std;

enum Instruction_Stage {IF, ID, IS, EX, WB};

struct Instruction
{
    int operation_type;
    int src_reg1;
    int src_reg2;
    int dest_reg;
    Instruction_Stage instr_stage;
    int ROB_tag;
    int instr_number;
    unordered_map<Instruction_Stage, Timer> timers;

    Instruction(int instr_num=-2);
    void print();
};

#endif