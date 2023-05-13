//
// Created by matvey on 5/8/23.
//

#pragma once

#include "common.h"

#include <stdio.h>

enum class States
{
    START,
    ID_OR_KEY_WORD,
    NUM,
    STRING,
    DELIMITER,
    COMMENT,
    ERR,
    END
};

class LexicalAnalyzer
{
public:
    LexicalAnalyzer(std::string fname, LexemeTable& lexeme_table, NameTable& name_table, NameToID& name_to_id,
                    LiteralTable& literal_table, IntegerToID& integer_to_id, StrToID& str_to_id);
    ~LexicalAnalyzer();

    LexicalAnalyzer(const LexicalAnalyzer& other) = delete;
    LexicalAnalyzer& operator=(const LexicalAnalyzer& other) = delete;
    LexicalAnalyzer(LexicalAnalyzer&& other) = delete;
    LexicalAnalyzer& operator=(LexicalAnalyzer&& other) = delete;

    void analyze();

private:
    void start_state();
    void id_or_key_word_state();
    void num_state();
    void string_state();
    void delimiter_state();
    void comment_state();
    void err_state();

    void readch();
    void clear_buff();
    void add_lexeme(LexemeType type, LexemeValue value, int64_t id = -1, size_t size = 0);
    void add_lexeme(LexemeValue value, int64_t id = -1, size_t size = 0);
    void add_lexeme(LexemeType type, int64_t id = -1, size_t size = 0);
    void add_identifier_name(std::string name);
    void add_to_literal_table(int64_t num);
    void add_to_literal_table(std::string str);

private:
    LexemeTable& _lexeme_table;
    NameTable& _name_table;
    NameToID& _name_to_id;
    LiteralTable& _literal_table;
    IntegerToID& _integer_to_id;
    StrToID& _str_to_id;

    std::string _fname;
    FILE* _file;
    char _ch = ' ';
    uint64_t  _line_num = 0;
    uint64_t  _col_num = 0;
    std::string _buff;

    States _state = States::START;

    std::string _error_description;
};

