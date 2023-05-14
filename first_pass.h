#pragma once

#include "common.h"


class FirstPass
{
public:
    FirstPass(LexemeTable &lexeme_table, NameTable &name_table, LiteralTable &literal_table,
              RowToAddress &row_to_address, size_t start_address);
    ~FirstPass() = default;

    FirstPass(FirstPass& other) = delete;
    FirstPass& operator=(FirstPass& other) = delete;

    FirstPass(FirstPass&& other) = delete;
    FirstPass& operator=(FirstPass&& other) = delete;

    void start();
    size_t get_programm_size() const;
    size_t get_start_text_address() const;

private:
    template<typename Func>
    void process_operation(Func get_length)
    {
        auto length = get_length();
        _address += length;
        _row_to_address[_line_num] = _address;
    }

    void process_line();
    void process_decl_identifier();
    void process_mov();
    void process_syscall();
    void process_int();
    void process_jmp();
    void process_jcc(); // jcc - jump id condition is met(ja, jg, jge, ...)
    void process_cmp();

    void go_to_next_lex();
    std::vector<Lexeme>& get_curr_line();
    Lexeme& get_curr_lex();
    NameTableItem& get_var(const Lexeme& lexeme);
    std::vector<int64_t> get_literals();

    size_t get_mov_length();
    size_t get_syscall_length();
    size_t get_int_length();
    size_t get_jmp_length();
    size_t get_jcc_length();
    size_t get_cmp_length();

private:
    LexemeTable& _lexeme_table;
    NameTable& _name_table;
    LiteralTable& _literal_table;
    RowToAddress& _row_to_address;


    uint64_t _line_num = 0;
    int _lex_id = 0;
    size_t _address;
    size_t _start_text_address;
};

