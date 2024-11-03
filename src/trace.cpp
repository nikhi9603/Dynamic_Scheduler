#include "trace.h"
#define TRACE_DIR_PATH "trace_files/"

TraceFileParser::TraceFileParser(string fileName)
{
    this->traceFileName = fileName;

    string traceFilePath = TRACE_DIR_PATH + traceFileName;
    traceFile.open(traceFilePath);

    if(!traceFile.is_open())
    {
        cerr << "Error in opening file - " << traceFilePath << endl;
    }
}


pair<bool,TraceEntry> TraceFileParser::parseNextInstruction()
{
    TraceEntry instr;
    bool isEOF = false;

    string s1;
    traceFile >> s1 >> instr.operation_type   >> instr.dest_reg >> instr.src_reg1 >> instr.src_reg2;

    if(traceFile.fail() && !traceFile.eof())
    {
        cerr << "Invalid input or formatting in trace file" << endl;
        exit(EXIT_FAILURE);
    }
    else if(traceFile.eof())
    {
        isEOF = true;
    }
    else
    {
        instr.PC = std::stoull(s1, nullptr, 16);
    }

    return make_pair(isEOF, instr);
}