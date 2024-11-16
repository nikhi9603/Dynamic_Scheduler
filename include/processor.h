#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<iostream>
#include<vector>
#include<queue>
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
        ROB rob;
        Counter cycle_counter;
        int N, S;   // N - fetch & dispatch list capacity => but stored combinedly as dispatch_list size of 2N

        priority_queue<int, vector<int>, InstructionTagComparator> dispatch_list;        // stores indices of instructions in ROB 
        priority_queue<int, vector<int>, InstructionExecutionTimeComparator> execute_list;        // stores indices of instructions in ROB 
        IssueList issue_list;
    public:
        Processor(string traceFilename, int N, int S);

        void simulate();

        // These following function perform for min(capacity, n) instr
        void fetch(int n);
        void dispatch(int n);
        void issue();
        vector<int> execute();
        bool retire();
        void advance_cycle() {cycle_counter.increment();}

        void printConfiguration();
        void printResults();
};


#endif