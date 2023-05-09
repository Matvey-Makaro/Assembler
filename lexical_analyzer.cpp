//
// Created by matvey on 5/8/23.
//

#include "lexical_analyzer.h"

#include <utility>
#include <stdexcept>
using namespace std;


LexicalAnalyzer::LexicalAnalyzer(FILE* file, LexemeTable &lexeme_table, NameTable &name_table, NameToID &name_to_id,
                                 LiteralTable &literal_table, IntegerToID &integer_to_id, StrToID &str_to_id)
        : _file(file), _lexeme_table(lexeme_table), _name_table(name_table), _name_to_id(name_to_id),
          _literal_table(literal_table), _integer_to_id(integer_to_id), _str_to_id(str_to_id)
{
    _lexeme_table.emplace_back();
}

void LexicalAnalyzer::analyze()
{
    readch();
    while(true)
    {
        if(_state == States::START)
            start_state();
        else if(_state == States::ID_OR_KEY_WORD)
            id_or_key_word_state();
        else if(_state == States::NUM)
            num_state();
        else if(_state == States::DELIMITER)
            delimiter_state();
        else if(_state == States::STRING)
            string_state();
        else if(_state == States::COMMENT)
            comment_state();
        else if(_state == States::END)
        {
            while(_lexeme_table.back().empty())
                _lexeme_table.pop_back();
            return;
        }
    }
}

void LexicalAnalyzer::start_state()
{
    while(isspace(_ch))
        readch();

    if(isalpha(_ch) || _ch == '_')
        _state = States::ID_OR_KEY_WORD;
    else if(isdigit(_ch) || _ch == '+' || _ch == '-')
        _state = States::NUM;
    else if(is_delimiter(_ch))
        _state = States::DELIMITER;
    else if(_ch == '\"')
        _state = States::STRING;
    else if(_ch == ';')
        _state = States::COMMENT;
    else if(is_eof(_ch))
        _state = States::END;
}

void LexicalAnalyzer::id_or_key_word_state()
{
    clear_buff();
    while(isalnum(_ch) || _ch == '_')
    {
        _buff += _ch;
        readch();
    }

    auto key_words_it = key_words.find(_buff);
    if(key_words_it != end(key_words))
    {
        auto lexeme_value = key_words_it->second;
        add_lexeme(lexeme_value);
    } else if(_name_to_id.count(_buff) == 0)
    {
        add_identifier_name(move(_buff));
        auto id = _name_table.size() - 1;
        add_lexeme(LexemeType::IDENTIFIER, id);
    }
    else add_lexeme(LexemeType::IDENTIFIER, _name_to_id[_buff]);

    _state = States::START;
}

void LexicalAnalyzer::num_state()
{
    clear_buff();
    if(_ch == '+' || _ch == '-')
    {
        _buff += _ch;
        readch();
    }
    while(isdigit(_ch))
    {
        _buff += _ch;
        readch();
    }

    if(!isspace(_ch) && _ch != ',')
    {
        _error_description = "Wrong characters after a number";
        _state = States::ERR;
    }

    int64_t num;
    try
    {
        num = stoll(_buff);
    }
    catch(std::invalid_argument&)
    {
        _error_description = "Wrong number";
        _state = States::ERR;
    }
    catch(std::out_of_range&)
    {
        _error_description = "Number out or range";
        _state = States::ERR;
    }

    auto _integer_to_id_it = _integer_to_id.find(num);
    if(_integer_to_id_it == end(_integer_to_id))
    {
        add_integer_to_literal_table(num);
        auto id = _integer_to_id.size() - 1;
        add_lexeme(LexemeType::LITERAL, id);
    }
    else add_lexeme(LexemeType::LITERAL, _integer_to_id_it->second);

    _state = States::START;
}

void LexicalAnalyzer::delimiter_state()
{
    add_lexeme(str_to_delimiters.at(_ch + string("")));
    readch();
    _state = States::START;
}

void LexicalAnalyzer::string_state()
{

}

void LexicalAnalyzer::comment_state()
{
    while(_ch != '\n' && !is_eof(_ch))
        readch();
    _state = States::START;
}

void LexicalAnalyzer::readch()
{
    if(_ch == '\n')
    {
        _line_num += 1;
        _col_num = 0;
        _lexeme_table.emplace_back();
    }
    else _col_num++;
    _ch = fgetc(_file);
}

void LexicalAnalyzer::clear_buff()
{
    _buff = "";
}

void LexicalAnalyzer::add_lexeme(LexemeType type, LexemeValue value, int64_t id, size_t size)
{
    auto& curr_line = _lexeme_table.back();
    curr_line.emplace_back(type, value, id, size, _line_num, _col_num);
}

void LexicalAnalyzer::add_lexeme(LexemeValue value, int64_t id, size_t size)
{
    add_lexeme(get_lexeme_type(value), value, id, size);
}

void LexicalAnalyzer::add_lexeme(LexemeType type, int64_t id, size_t size)
{
    add_lexeme(type, LexemeValue::UNDEFINED, id, size);
}

void LexicalAnalyzer::add_identifier_name(std::string name)
{
    _name_table.emplace_back(move(name));
    auto index = _name_table.size() - 1;
    _name_to_id[_name_table[index].name] = index;
}

void LexicalAnalyzer::add_integer_to_literal_table(int64_t num)
{
    _literal_table.emplace_back(num);
    auto id = _literal_table.size() - 1;
    _integer_to_id[num] = id;
}

