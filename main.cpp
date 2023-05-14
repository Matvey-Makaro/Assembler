#include "assembler.h"

#include <iostream>
#include <string>
using namespace std;

int main()
{
    std::string fname = "test.asm";
//    std::string fname = "hello.asm";
//    std::string fname = "read_write.asm";
    Assembler assembler(fname);
    assembler.assemble();
}
