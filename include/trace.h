#ifndef TRACE_H
#define TRACE_H

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

struct TraceEntry
{
    long long int PC;
    int operation_type;
    int src_reg1, src_reg2;
    int dest_reg;
};


class TraceFileParser
{
    private:
        string traceFileName;
        ifstream traceFile;
    public:
        TraceFileParser(string fileName);

        /*
         * @return pair<bool,TraceEntry> bool = true => EOF, bool = false => parsed successfully and returns next trace entry
         */
        pair<bool,TraceEntry> parseNextInstruction();   
};

#endif