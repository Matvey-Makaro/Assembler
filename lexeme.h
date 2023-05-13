#pragma once

#include <cstdint>
#include <cstddef>
#include <unordered_set>
#include <ostream>

enum class LexemeType
{
    IDENTIFIER,
    DECLARATION_MNEMONIC,
    EXECUTABLE_MNEMONIC,
    LITERAL,
    DELIMITER,
    BYTE_REGISTER,
    WORD_REGISTER,
    DWORD_REGISTER,
    QWORD_REGISTER,

    UNDEFINED,
};

enum class LexemeValue
{
    // IDENTIFIERS
    CONSTANT_IDENTIFIER,
    INITIALIZED_IDENTIFIER,
    UNINITIALIZED_IDENTIFIER,
    LINK,

    // DECLARATION MNEMONICS
    DB,
    DW,
    DD,
    DQ,
    RESB,
    RESW,
    RESD,
    RESQ,
    EQU,

    // EXECUTABLE MNEMONICS
    MOV,
    ADD,
    SUB,
    INC,
    DEC,
    NEG,
    MUL,
    IMUL,
    DIV,
    IDIV,
    AND,
    OR,
    XOR,
    NOT,
    TEST,
    JMP,
    JE,
    JNE,
    JL,
    JLE,
    JG,
    JGE,
    JB,
    JBE,
    JA,
    JAE,
    JZ,
    JS,
    JC,
    JO,
    JP,
    SYSCALL,
    INT,
    BYTE,
    WORD,
    DWORD,
    QWORD,

    // LITERALS
    INT_LITERAL,
    STRING_LITERAL,

    // DELIMITERS
    OPEN_SQUARE_BRACKET,
    CLOS_SQUARE_BRACKET,
    COLON,
    COMMA,

    // BYTE REGISTERS
    al,
    ah,
    bl,
    bh,
    cl,
    ch,
    dl,
    dh,
    spl,
    bpl,
    sil,
    dil,
    r8b,
    r9b,
    r10b,
    r11b,
    r12b,
    r13b,
    r14b,
    r15b,

    // WORD REGISTERS
    ax,
    bx,
    cx,
    dx,
    sp,
    bp,
    si,
    di,
    r8w,
    r9w,
    r10w,
    r11w,
    r12w,
    r13w,
    r14w,
    r15w,

    // DWORD REGISTERS
    eax,
    ebx,
    ecx,
    edx,
    esp,
    ebp,
    esi,
    edi,
    r8d,
    r9d,
    r10d,
    r11d,
    r12d,
    r13d,
    r14d,
    r15d,

    // QWORD REGISTERS
    rax,
    rbx,
    rcx,
    rdx,
    rsp,
    rbp,
    rsi,
    rdi,
    r8,
    r9,
    r10,
    r11,
    r12,
    r13,
    r14,
    r15,

    UNDEFINED,
};

const std::unordered_set<LexemeValue> identifiers = {
        LexemeValue::CONSTANT_IDENTIFIER,
        LexemeValue::INITIALIZED_IDENTIFIER,
        LexemeValue::UNINITIALIZED_IDENTIFIER,
        LexemeValue::LINK,
};

const std::unordered_set<LexemeValue> declaration_mnemonics = {
        LexemeValue::DB,
        LexemeValue::DW,
        LexemeValue::DD,
        LexemeValue::DQ,
        LexemeValue::RESB,
        LexemeValue::RESW,
        LexemeValue::RESD,
        LexemeValue::RESQ,
        LexemeValue::EQU,
};

