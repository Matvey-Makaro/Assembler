#pragma once

#include "common.h"

#include <elf.h>
#include <cstdio>

class ElfFileGenerator
{
public:
    ElfFileGenerator(const Programm &programm, size_t start_address, size_t entry_point);
    void generate(FILE* file);

private:
    void init_header();
    void fill_program_header();

private:
    Elf64_Ehdr _elf_header;
    Elf64_Phdr _program_header;
    Elf64_Shdr _segment_header;

    const Programm& _programm;
    size_t _start_address;
    size_t _entry_point;
};