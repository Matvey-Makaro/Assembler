#include "assembler.h"

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        cerr << "Incorrect parameters. The first argument is the name of the input file, the second argument is the name of the output file.";
        return -1;
    }

//    std::string in_fname = "test.asm";
//    std::string in_fname = "hello.asm";
//    std::string in_fname = "read_write.asm";
    std::string in_fname(argv[1]);
    std::string out_fname(argv[2]);
    Assembler assembler(in_fname, out_fname);
    assembler.assemble();
}