const std::unordered_set<LexemeValue> executable_mnemonics = {
        LexemeValue::MOV,
        LexemeValue::ADD,
        LexemeValue::SUB,
        LexemeValue::INC,
        LexemeValue::DEC,
        LexemeValue::NEG,
        LexemeValue::MUL,
        LexemeValue::IMUL,
        LexemeValue::DIV,
        LexemeValue::IDIV,
        LexemeValue::AND,
        LexemeValue::OR,
        LexemeValue::XOR,
        LexemeValue::NOT,
        LexemeValue::TEST,
        LexemeValue::JMP,
        LexemeValue::JE,
        LexemeValue::JNE,
        LexemeValue::JL,
        LexemeValue::JLE,
        LexemeValue::JG,
        LexemeValue::JGE,
        LexemeValue::JB,
        LexemeValue::JBE,
        LexemeValue::JA,
        LexemeValue::JAE,
        LexemeValue::JZ,
        LexemeValue::JS,
        LexemeValue::JC,
        LexemeValue::JO,
        LexemeValue::JP,
        LexemeValue::SYSCALL,
        LexemeValue::INT,
        LexemeValue::BYTE,
        LexemeValue::WORD,
        LexemeValue::DWORD,
        LexemeValue::QWORD,
};

const std::unordered_set<LexemeValue> literal_types = {
        LexemeValue::INT_LITERAL,
        LexemeValue::STRING_LITERAL,
};

const std::unordered_set<LexemeValue> delimiters = {
        LexemeValue::OPEN_SQUARE_BRACKET,
        LexemeValue::CLOS_SQUARE_BRACKET,
        LexemeValue::COLON,
        LexemeValue::COMMA,
};

const std::unordered_set<LexemeValue> byte_registers = {
        LexemeValue::al,
        LexemeValue::ah,
        LexemeValue::bl,
        LexemeValue::bh,
        LexemeValue::cl,
        LexemeValue::ch,
        LexemeValue::dl,
        LexemeValue::dh,
        LexemeValue::spl,
        LexemeValue::bpl,
        LexemeValue::sil,
        LexemeValue::dil,
        LexemeValue::r8b,
        LexemeValue::r9b,
        LexemeValue::r10b,
        LexemeValue::r11b,
        LexemeValue::r12b,
        LexemeValue::r13b,
        LexemeValue::r14b,
        LexemeValue::r15b,
};

const std::unordered_set<LexemeValue> word_registers = {
        LexemeValue::ax,
        LexemeValue::bx,
        LexemeValue::cx,
        LexemeValue::dx,
        LexemeValue::sp,
        LexemeValue::bp,
        LexemeValue::si,
        LexemeValue::di,
        LexemeValue::r8w,
        LexemeValue::r9w,
        LexemeValue::r10w,
        LexemeValue::r11w,
        LexemeValue::r12w,
        LexemeValue::r13w,
        LexemeValue::r14w,
        LexemeValue::r15w,
};

const std::unordered_set<LexemeValue> dword_registers = {
        LexemeValue::eax,
        LexemeValue::ebx,
        LexemeValue::ecx,
        LexemeValue::edx,
        LexemeValue::esp,
        LexemeValue::ebp,
        LexemeValue::esi,
        LexemeValue::edi,
        LexemeValue::r8d,
        LexemeValue::r9d,
        LexemeValue::r10d,
        LexemeValue::r11d,
        LexemeValue::r12d,
        LexemeValue::r13d,
        LexemeValue::r14d,
        LexemeValue::r15d,
};

const std::unordered_set<LexemeValue> qword_registers = {
        LexemeValue::rax,
        LexemeValue::rbx,
        LexemeValue::rcx,
        LexemeValue::rdx,
        LexemeValue::rsp,
        LexemeValue::rbp,
        LexemeValue::rsi,
        LexemeValue::rdi,
        LexemeValue::r8,
        LexemeValue::r9,
        LexemeValue::r10,
        LexemeValue::r11,
        LexemeValue::r12,
        LexemeValue::r13,
        LexemeValue::r14,
        LexemeValue::r15,
};

struct Lexeme
{
    LexemeType type;
    LexemeValue value;
    int64_t id;
    size_t size;
    uint64_t line;
    uint64_t col;

    Lexeme(LexemeType lex_type, LexemeValue lex_value, int64_t lex_id, size_t lex_size,
           uint64_t line_num, uint64_t col_num) :
           type(lex_type), value(lex_value), id(lex_id), size(lex_size), line(line_num), col(col_num)
    { }
};
