#include "instruction.h"
#include "utils.h"
#include<algorithm>

unordered_map<int, int> execution_latency = {{0,1}, {1,2}, {2,10}};

bool InstructionTagComparator::operator()(int idx1, int idx2)
{
    if(rob_list->at(idx1).ROB_tag > rob_list->at(idx2).ROB_tag)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool InstructionExecutionTimeComparator::operator()(int idx1, int idx2)
{
    int finishTime1, finishTime2;
    Instruction i1 = rob_list->at(idx1);
    Instruction i2 = rob_list->at(idx2);
    
    finishTime1 = i1.timers[EX].start_time + execution_latency[i1.operation_type];
    finishTime2 = i2.timers[EX].start_time + execution_latency[i2.operation_type];

    if(finishTime1 > finishTime2)       
    {
        return true;
    }
    else if(finishTime1 == finishTime2)
    {
        return i1.ROB_tag > i2.ROB_tag;
    }
    else    
    {
        return false;
    }
}


bool IssueListInstructionComparator::operator()(IssueListEntry i1, IssueListEntry i2)
{
    // if both src1, src2 ready - higher priority for lower rob tag
    // higher priority at the end
    bool i1_ready = i1.src1_ready && i1.src2_ready;
    bool i2_ready = i2.src1_ready && i2.src2_ready;

    if(i1_ready && i2_ready)
    {
        return rob_list->at(i1.instr_rob_index).ROB_tag > rob_list->at(i2.instr_rob_index).ROB_tag;
    }
    else if(i1_ready)
    {
        return false;
    }
    else if(i2_ready)
    {
        return true;
    }
    else
    {
        return rob_list->at(i1.instr_rob_index).ROB_tag > rob_list->at(i2.instr_rob_index).ROB_tag;
    }
}


IssueList::IssueList(int capacity, vector<Instruction>* ROB_list, RegisterFile* registerFile)
{
    this->capacity = capacity;
    size = 0;
    rob_list = ROB_list;
    this->registerFile = registerFile;
}


bool IssueList::addInstruction(int instr_rob_idx)
{
    if(size < capacity)
    {
        IssueListEntry i = IssueListEntry(instr_rob_idx);
        int r1 = rob_list->at(instr_rob_idx).src_reg1;
        int r2 = rob_list->at(instr_rob_idx).src_reg2;
        int dest_reg = rob_list->at(instr_rob_idx).dest_reg;
        
        // R1
        if(r1 != -1)
        {
            if(registerFile->registers[r1].inRF_bit == 1)    // available
            {
                i.src1_ready = true;
                i.src1_tag = -1;        // since val is not considered in simulator
            }
            else
            {
                i.src1_ready = false;
                i.src1_tag = registerFile->registers[r1].ROB_tag;
            }
        }
        else
        {
            i.src1_ready = true;
            i.src1_tag = -1;
        }

        // R2
        if(r2 != -1)
        {
            if(registerFile->registers[r2].inRF_bit == 1)    // available
            {
                i.src2_ready = true;
                i.src2_tag = -1;        // since val is not considered in simulator
            }
            else
            {
                i.src2_ready = false;
                i.src2_tag = registerFile->registers[r2].ROB_tag;
            }
        }
        else
        {
            i.src2_ready = true;
            i.src2_tag = -1;
        }
        
        // destination operand
        if(dest_reg != -1)
        {
            registerFile->registers[dest_reg].inRF_bit = 0;
            registerFile->registers[dest_reg].ROB_tag = rob_list->at(instr_rob_idx).ROB_tag;
        }

        issue_list.push_back(i);
        size++;
        return true;
    }
    else
    {
        return false;
    }
}


void IssueList::updateReadyValues(vector<int> rob_tags)
{
    if(rob_tags.size() != 0)
    {
        for(int i = 0; i < size; i++)
        {
            if(!issue_list[i].src1_ready)
            {
                if(find(rob_tags.begin(), rob_tags.end(), issue_list[i].src1_tag) != rob_tags.end())
                {
                    issue_list[i].src1_ready = true;
                    issue_list[i].src1_tag = -1;
                }
            }

            if(!issue_list[i].src2_ready)
            {
                if(find(rob_tags.begin(), rob_tags.end(), issue_list[i].src2_tag) != rob_tags.end())
                {
                    issue_list[i].src2_ready = true;
                    issue_list[i].src2_tag = -1;
                }
            }
        }
    }
}


vector<int> IssueList::getNReadyInstructions(int N)
{
    vector<int> result;

    sort(issue_list.begin(), issue_list.end(), IssueListInstructionComparator(rob_list));

    int temp_size = size;
    for(int i = temp_size-1; i >= 0; i--)
    {
        if(issue_list[i].src1_ready && issue_list[i].src2_ready && result.size() < N)
        {
            result.push_back(issue_list[i].instr_rob_index);
            issue_list.pop_back();
            size--;
        }
        else
        {
            break;
        }
    }
    return result;
}