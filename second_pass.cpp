//
// Created by matvey on 5/14/23.
//

#include "second_pass.h"

#include <cassert>

SecondPass::SecondPass(size_t programm_size, LexemeTable &lexeme_table, NameTable &name_table,
                       LiteralTable &literal_table, RowToAddress &row_to_address) :
        _lexeme_table(lexeme_table), _name_table(name_table), _literal_table(literal_table),
        _row_to_address(row_to_address)
{
    _programm.reserve(programm_size);
}

void SecondPass::start()
{
    for(_line_num = 0; _line_num < _lexeme_table.size(); _line_num++)
    {
        _lex_id = 0;
        process_line();
    }
}

std::vector<uint8_t> SecondPass::get_programm()
{
    return _programm;
}

void SecondPass::process_line()
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
    else assert(0);

}

void SecondPass::go_to_next_lex()
{
    _lex_id++;
}

std::vector<Lexeme> &SecondPass::get_curr_line()
{
    return _lexeme_table[_line_num];
}

Lexeme &SecondPass::get_curr_lex()
{
    return get_curr_line()[_lex_id];
}

NameTableItem &SecondPass::get_var(const Lexeme &lexeme)
{
    return get_name_table_item(_name_table, lexeme);
}

void SecondPass::process_decl_identifier()
{
    auto& identifier = get_curr_lex();
    auto& var = get_var(identifier);

    if(identifier.value == LexemeValue::LINK)
        return;

    if(var.size == 1)
    {
        uint8_t val;
        for(size_t i = 0; i < var.values.size(); i ++)
        {
            val = var.values[i];
            _programm.push_back(val);
        }
    }
    else assert(0);
}

void SecondPass::process_mov()
{
    auto& line = get_curr_line();
    assert(line[0].value == LexemeValue::MOV);

    if(line[3].type == LexemeType::IDENTIFIER || line[3].type == LexemeType::LITERAL)
    {
        if(is_dword_register(line[1].value))
        {
            if(is_additional_register(line[1].value))
            {
                uint8_t rex_prefix = 0b01000001;
                _programm.push_back(rex_prefix);
            }
            uint8_t opcode = 0xB8;
            opcode |= get_reg_code(line[1].value);
            _programm.push_back(opcode);

            uint32_t val = 0;
            if(line[3].type == LexemeType::IDENTIFIER)
                val = get_var(line[3]).address;
            else val =  std::get<int64_t>(get_literal(_literal_table, line[3]));

            add_num_to_programm(val);
        }
    }

}

void SecondPass::process_syscall()
{
    _programm.push_back(0x0f);
    _programm.push_back(0x05);
}

void SecondPass::process_int()
{
    auto& line = get_curr_line();
    _programm.push_back(0xcd);
    uint8_t val =  std::get<int64_t>(get_literal(_literal_table, line[1]));
    _programm.push_back(val);
}

void SecondPass::process_jmp()
{
    auto& line = get_curr_line();
    assert(line[0].value == LexemeValue::JMP);

    auto& var = get_var(line[1]);
    int64_t address;
    if(var.type == IdentifierType::LINK)
        address = var.address;
    else assert(0);
    int32_t displacement = address - _row_to_address[_line_num];

    _programm.push_back(0xe9);  // opcode
    add_num_to_programm(displacement);
}

void SecondPass::process_jcc()
{
    auto& line = get_curr_line();
    _programm.push_back(0x0F);  // first part of opcode
    _programm.push_back(jcc_to_opcode.at(line[0].value));   // second part of opcode

    auto& var = get_var(line[1]);
    int64_t address;
    if(var.type == IdentifierType::LINK)
        address = var.address;
    else assert(0);
    int32_t displacement = address - _row_to_address[_line_num];
    add_num_to_programm(displacement);
}

void SecondPass::process_cmp()
{
    auto& line = get_curr_line();
    assert(line[0].value == LexemeValue::CMP);

    if(line[3].type == LexemeType::IDENTIFIER || line[3].type == LexemeType::LITERAL)
    {
        if(is_dword_register(line[1].value))
        {
            if(is_additional_register(line[1].value))
            {
                uint8_t rex_prefix = 0b01000001;
                _programm.push_back(rex_prefix);
            }
            uint8_t opcode = 0x81;
            _programm.push_back(opcode);
            uint8_t mod_r_m = 0b11111000 | reg_to_code.at(line[1].value);
            _programm.push_back(mod_r_m);

            uint32_t val = 0;
            if(line[3].type == LexemeType::IDENTIFIER)
                val = get_var(line[3]).address;
            else val =  std::get<int64_t>(get_literal(_literal_table, line[3]));

            add_num_to_programm(val);
        }
    }
}

