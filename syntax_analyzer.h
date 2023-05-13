#pragma once

#include "common.h"

class SyntaxAnalyzer
{
public:
    SyntaxAnalyzer(std::string fname, LexemeTable& lexeme_table, NameTable& name_table, LiteralTable& literal_table);
    ~SyntaxAnalyzer() = default;

    SyntaxAnalyzer(SyntaxAnalyzer& other) = delete;
    SyntaxAnalyzer& operator=(SyntaxAnalyzer& other) = delete;

    SyntaxAnalyzer(SyntaxAnalyzer&& other) = delete;
    SyntaxAnalyzer& operator=(SyntaxAnalyzer&&) = delete;

    void analyze();

private:
    void analyze_line();
    void analyze_decl_identifier();

    void go_to_next_lex();
    Lexeme& get_curr_lex();

private:
    LexemeTable& _lexeme_table;
    NameTable& _name_table;
    LiteralTable& _literal_table;

    std::string _fname;
    std::vector<Lexeme>& _line;
    int _lex_id;
};


