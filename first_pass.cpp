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
                     RowToAddress &row_to_address, size_t start_address) :
        _lexeme_table(lexeme_table), _name_table(name_table), _literal_table(literal_table),
        _row_to_address(row_to_address), _lex_id{0}, _address{start_address}
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
    else if(start_lex.value == LexemeValue::JMP)
        process_jmp();
    else if(is_jcc(start_lex.value))
        process_jcc();
    else if(start_lex.value == LexemeValue::CMP)
        process_cmp();
    else if(start_lex.value == LexemeValue::ADD)
        process_add();
    else assert(0);
}

void FirstPass::process_decl_identifier()
{
    auto& identifier = get_curr_lex();
    go_to_next_lex();
    auto& lex = get_curr_lex();
    assert(lex.type == LexemeType::DECLARATION_MNEMONIC || lex.value == LexemeValue::COLON);
    go_to_next_lex();

    auto& table_name_item = get_var(identifier);

    if(lex.value == LexemeValue::DB)
    {
        identifier.value = LexemeValue::INITIALIZED_IDENTIFIER;
        table_name_item.size = BYTE_SIZE;
        table_name_item.type = IdentifierType::INITIALIZED;
        table_name_item.values = move(get_literals());
    }
    else if(lex.value == LexemeValue::COLON)
    {
        identifier.value = LexemeValue::LINK;
        table_name_item.size = QWORD_SIZE;
        table_name_item.type = IdentifierType::LINK;
        table_name_item.values.push_back(_address);
        table_name_item.address = _address;
        return;
    }

    table_name_item.address = _address;
    _address += table_name_item.size * table_name_item.values.size();
    _start_text_address = _address;
}

void FirstPass::process_mov()
{
    process_operation([this](){
        return get_mov_length();
    });
}

void FirstPass::process_syscall()
{
    process_operation([this](){
        return get_syscall_length();
    });
}

void FirstPass::process_int()
{
    process_operation([this](){
        return get_int_length();
    });
}

void FirstPass::process_jmp()
{
    process_operation([this](){
        return get_jmp_length();
    });
}

void FirstPass::process_jcc()
{
    process_operation([this](){
        return get_jcc_length();
    });
}

void FirstPass::process_cmp()
{
    process_operation([this](){
        return get_cmp_length();
    });
}

void FirstPass::process_add()
{
    process_operation([this](){
        return get_add_length();
    });
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

size_t FirstPass::get_mov_length()
{
    auto& line = get_curr_line();
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

size_t FirstPass::get_jmp_length()
{
    return 5;
}

size_t FirstPass::get_jcc_length()
{
    return 6;
}

size_t FirstPass::get_cmp_length()
{
    auto& line = get_curr_line();
    size_t size = 2;
    if(is_dword_register(line[1].value))
    {
        if(line[3].type == LexemeType::LITERAL)
            size += 4;
    }


    return size;
}

size_t FirstPass::get_add_length()
{
    auto& line = get_curr_line();
    size_t size = 2;
    if(is_dword_register(line[1].value))
    {
        if(line[3].type == LexemeType::LITERAL)
            size += 4;
    }


    return size;
}




