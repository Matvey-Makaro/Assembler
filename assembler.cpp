#include "assembler.h"
#include "lexical_analyzer.h"
#include "first_pass.h"
#include "second_pass.h"
#include "elf_file_generator.h"

#include <utility>
#include <iostream>
#include <stdexcept>
using namespace std;

Assembler::Assembler(std::string fname) :
    _fname(move(fname))
{

}

void Assembler::assemble()
{
    try
    {
        LexicalAnalyzer lex_analyzer(_fname, _lexeme_table, _name_table, _name_to_id, _literal_table,
                                     _integer_to_id, _str_to_id);
        lex_analyzer.analyze();
    }
    catch(exception& ex)
    {
        cerr << ex.what() << endl;
    }

    FirstPass first_pass(_lexeme_table, _name_table, _literal_table, _row_to_command_size, _start_address);
    first_pass.start();
    auto programm_size = first_pass.get_programm_size();
    auto start_text_address = first_pass.get_start_text_address();

    SecondPass second_pass(programm_size, _lexeme_table, _name_table, _literal_table, _row_to_command_size);
    second_pass.start();
    auto programm = second_pass.get_programm();

    auto file = fopen("result", "w");
    if(file == nullptr)
        throw runtime_error("File " + std::string("result") + " doesn't open!");

    ElfFileGenerator generator(programm, _start_address, start_text_address);
    generator.generate(file);

    fclose(file);
    double delete_later = 0;
}
