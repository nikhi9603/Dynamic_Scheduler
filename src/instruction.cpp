#include"instruction.h"

Instruction::Instruction(int instr_num)
{
    operation_type = -1;
    src_reg1 = -1;
    src_reg2 = -1;
    dest_reg = -1;
    instr_stage = IF; 
    ROB_tag = -1;
    instr_number = instr_num;

    timers[IF] = Timer();
    timers[ID] = Timer();
    timers[IS] = Timer();
    timers[EX] = Timer();
    timers[WB] = Timer();
}

void Instruction::print()
{
    cout << instr_number << " ";
    cout << "fu{" << operation_type << "} ";
    cout << "src{" << src_reg1 << ", " << src_reg2 << "} ";
    cout << "dst{" << dest_reg << "} ";
    cout << "IF{" << timers[IF].start_time << "," << timers[IF].end_time - timers[IF].start_time << "} ";
    cout << "ID{" << timers[ID].start_time << "," << timers[ID].end_time - timers[ID].start_time << "} ";
    cout << "IS{" << timers[IS].start_time << "," << timers[IS].end_time - timers[IS].start_time << "} ";
    cout << "EX{" << timers[EX].start_time << "," << timers[EX].end_time - timers[EX].start_time << "} ";
    cout << "WB{" << timers[WB].start_time << "," << timers[WB].end_time - timers[WB].start_time << "}" << endl;
}