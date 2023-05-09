#pragma once

#include "common.h"

#include <string>

class Assembler
{
public:
    explicit Assembler(std::string fname);

    void assemble();
private:
    std::string _fname;

    LexemeTable _lexeme_table;
    NameTable _name_table;
    NameToID _name_to_id;
    RowToCommandSize _row_to_command_size;
    LiteralTable _literal_table;
    IntegerToID _integer_to_id;
    StrToID _str_to_id;


};


