#include "assembler.h"

#include <iostream>
#include <string>


int main()
{
    std::string fname = "test.asm";
    Assembler assembler(fname);
    assembler.assemble();
}
