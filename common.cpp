#include "common.h"

#include <ostream>
#include <cassert>
#include <stdexcept>
using namespace std;

bool is_delimiter(char ch)
{
    return str_to_delimiters.count(string("") + ch);
}

bool is_eof(char ch)
{
    return ch == EOF;
}

LexemeType get_lexeme_type(LexemeValue value)
{
    if(executable_mnemonics.count(value))
        return LexemeType::EXECUTABLE_MNEMONIC;
    if(qword_registers.count(value))
        return LexemeType::QWORD_REGISTER;
    if(dword_registers.count(value))
        return LexemeType::DWORD_REGISTER;
    if(word_registers.count(value))
        return LexemeType::WORD_REGISTER;
    if(byte_registers.count(value))
        return LexemeType::BYTE_REGISTER;
    if(identifiers.count(value))
        return LexemeType::IDENTIFIER;
    if(declaration_mnemonics.count(value))
        return LexemeType::DECLARATION_MNEMONIC;
    if(literal_types.count(value))
        return LexemeType::LITERAL;
    if(delimiters.count(value))
        return LexemeType::DELIMITER;

    assert(0);
}

char get_escape_sequences(char ch)
{
    if (ch == 'a')
        return '\a';
    if (ch == 'b')
        return '\b';
    if (ch == 'f')
        return '\f';
    if (ch == 'n')
        return '\n';
    if (ch == 'r')
        return '\r';
    if (ch == 't')
        return '\t';
    if (ch == 'v')
        return '\v';
    if (ch == '\'')
        return '\'';
    if (ch == '\"')
        return '\"';
    if (ch == '\\')
        return '\\';
    else throw runtime_error("No such escape sequence");
}

NameTableItem& get_name_table_item(NameTable& name_table, const Lexeme& identifier)
{
    assert(identifier.type == LexemeType::IDENTIFIER);
    return name_table[identifier.id];
}

std::variant<std::string, int64_t>& get_literal(LiteralTable& literal_table, const Lexeme& literal)
{
    assert(literal.type == LexemeType::LITERAL);
    return literal_table[literal.id];
}

bool is_byte_register(LexemeValue lex_val)
{
    return byte_registers.count(lex_val);
}

bool is_word_register(LexemeValue lex_val)
{
    return word_registers.count(lex_val);
}

bool is_dword_register(LexemeValue lex_val)
{
    return dword_registers.count(lex_val);
}

bool is_qword_register(LexemeValue lex_val)
{
    return qword_registers.count(lex_val);
}

bool is_additional_register(LexemeValue lex_val)
{
    return additional_registers.count(lex_val);
}

uint8_t get_reg_code(LexemeValue lex_val)
{
    return reg_to_code.at(lex_val);
}

bool is_jcc(LexemeValue lex_val)
{
    return jcc_mnemonics.count(lex_val);
}
