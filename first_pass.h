#pragma once

#include "common.h"


class FirstPass
{
public:
    FirstPass(LexemeTable& lexeme_table, NameTable& name_table, LiteralTable& literal_table,
              RowToCommandSize& row_to_command_size);
    ~FirstPass() = default;

    FirstPass(FirstPass& other) = delete;
    FirstPass& operator=(FirstPass& other) = delete;

    FirstPass(FirstPass&& other) = delete;
    FirstPass& operator=(FirstPass&& other) = delete;

    void start();
    size_t get_programm_size() const;

private:
    void process_line();
    void process_decl_identifier();
    void process_mov();
    void process_syscall();
    void process_int();

    void go_to_next_lex();
    std::vector<Lexeme>& get_curr_line();
    Lexeme& get_curr_lex();
    NameTableItem& get_var(const Lexeme& lexeme);
    std::vector<int64_t> get_literals();

    size_t get_mov_length(const std::vector<Lexeme>& line);
    size_t get_syscall_length();
    size_t get_int_length();

private:
    LexemeTable& _lexeme_table;
    NameTable& _name_table;
    LiteralTable& _literal_table;
    RowToCommandSize& _row_to_command_size;


    uint64_t _line_num = 0;
    int _lex_id = 0;
    size_t _address = 0;
};

