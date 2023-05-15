#include "assembler.h"
#include "lexical_analyzer.h"
#include "first_pass.h"
#include "second_pass.h"
#include "elf_file_generator.h"

#include <utility>
#include <iostream>
#include <stdexcept>
using namespace std;

Assembler::Assembler(std::string in_fname, std::string out_fname) :
        _in_fname(move(in_fname)), _out_fname(move(out_fname))
{

}

void Assembler::assemble()
{
    try
    {
        LexicalAnalyzer lex_analyzer(_in_fname, _lexeme_table, _name_table, _name_to_id, _literal_table,
                                     _integer_to_id, _str_to_id);
        lex_analyzer.analyze();
    }
    catch(exception& ex)
    {
        cerr << ex.what() << endl;
    }

    FirstPass first_pass(_lexeme_table, _name_table, _literal_table, _row_to_address, _start_address);
    first_pass.start();
    auto programm_size = first_pass.get_programm_size();
    auto start_text_address = first_pass.get_start_text_address();

    SecondPass second_pass(programm_size, _lexeme_table, _name_table, _literal_table, _row_to_address);
    second_pass.start();
    auto programm = second_pass.get_programm();

    auto file = fopen(_out_fname.c_str(), "w");
    if(file == nullptr)
        throw runtime_error("File " + _out_fname + " doesn't open!");

    ElfFileGenerator generator(programm, _start_address, start_text_address);
    generator.generate(file);

    fclose(file);
    system(("chmod +x " + _out_fname).c_str());
    double delete_later = 0;
}
