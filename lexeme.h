#pragma once

#include <cstdint>
#include <cstddef>

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
    BYTE,
    WORD,
    DWORD,
    QWORD,

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

    // LITERALS
    INT_LITERAL,
    STRING_LITERAL,

    // DELIMITERS
    OPEN_SQUARE_BRACKET,
    CLOS_SQUARE_BRACKET,
    COLON,

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
};

struct Lexeme
{
    LexemeType lexeme_type;
    LexemeValue value;
    uint64_t id;
    size_t size;
    uint64_t line;
    uint64_t col;
};
