#include "processor.h"
#include<iomanip>

Processor::Processor(string traceFilename, int N, int S) 
: dispatch_list(InstructionTagComparator(&rob.rob_list)),
  execute_list(InstructionExecutionTimeComparator(&rob.rob_list)),
  issue_list(S, &rob.rob_list, &registerFile)
{
    trace_parser = new TraceFileParser(traceFilename);
    this->N = N;
    this->S = S;
}


void Processor::simulate()
{
    int dispatch_list_size, execute_list_size, issue_list_size;

    while(1)
    {
        dispatch_list_size = dispatch_list.size();
        execute_list_size = execute_list.size();
        issue_list_size = issue_list.getSize();

        if(retire() && cycle_counter.getCurrentValue() != 0)   break;
        execute();
        issue();
        dispatch(S-issue_list.getSize());
        fetch(2*N-dispatch_list_size);
        advance_cycle();
    }
}


void Processor::fetch(int n)
{
    int n_instr_fetch = min(N,n);

    if(!trace_parser->isEOF_Reached())
    {
        for(int i = 0; i < n_instr_fetch; i++)
        {
            pair<bool,TraceEntry> traceInstr = trace_parser->parseNextInstruction();

            if(!traceInstr.first)    //not EOF
            {
                Instruction i = Instruction(traceInstr.second.trace_index);
                i.dest_reg = traceInstr.second.dest_reg;
                i.src_reg1 = traceInstr.second.src_reg1;
                i.src_reg2 = traceInstr.second.src_reg2;
                i.operation_type = traceInstr.second.operation_type;
                
                // keeping stage as next stage: ID so that it needed not be updated in Dispatch phase by searching
                i.instr_stage = ID;
                i.timers[IF].start_time = cycle_counter.getCurrentValue();
                i.timers[IF].end_time = cycle_counter.getCurrentValue();
                i.timers[ID].start_time = cycle_counter.getCurrentValue() + 1;

                pair<bool,int> result = rob.addInstruction(i);
                if(result.first)
                {
                    dispatch_list.push(result.second);
                }
                else    // wont occur mp because rob size is 2048
                {
                    // not handling occuring case
                    // if occured, the parse instruction I need to store and add to rob in next possible cycle 
                    // when rob is having empty slot
                    cout << "CURRENT ROB HOLDS 4096 INSTRUCTIONS. INCREASE IT MANUALLY IN THE PROGRAM AND RUN" << endl;
                    exit(1);
                    // break;   
                }
            }
            else
            {
                break;
            }
        }
    }
}


void Processor::dispatch(int n)
{
    int n_dispatch_instr = min(N, n);

    for(int i = 0; i < n_dispatch_instr; i++)
    {
        if(dispatch_list.size() != 0)
        {
            int idx = dispatch_list.top();
            bool result = issue_list.addInstruction(idx);

            if(result)
            {
                dispatch_list.pop();
                rob.rob_list[idx].instr_stage = IS;
                rob.rob_list[idx].timers[ID].end_time = cycle_counter.getCurrentValue();
                rob.rob_list[idx].timers[IS].start_time = cycle_counter.getCurrentValue()+1;
            }
            else    // wont happen because n_dispatch_instr = min(N, n);
            {
                // cout << "happened1" << endl;
                break;
            }
        }
        else
        {
            break;
        }
    }
}


void Processor::issue()
{
    int n_max_issue_instr = N;

    vector<int> ready_instr_indices = issue_list.getNReadyInstructions(n_max_issue_instr);

    for(int i = 0; i < ready_instr_indices.size(); i++)
    {
        rob.rob_list[ready_instr_indices[i]].instr_stage = EX;
        rob.rob_list[ready_instr_indices[i]].timers[IS].end_time = cycle_counter.getCurrentValue();
        rob.rob_list[ready_instr_indices[i]].timers[EX].start_time = cycle_counter.getCurrentValue() + 1;

        execute_list.push(ready_instr_indices[i]);
    }
}


vector<int> Processor::execute()
{
    vector<int> complete_instr_rob_tags;

    while(!execute_list.empty())
    {
        int idx = execute_list.top();

        // execution complete
        if(rob.rob_list[idx].timers[EX].start_time + execution_latency[rob.rob_list[idx].operation_type] - 1 == cycle_counter.getCurrentValue())
        {
            execute_list.pop();
            rob.rob_list[idx].instr_stage = WB;
            rob.rob_list[idx].timers[EX].end_time = cycle_counter.getCurrentValue();
            rob.rob_list[idx].timers[WB].start_time = cycle_counter.getCurrentValue()+1;

            complete_instr_rob_tags.push_back(rob.rob_list[idx].ROB_tag);

            // register file update
            int dest_reg = rob.rob_list[idx].dest_reg;
            if(registerFile.registers[dest_reg].inRF_bit == 0 && registerFile.registers[dest_reg].ROB_tag == rob.rob_list[idx].ROB_tag)
            {
                registerFile.registers[dest_reg].inRF_bit = 1;
                registerFile.registers[dest_reg].ROB_tag = -1;
            }
        }
        else    // they are arranged based on their finish times
        {
            break;
        }
    }

    issue_list.updateReadyValues(complete_instr_rob_tags);
    return complete_instr_rob_tags;
}


bool Processor::retire()
{
    rob.retireInstructions();       // TODO:: some doubt in ending time of wb
    return rob.isEmpty();
}


void Processor::printConfiguration()
{
    cout << "CONFIGURATION" << endl;
    cout << " superscalar bandwidth (N)\t= " << N << endl;
    cout << " dispatch queue size (2*N)\t= " << 2*N << endl;
    cout << " schedule queue size (S)\t= " << S << endl;
}


void Processor::printResults()
{
    int n_instr = trace_parser->getTraceCount();
    int n_cycles = cycle_counter.getCurrentValue() + 1 ;
    float ipc = (float) n_instr/n_cycles;

    cout << "RESULTS" << endl;
    cout << " number of instructions = " << n_instr << endl;
    cout << " number of cycles \t = " << n_cycles << endl;
    cout << "IPC \t\t = " << fixed << setprecision(2) << ipc << endl;
}