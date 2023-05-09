#include "assembler.h"

#include <iostream>
#include <string>
using namespace std;

int main()
{
    std::string fname = "test.asm";
    Assembler assembler(fname);
    assembler.assemble();
}
