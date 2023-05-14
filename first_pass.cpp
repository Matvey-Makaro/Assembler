//
// Created by matvey on 5/13/23.
//

#include "first_pass.h"

#include <cassert>
#include <variant>
#include <string>
#include <utility>
using namespace std;

FirstPass::FirstPass(LexemeTable &lexeme_table, NameTable &name_table, LiteralTable &literal_table,
                     RowToCommandSize &row_to_command_size, size_t start_address) :
        _lexeme_table(lexeme_table), _name_table(name_table), _literal_table(literal_table),
        _row_to_command_size(row_to_command_size), _lex_id{0}, _address{start_address}
{ }

void FirstPass::start()
{
    for(_line_num = 0; _line_num < _lexeme_table.size(); _line_num++)
    {
        _lex_id = 0;
        process_line();
    }
}

size_t FirstPass::get_programm_size() const
{
    return _address;
}

size_t FirstPass::get_start_text_address() const
{
    return _start_text_address;
}

void FirstPass::process_line()
{
    auto& start_lex = get_curr_lex();

    if(start_lex.type == LexemeType::IDENTIFIER)
        process_decl_identifier();
    else if(start_lex.value == LexemeValue::MOV)
        process_mov();
    else if(start_lex.value == LexemeValue::SYSCALL)
        process_syscall();
    else if(start_lex.value == LexemeValue::INT)
        process_int();
    else assert(0);
}

void FirstPass::process_decl_identifier()
{
    auto& identifier = get_curr_lex();
    go_to_next_lex();
    auto& lex = get_curr_lex();
    assert(lex.type == LexemeType::DECLARATION_MNEMONIC);
    go_to_next_lex();

    auto& table_name_item = get_var(identifier);

    switch (lex.value)
    {
        case LexemeValue::DB:
            table_name_item.size = BYTE_SIZE;
            table_name_item.type = IdentifierType::INITIALIZED;
            table_name_item.values = move(get_literals());
            break;
        default:
            assert(0);  // UNREACHABLE
    }
    table_name_item.address = _address;
    _address += table_name_item.size * table_name_item.values.size();
    _start_text_address = _address;
}

void FirstPass::process_mov()
{
    auto length = get_mov_length(get_curr_line());
    _address += length;
    _row_to_command_size[_line_num] = length;
}

void FirstPass::process_syscall()
{
    auto length = get_syscall_length();
    _address += length;
    _row_to_command_size[_line_num] = length;
}

void FirstPass::process_int()
{
    auto length = get_int_length();
    _address += length;
    _row_to_command_size[_line_num] = length;
}

void FirstPass::go_to_next_lex()
{
    _lex_id++;
}

std::vector<Lexeme> &FirstPass::get_curr_line()
{
    return _lexeme_table[_line_num];
}

Lexeme &FirstPass::get_curr_lex()
{
    return get_curr_line()[_lex_id];
}

NameTableItem &FirstPass::get_var(const Lexeme &lexeme)
{
    return get_name_table_item(_name_table, lexeme);
}

std::vector<int64_t> FirstPass::get_literals()
{
    std::vector<int64_t> result;
    auto& line = get_curr_line();
    while(_lex_id < line.size())
    {
        auto& literal = get_curr_lex();
        assert(literal.type == LexemeType::LITERAL);

        auto& literal_variant = get_literal(_literal_table, literal);
        if(std::holds_alternative<string>(literal_variant))
        {
            auto& str = get<string>(literal_variant);
            for(const char ch : str)

                result.push_back(static_cast<int64_t>(ch));

        }
        else result.push_back(get<int64_t>(literal_variant));

        go_to_next_lex();

        if(_lex_id < line.size())
        {
            assert(get_curr_lex().value == LexemeValue::COMMA);
            go_to_next_lex();
        }
        else break;
    }

    return result;
}

size_t FirstPass::get_mov_length(const std::vector<Lexeme>& line)
{
    size_t size = 1;
    if(is_dword_register(line[1].value))
    {
        if(line[3].type == LexemeType::LITERAL || line[3].type == LexemeType::IDENTIFIER)
            size += 4;
    }


    return size;
}

size_t FirstPass::get_syscall_length()
{
    return 2;
}

size_t FirstPass::get_int_length()
{
    return 2;
}


