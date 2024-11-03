#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<iostream>
#include<vector>
#include "instruction.h"
#include "utils.h"
#include "register_file.h"
#include "trace.h"
using namespace std;



class Processor
{
    private:
        TraceFileParser* trace_parser;
        RegisterFile registerFile;
        unordered_map<int, int> execution_latency;
        
        
    public:
};


#endif