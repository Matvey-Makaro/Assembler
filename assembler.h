#pragma once

#include "common.h"

#include <string>

class Assembler
{
public:
    explicit Assembler(std::string in_fname, std::string out_fname);

    void assemble();
private:
    std::string _in_fname;
    std::string _out_fname;

    LexemeTable _lexeme_table;
    NameTable _name_table;
    NameToID _name_to_id;   // TODO: needed only in the lexical analyzer
    RowToAddress _row_to_address;
    LiteralTable _literal_table;
    IntegerToID _integer_to_id; // TODO: needed only in the lexical analyzer
    StrToID _str_to_id; // TODO: needed only in the lexical analyzer

    const size_t _start_address = 0x400078;

};


