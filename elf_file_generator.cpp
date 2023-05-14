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


//    // TODO: Поменять p_filesz и p_memsz в program header.
//    uint8_t commands[100];
//#if 0
//    // mov rax, 0
//    commands[0] = 0xB8;
//    commands[1] = 0x00;
//    commands[2] = 0x00;
//    commands[3] = 0x00;
//    commands[4] = 0x00;
//
//    //mov rdi, 0
//    commands[5] = 0xBF;
//    commands[6] = 0x00;
//    commands[7] = 0x00;
//    commands[8] = 0x00;
//    commands[9] = 0x00;
//
//    // mov rsi, 0
//    commands[10] = 0xBE;
//    commands[11] = 0x22;
//    commands[12] = 0x00;
//    commands[13] = 0x40;
//    commands[14] = 0x00;
//
//    //mov rdx, 14
//    commands[15] = 0xBA;
//    commands[16] = 0x02;
//    commands[17] = 0x00;
//    commands[18] = 0x00;
//    commands[19] = 0x00;
//
//    // syscall
//    commands[20] = 0x0F;
//    commands[21] = 0x05;
//
//    // mov rax, 60
//    commands[22] = 0xB8;
//    commands[23] = 0x3C;
//    commands[24] = 0x00;
//    commands[25] = 0x00;
//    commands[26] = 0x00;
//
//    //mov rdi, 0
//    commands[27] = 0xBF;
//    commands[28] = 0x00;
//    commands[29] = 0x00;
//    commands[30] = 0x00;
//    commands[31] = 0x00;
//
//    // syscall
//    commands[32] = 0x0F;
//    commands[33] = 0x05;
//    commands[34] = 0x00;
//    commands[35] = 0x00;
//
//
//
//    for(size_t i = 0; i < 34; i++)
//        fwrite(&commands[i], sizeof(commands[i]), 1, file);
//#else
//    // mov rax, 60
//    commands[0] = 0xB8;
//    commands[1] = 0x3C;
//    commands[2] = 0x00;
//    commands[3] = 0x00;
//    commands[4] = 0x00;
//
//    //mov rdi, 0
//    commands[5] = 0xBF;
//    commands[6] = 0x00;
//    commands[7] = 0x00;
//    commands[8] = 0x00;
//    commands[9] = 0x00;
//
//    // syscall
//    commands[10] = 0x0F;
//    commands[11] = 0x05;
//    commands[12] = 0x00;
//    commands[13] = 0x00;
//    commands[14] = 0x00;
//    commands[15] = 0x00;
//
//
//
//    for(size_t i = 0; i < 14; i++)
//        fwrite(&commands[i], sizeof(commands[i]), 1, file);
//#endif
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

#if 1
    _program_header.p_filesz = 34;
    _program_header.p_memsz = 34;
#endif
}