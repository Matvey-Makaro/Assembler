//
// Created by matvey on 5/8/23.
//

#include "lexical_analyzer.h"
using namespace std;

void LexicalAnalyzer::analyze()
{
    readch();
    while(!_is_eof)
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
    }
}



void LexicalAnalyzer::readch()
{
    _line_index++;
    if(_line_index < _line.size())
    {
        getline(_fin, _line);
        if(_fin.eof())
            _is_eof = true;
        _line_index = 0;
    }

    _ch = _line[_line_index];
}

void LexicalAnalyzer::start_state()
{
    while(isspace(_ch))
        readch();

    if(isalpha(_ch) || _ch == '_')
        _state = States::ID_OR_KEY_WORD;
    else if(isdigit(_ch))
        _state = States::NUM;
    else if(is_delimiter(_ch))
        _state = States::DELIMITER;
    else if(_ch == '\"')
        _state = States::STRING;
    else if(_ch == ';')
        _state = States::COMMENT;
    else if(_is_eof)
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

}

void LexicalAnalyzer::clear_buff()
{
    _buff = "";
}
