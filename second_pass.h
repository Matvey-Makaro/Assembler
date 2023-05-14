#pragma once

#include "common.h"

class SecondPass
{
public:
    SecondPass(size_t programm_size, LexemeTable& lexeme_table, NameTable& name_table, LiteralTable& literal_table,
               RowToAddress& row_to_address);
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

    template<typename T>
    void add_num_to_programm(T val)
    {
        constexpr int SIZE_IN_BYTES = sizeof(val) * 8;
        for(int i = 0; i < SIZE_IN_BYTES; i += 8)
            _programm.push_back((val >> i) & 0xFF);
    }


    void process_decl_identifier();
    void process_mov();
    void process_syscall();
    void process_int();
    void process_jmp();
    void process_jcc();
    void process_cmp();

private:
    LexemeTable& _lexeme_table;
    NameTable& _name_table;
    LiteralTable& _literal_table;
    RowToAddress& _row_to_address;


    std::vector<uint8_t> _programm;
    uint64_t _line_num = 0;
    int _lex_id = 0;
};

