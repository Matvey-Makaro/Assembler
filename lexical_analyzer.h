//
// Created by matvey on 5/8/23.
//

#pragma once

#include "name_table_item.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <string_view>


class LexicalAnalyzer
{
public:
    LexicalAnalyzer(std::vector<NameTableItem>& name_table, std::unordered_map<std::string_view, uint32_t>& name_to_id,
                    std::unordered_map<uint64_t, uint8_t>& row_to_command_size);
    ~LexicalAnalyzer() = default;

    LexicalAnalyzer(const LexicalAnalyzer& other) = delete;
    LexicalAnalyzer& operator=(const LexicalAnalyzer& other) = delete;
    LexicalAnalyzer(LexicalAnalyzer&& other) = delete;
    LexicalAnalyzer& operator=(LexicalAnalyzer&& other) = delete;

private:
    std::vector<NameTableItem> _name_table;
    std::unordered_map<std::string_view, uint32_t> _name_to_id;
    std::unordered_map<uint64_t, uint8_t> _row_to_command_size;

};

