#pragma once

#include <string>
#include <vector>


enum class ValType : uint8_t
{
    STRING,
    INTEGER,
};

struct NameTableItem
{
    std::string name;
    size_t size = 0;
    std::vector<std::string> str_values;
    std::vector<int64_t> int_values;
    ValType type = ValType::INTEGER;
    size_t address = 0;
};