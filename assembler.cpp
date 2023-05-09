//
// Created by matvey on 5/8/23.
//

#include "assembler.h"
#include "lexical_analyzer.h"

#include <utility>
#include <stdio.h>
#include <stdexcept>
using namespace std;

Assembler::Assembler(std::string fname) :
    _fname(move(fname))
{

}

void Assembler::assemble()
{
    FILE* file = fopen(_fname.c_str(), "r");
    if(file == nullptr)
        throw runtime_error("File " + _fname + " doesn't open!");

    LexicalAnalyzer lex_analyzer(file, _lexeme_table, _name_table, _name_to_id, _literal_table,
                                 _integer_to_id, _str_to_id);
    lex_analyzer.analyze();

    double delete_later = 0;
}
