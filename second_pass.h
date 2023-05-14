#pragma once

#include "common.h"

class SecondPass
{
public:
    SecondPass(size_t programm_size, LexemeTable& lexeme_table, NameTable& name_table, LiteralTable& literal_table,
               RowToCommandSize& row_to_command_size);
    ~SecondPass() = default;

    SecondPass(SecondPass& other) = delete;
    SecondPass& operator=(SecondPass& other) = delete;

    SecondPass(SecondPass&& other) = delete;
    SecondPass& operator=(SecondPass&& other) = delete;

    void start();
    std::vector<uint8_t> get_programm();

private:
    void process_line();

    void go_to_next_lex();
    std::vector<Lexeme>& get_curr_line();
    Lexeme& get_curr_lex();
    NameTableItem& get_var(const Lexeme& lexeme);

    void process_decl_identifier();
    void process_mov();
    void process_syscall();
    void process_int();

private:
    LexemeTable& _lexeme_table;
    NameTable& _name_table;
    LiteralTable& _literal_table;
    RowToCommandSize& _row_to_command_size;


    std::vector<uint8_t> _programm;
    uint64_t _line_num = 0;
    int _lex_id = 0;
};

