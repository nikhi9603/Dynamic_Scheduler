#include "processor.h"
#include<fstream>

int main(int argc, char* argv[])
{
    if(argc == 4)
    {
        int N = stoi(argv[1]);
        int S = stoi(argv[2]);
        string tracefileName = argv[3];

        Processor p = Processor(tracefileName, N, S);
        p.simulate();

        // fstream file;
        // file.open("sample_output.txt", ios::app);
        // cout.rdbuf(file.rdbuf());

        p.printConfiguration();
        p.printResults();

        // cout << "\n" << endl;
        // file.close();
    }
    else
    {
        cout << "Invalid arguments" << endl;
    }
    return 0;
}