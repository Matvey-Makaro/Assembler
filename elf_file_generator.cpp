#include "elf_file_generator.h"

ElfFileGenerator::ElfFileGenerator(const Programm &programm, size_t start_address, size_t entry_point) :
        _elf_header{0}, _programm(programm), _start_address(start_address), _entry_point(entry_point)
{
    init_header();
    fill_program_header();
}

void ElfFileGenerator::init_header()
{
    auto* const e_ident = _elf_header.e_ident;
    e_ident[EI_MAG0] = 0x7f;
    e_ident[EI_MAG1] = 'E';
    e_ident[EI_MAG2] = 'L';
    e_ident[EI_MAG3] = 'F';
    e_ident[EI_CLASS] = ELFCLASS64;
    e_ident[EI_DATA] = ELFDATA2LSB;
    e_ident[EI_VERSION] = EV_CURRENT;
    e_ident[EI_OSABI] = ELFOSABI_NONE;  // TODO: Here maybe a problem.
    e_ident[EI_ABIVERSION] = 0;
    e_ident[EI_PAD] = 0;
    e_ident[10] = 0;
    e_ident[11] = 0;
    e_ident[12] = 0;
    e_ident[13] = 0;
    e_ident[14] = 0;
    e_ident[15] = 0;

    _elf_header.e_type = ET_EXEC;
    _elf_header.e_machine = EM_X86_64;
    _elf_header.e_version = EV_CURRENT;
    // _elf_header.e_entry is filled later.
    // _elf_header.e_phoff is filled later.
    // _elf_header.e_shoff is filled later.
    _elf_header.e_flags = 0;
    _elf_header.e_ehsize = sizeof(Elf64_Ehdr);
    // _elf_header.e_phentsize is filled later.
    // _elf_header.e_phnum is filled later.
    // _elf_header.e_shentsize is filled later.
    // _elf_header.e_shnum is filled later.
    _elf_header.e_shstrndx = 0;

    // TODO: For test:
#if 1
    // _elf_header.e_entry = 0x400000 + sizeof(_elf_header);
//    _elf_header.e_entry = 0x40007f;
    _elf_header.e_entry = _entry_point;
    _elf_header.e_phoff = sizeof(_elf_header);    // Где начинается Program _elf_header table
    _elf_header.e_shoff = 0;
    _elf_header.e_phentsize = sizeof(_program_header);
    _elf_header.e_phnum = 1;     // Количество в Program _elf_header table
    _elf_header.e_shentsize = 0;
    _elf_header.e_shnum = 0;
#endif
}

void ElfFileGenerator::generate(FILE* file)
{
    fwrite(reinterpret_cast<void*>(&_elf_header), sizeof(_elf_header), 1, file);
    fwrite(reinterpret_cast<void*>(&_program_header), sizeof(_program_header), 1, file);

    for(size_t i = 0; i < _programm.size(); i++)
        fwrite(&_programm[i], sizeof(_programm[i]), 1, file);
}

void ElfFileGenerator::fill_program_header()
{
    _program_header.p_type = PT_LOAD;
    _program_header.p_flags = PF_X | PF_R | PF_W;
    _program_header.p_offset = sizeof(_elf_header) + sizeof(_program_header);
    //_program_header.p_offset = 0;    // Скорее всего смещение относительно начала сегментов, а не начала файла.
    _program_header.p_vaddr = 0x400000 + _program_header.p_offset;
    _program_header.p_paddr = 0x0;
    // _program_header.p_filesz; is filled later.
    // _program_header.p_memsz; is filled later.
    _program_header.p_align = 0x1000;

    // TODO: Поменять p_filesz и p_memsz в program header.
#if 1
    _program_header.p_filesz = 34;
    _program_header.p_memsz = 34;
#endif
}