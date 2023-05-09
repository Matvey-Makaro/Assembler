#pragma once

#include <string>
#include <vector>


//enum class ValType : uint8_t
//{
//    STRING,
//    INTEGER,
//};

enum class IdentifierType
{
    CONSTANT,
    INITIALIZED,
    UNINITIALIZED,
    LINK,
};

struct NameTableItem
{
    std::string name;
    size_t size = 0;
    std::vector<int64_t> int_values;
    size_t address = 0;
    IdentifierType type;
//    std::vector<std::string> str_values;
//    ValType type = ValType::INTEGER;

};