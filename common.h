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
using NameToID = std::unordered_map<std::string, uint32_t>;
using RowToAddress = std::unordered_map<uint64_t, int64_t>;
using LiteralTable = std::vector<std::variant<std::string, int64_t>>;   // TODO: Fix. All numbers in the language are limited to int64_t
using IntegerToID =  std::unordered_map<int64_t, uint64_t>;
using StrToID = std::unordered_map<std::string, uint64_t>;
using LexemeTable = std::vector<std::vector<Lexeme>>;
using Programm = std::vector<uint8_t>;

bool is_delimiter(char ch);
bool is_eof(char ch);
LexemeType get_lexeme_type(LexemeValue value);
char get_escape_sequences(char ch);
NameTableItem& get_name_table_item(NameTable& name_table, const Lexeme& identifier);
std::variant<std::string, int64_t>& get_literal(LiteralTable& literal_table, const Lexeme& literal);
bool is_byte_register(LexemeValue lex_val);
bool is_word_register(LexemeValue lex_val);
bool is_dword_register(LexemeValue lex_val);
bool is_qword_register(LexemeValue lex_val);
bool is_additional_register(LexemeValue lex_val);
uint8_t get_reg_code(LexemeValue lex_val);
bool is_jcc(LexemeValue lex_val);


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
        {"cmp", LexemeValue::CMP},

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

const std::unordered_map<LexemeValue, uint8_t> reg_to_code = {
        {LexemeValue::al, 0b000},  {LexemeValue::ax, 0b000}, {LexemeValue::eax, 0b000}, {LexemeValue::rax, 0b000}, {LexemeValue::r8b, 0b000},   {LexemeValue::r8w, 0b000},   {LexemeValue::r8d, 0b000},   {LexemeValue::r8, 0b000},
        {LexemeValue::cl, 0b001},  {LexemeValue::cx, 0b001}, {LexemeValue::ecx, 0b001}, {LexemeValue::rcx, 0b001}, {LexemeValue::r9b, 0b001},   {LexemeValue::r9w, 0b001},   {LexemeValue::r9d, 0b001},   {LexemeValue::r9, 0b001},
        {LexemeValue::dl, 0b010},  {LexemeValue::dx, 0b010}, {LexemeValue::edx, 0b010}, {LexemeValue::rdx, 0b010}, {LexemeValue::r10b, 0b010},  {LexemeValue::r10w, 0b010},  {LexemeValue::r10d, 0b010},  {LexemeValue::r10, 0b010},
        {LexemeValue::bl, 0b011},  {LexemeValue::bx, 0b011}, {LexemeValue::ebx, 0b011}, {LexemeValue::rbx, 0b011}, {LexemeValue::r11b, 0b011},  {LexemeValue::r11w, 0b011},  {LexemeValue::r11d, 0b011},  {LexemeValue::r11, 0b011},
        {LexemeValue::spl, 0b100}, {LexemeValue::sp, 0b100}, {LexemeValue::esp, 0b100}, {LexemeValue::rsp, 0b100}, {LexemeValue::r12b, 0b100},  {LexemeValue::r12w, 0b100},  {LexemeValue::r12d, 0b100},  {LexemeValue::r12, 0b100},
        {LexemeValue::bpl, 0b101}, {LexemeValue::bp, 0b101}, {LexemeValue::ebp, 0b101}, {LexemeValue::rbp, 0b101}, {LexemeValue::r13b, 0b101},  {LexemeValue::r13w, 0b101},  {LexemeValue::r13d, 0b101},  {LexemeValue::r13, 0b101},
        {LexemeValue::sil, 0b110}, {LexemeValue::si, 0b110}, {LexemeValue::esi, 0b110}, {LexemeValue::rsi, 0b110}, {LexemeValue::r14b, 0b110},  {LexemeValue::r14w, 0b110},  {LexemeValue::r14d, 0b110},  {LexemeValue::r14, 0b110},
        {LexemeValue::dil, 0b110}, {LexemeValue::di, 0b111}, {LexemeValue::edi, 0b111}, {LexemeValue::rdi, 0b111}, {LexemeValue::r15b, 0b111},  {LexemeValue::r15w, 0b111},  {LexemeValue::r15d, 0b111},  {LexemeValue::r15, 0b111},
};


const std::unordered_map<LexemeValue, uint8_t> jcc_to_opcode
{
        {LexemeValue::JE, 0x84},
        {LexemeValue::JL, 0x8C},
        {LexemeValue::JLE, 0x8E},
        {LexemeValue::JG, 0x8F},
        {LexemeValue::JGE, 0x8D},
        {LexemeValue::JB, 0x82},
        {LexemeValue::JBE, 0x86},
        {LexemeValue::JA, 0x87},
        {LexemeValue::JAE, 0x83},
        {LexemeValue::JZ, 0x84},
        {LexemeValue::JS, 0x88},
        {LexemeValue::JC, 0x82},
        {LexemeValue::JO, 0x80},
        {LexemeValue::JP, 0x8A},
};


constexpr int BYTE_SIZE = 1;
constexpr int WORD_SIZE = 2;
constexpr int DWORD_SIZE = 4;
constexpr int QWORD_SIZE = 8;
