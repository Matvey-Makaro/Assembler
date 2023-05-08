//
// Created by matvey on 5/8/23.
//

#include "lexical_analyzer.h"

LexicalAnalyzer::LexicalAnalyzer(std::vector<NameTableItem> &name_table,
                                 std::unordered_map<std::string_view, uint32_t> &name_to_id,
                                 std::unordered_map<uint64_t, uint8_t> &row_to_command_size) :
                                 _name_table(name_table), _name_to_id(name_to_id), _row_to_command_size(row_to_command_size)
{

}

