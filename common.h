#pragma once

#include "name_table_item.h"
#include "lexeme.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <string_view>
#include <variant>
#include <stdio.h>

using NameTable = std::vector<NameTableItem>;
using NameToID = std::unordered_map<std::string_view, uint32_t>;
using RowToCommandSize = std::unordered_map<uint64_t, uint8_t>;
using LiteralTable = std::vector<std::variant<std::string, int64_t>>;   // TODO: Fix. All numbers in the language are limited to int64_t
using IntegerToID =  std::unordered_map<int64_t, uint64_t>;
using StrToID = std::unordered_map<std::string_view, uint64_t>;
using LexemeTable = std::vector<std::vector<Lexeme>>;

bool is_delimiter(char ch);
bool is_eof(char ch);
LexemeType get_lexeme_type(LexemeValue value);


const std::unordered_map<std::string, LexemeValue> key_words = {
        {"db", LexemeValue::DB},
        {"dw", LexemeValue::DW},
        {"dd", LexemeValue::DD},
        {"dq", LexemeValue::DQ},
        {"resb", LexemeValue::RESB},
        {"resw", LexemeValue::RESW},
        {"resd", LexemeValue::RESD},
        {"resq", LexemeValue::RESQ},
        {"byte", LexemeValue::BYTE},
        {"word", LexemeValue::WORD},
        {"dword", LexemeValue::DWORD},
        {"qword", LexemeValue::QWORD},

        {"mov", LexemeValue::MOV},
        {"add", LexemeValue::ADD},
        {"sub", LexemeValue::SUB},
        {"inc", LexemeValue::INC},
        {"dec", LexemeValue::DEC},
        {"neg", LexemeValue::NEG},
        {"mul", LexemeValue::MUL},
        {"imul", LexemeValue::IMUL},
        {"div", LexemeValue::DIV},
        {"idiv", LexemeValue::IDIV},
        {"and", LexemeValue::AND},
        {"or", LexemeValue::OR},
        {"xor", LexemeValue::XOR},
        {"not", LexemeValue::NOT},
        {"test", LexemeValue::TEST},
        {"jmp", LexemeValue::JMP},
        {"je", LexemeValue::JE},
        {"jne", LexemeValue::JNE},
        {"jl", LexemeValue::JL},
        {"jle", LexemeValue::JLE},
        {"jg", LexemeValue::JG},
        {"jge", LexemeValue::JGE},
        {"jb", LexemeValue::JB},
        {"jbe", LexemeValue::JBE},
        {"ja", LexemeValue::JA},
        {"jae", LexemeValue::JAE},
        {"jz", LexemeValue::JZ},
        {"js", LexemeValue::JS},
        {"jc", LexemeValue::JC},
        {"jo", LexemeValue::JO},
        {"jp", LexemeValue::JP},
        {"syscall", LexemeValue::SYSCALL},
        {"int", LexemeValue::INT},

        {"al", LexemeValue::al},
        {"ah", LexemeValue::ah},
        {"bl", LexemeValue::bl},
        {"bh", LexemeValue::bh},
        {"cl", LexemeValue::cl},
        {"ch", LexemeValue::ch},
        {"dl", LexemeValue::dl},
        {"dh", LexemeValue::dh},
        {"spl", LexemeValue::spl},
        {"bpl", LexemeValue::bpl},
        {"sil", LexemeValue::sil},
        {"dil", LexemeValue::dil},
        {"r8b", LexemeValue::r8b},
        {"r9b", LexemeValue::r9b},
        {"r10b", LexemeValue::r10b},
        {"r11b", LexemeValue::r11b},
        {"r12b", LexemeValue::r12b},
        {"r13b", LexemeValue::r13b},
        {"r14b", LexemeValue::r14b},
        {"r15b", LexemeValue::r15b},
        {"ax", LexemeValue::ax},
        {"bx", LexemeValue::bx},
        {"cx", LexemeValue::cx},
        {"dx", LexemeValue::dx},
        {"sp", LexemeValue::sp},
        {"bp", LexemeValue::bp},
        {"si", LexemeValue::si},
        {"di", LexemeValue::di},
        {"r8w", LexemeValue::r8w},
        {"r9w", LexemeValue::r9w},
        {"r10w", LexemeValue::r10w},
        {"r11w", LexemeValue::r11w},
        {"r12w", LexemeValue::r12w},
        {"r13w", LexemeValue::r13w},
        {"r14w", LexemeValue::r14w},
        {"r15w", LexemeValue::r15w},
        {"eax", LexemeValue::eax},
        {"ebx", LexemeValue::ebx},
        {"ecx", LexemeValue::ecx},
        {"edx", LexemeValue::edx},
        {"esp", LexemeValue::esp},
        {"ebp", LexemeValue::ebp},
        {"esi", LexemeValue::esi},
        {"edi", LexemeValue::edi},
        {"r8d", LexemeValue::r8d},
        {"r9d", LexemeValue::r9d},
        {"r10d", LexemeValue::r10d},
        {"r11d", LexemeValue::r11d},
        {"r12d", LexemeValue::r12d},
        {"r13d", LexemeValue::r13d},
        {"r14d", LexemeValue::r14d},
        {"r15d", LexemeValue::r15d},
        {"rax", LexemeValue::rax},
        {"rbx", LexemeValue::rbx},
        {"rcx", LexemeValue::rcx},
        {"rdx", LexemeValue::rdx},
        {"rsp", LexemeValue::rsp},
        {"rbp", LexemeValue::rbp},
        {"rsi", LexemeValue::rsi},
        {"rdi", LexemeValue::rdi},
        {"r8", LexemeValue::r8},
        {"r9", LexemeValue::r9},
        {"r10", LexemeValue::r10},
        {"r11", LexemeValue::r11},
        {"r12", LexemeValue::r12},
        {"r13", LexemeValue::r13},
        {"r14", LexemeValue::r14},
        {"r15", LexemeValue::r15},
};

const std::unordered_map<std::string, LexemeValue> str_to_delimiters = {
        {"[", LexemeValue::OPEN_SQUARE_BRACKET},
        {"]", LexemeValue::CLOS_SQUARE_BRACKET},
        {":", LexemeValue::COLON},
        {",", LexemeValue::COMMA},
};
