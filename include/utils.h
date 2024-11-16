#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include<vector>
#include<unordered_map>
#include<set>
#include "register_file.h"
using namespace std;

extern unordered_map<int, int> execution_latency;

struct Timer
{
    int start_time;
    int end_time;

    Timer() {start_time = -1; end_time = -1;} 
};

struct Instruction;

class Counter
{
    private:
        int cur_count;
    public:
        Counter() {cur_count = 0;}
        void increment() { cur_count++; }
        int getCurrentValue()  {return cur_count;}
};


struct IssueListEntry
{
    int instr_rob_index;
    int src1_tag;
    int src2_tag;
    bool src1_ready;
    bool src2_ready;

    IssueListEntry(int instr_rob_idx) {this->instr_rob_index = instr_rob_idx;}
};


// based on their ROB tag (ascending order)
struct InstructionTagComparator
{
    vector<Instruction>* rob_list;
    InstructionTagComparator(vector<Instruction>* ROB_list) : rob_list(ROB_list) {}

    bool operator()(int idx1, int idx2);
};


struct InstructionExecutionTimeComparator
{
    vector<Instruction>* rob_list;
    InstructionExecutionTimeComparator(vector<Instruction>* ROB_list) : rob_list(ROB_list) {}

    bool operator()(int idx1, int idx2);
};

struct IssueListInstructionComparator
{
    vector<Instruction>* rob_list;
    IssueListInstructionComparator(vector<Instruction>* ROB_list) : rob_list(ROB_list) {}

    bool operator()(IssueListEntry i1, IssueListEntry i2);
};


class IssueList
{
    private:
        int capacity;
        int size;
        vector<Instruction>* rob_list;
        RegisterFile* registerFile;
        vector<IssueListEntry> issue_list;
    public:
        IssueList(int capacity, vector<Instruction>* ROB_list, RegisterFile* registerFile);

        int getSize() {return size;}
        bool addInstruction(int instr_rob_idx);
        void updateReadyValues(vector<int> rob_tags);
        vector<int> getNReadyInstructions(int N);   // atmax N if possible
};


#endif