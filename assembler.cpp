//
// Created by matvey on 5/8/23.
//

#include "assembler.h"
#include "lexical_analyzer.h"

#include <utility>
#include <iostream>
#include <stdexcept>
using namespace std;

Assembler::Assembler(std::string fname) :
    _fname(move(fname))
{

}

void Assembler::assemble()
{
    try
    {
        LexicalAnalyzer lex_analyzer(_fname, _lexeme_table, _name_table, _name_to_id, _literal_table,
                                     _integer_to_id, _str_to_id);
        lex_analyzer.analyze();
    }
    catch(exception& ex)
    {
        cerr << ex.what() << endl;
    }

    double delete_later = 0;
}
