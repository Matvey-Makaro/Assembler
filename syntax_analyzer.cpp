//
// Created by matvey on 5/13/23.
//

#include "syntax_analyzer.h"

void SyntaxAnalyzer::analyze()
{
    for(auto& line : _lexeme_table)
    {
        _line = line;
        analyze_line();
    }
}

void SyntaxAnalyzer::analyze_line()
{
    _lex_id = 0;
    if(_line[_lex_id].type == LexemeType::IDENTIFIER)
        analyze_decl_identifier();
}

void SyntaxAnalyzer::analyze_decl_identifier()
{
    auto& identifier = get_curr_lex();
    go_to_next_lex();
    auto& lex = get_curr_lex();


}

void SyntaxAnalyzer::go_to_next_lex()
{
    _lex_id++;
}

Lexeme &SyntaxAnalyzer::get_curr_lex()
{
    return _line[_lex_id];
}


