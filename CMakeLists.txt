cmake_minimum_required(VERSION 3.25)
project(Assembler)

set(CMAKE_CXX_STANDARD 17)

add_executable(Assembler main.cpp lexical_analyzer.cpp lexical_analyzer.h name_table_item.h lexeme.h assembler.cpp assembler.h common.h common.cpp syntax_analyzer.cpp syntax_analyzer.h first_pass.cpp first_pass.h second_pass.cpp second_pass.h elf_file_generator.cpp elf_file_generator.h)
