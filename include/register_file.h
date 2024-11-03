#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include<iostream>
#include<vector>
using namespace std;

struct Register
{
    int ROB_tag;
    int inRF_bit;

    Register() 
    { 
        ROB_tag = -1; 
        inRF_bit = 1;
    }
};

struct RegisterFile
{
    int reg_count;
    long long int PC;
    vector<Register> registers;

    RegisterFile(int register_count) 
    {
        this->reg_count = register_count; 
        registers = vector<Register>(register_count, Register());
    }
};

#endif