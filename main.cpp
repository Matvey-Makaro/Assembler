#include "assembler.h"

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        cerr << "Incorrect parameters. The first argument is the name of the input file, the second argument is the name of the output file.";
        return -1;
    }

    string in_fname(argv[1]);
    string out_fname(argv[2]);
    try
    {
        Assembler assembler(in_fname, out_fname);
        assembler.assemble();
    }
    catch(std::exception& ex)
    {
        cerr << ex.what() << endl;
    }
}
