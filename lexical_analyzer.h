//
// Created by matvey on 5/8/23.
//

#pragma once

#include "common.h"

#include <fstream>

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
    LexicalAnalyzer(std::istream& in, LexemeTable& lexeme_table, NameTable& name_table, NameToID& name_to_id,
                    RowToCommandSize& row_to_command_size, LiteralTable literal_table,
                    IntegerToID& integer_to_id, StrToID& str_to_id);
    ~LexicalAnalyzer() = default;

    LexicalAnalyzer(const LexicalAnalyzer& other) = delete;
    LexicalAnalyzer& operator=(const LexicalAnalyzer& other) = delete;
    LexicalAnalyzer(LexicalAnalyzer&& other) = delete;
    LexicalAnalyzer& operator=(LexicalAnalyzer&& other) = delete;

    void analyze();

private:
    void readch();
    void start_state();
    void id_or_key_word_state();
    void num_state();
    void string_state();
    void delimiter_state();
    void comment_state();

    void clear_buff();

private:
    LexemeTable _lexeme_table;
    NameTable _name_table;
    NameToID _name_to_id;
    RowToCommandSize _row_to_command_size;
    LiteralTable _literal_table;
    IntegerToID _integer_to_id;
    StrToID _str_to_id;

    std::ifstream& _fin;
    char _ch = ' ';
    uint64_t  _line_num = 0;
    uint64_t  _col_num = 0;
    std::string _buff;
    std::string _line;
    int _line_index = 0;
    bool _is_eof = false;

    States _state = States::START;
};

