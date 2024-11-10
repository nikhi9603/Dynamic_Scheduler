#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<iostream>
#include<vector>
#include "instruction.h"
#include "utils.h"
#include "register_file.h"
#include "trace.h"
#include "rob.h"
using namespace std;



class Processor
{
    private:
        TraceFileParser* trace_parser;
        RegisterFile registerFile;
        unordered_map<int, int> execution_latency;
        
        ROB rob;
        vector<Instruction> dispatch_list;
        vector<Instruction> execute_list;
        //Issue list - new structure with rob_index, src_tag1, src_tag2, src_ready1, src_ready2; 
    public:
};


#endif