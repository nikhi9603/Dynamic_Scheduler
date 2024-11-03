#include"instruction.h"

void Instruction::print()
{
    cout << instr_number << " ";
    cout << "fu{" << operation_type << "} ";
    cout << "src{" << src_reg1 << ", " << src_reg2 << "} ";
    cout << "dst{" << dest_reg << "} ";
    cout << "IF{" << timers[IF].getStartTime() << "," << timers[IF].getEndTime() << "} ";
    cout << "ID{" << timers[ID].getStartTime() << "," << timers[ID].getEndTime() << "} ";
    cout << "IS{" << timers[IS].getStartTime() << "," << timers[IS].getEndTime() << "} ";
    cout << "EX{" << timers[EX].getStartTime() << "," << timers[EX].getEndTime() << "} ";
    cout << "WB{" << timers[WB].getStartTime() << "," << timers[WB].getEndTime() << "}" << endl;
}