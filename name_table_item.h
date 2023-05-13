#pragma once

#include <string>
#include <vector>
#include <utility>


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
    UNKNOWN,
};

struct NameTableItem
{
    std::string name;
    size_t size = 0;
    std::vector<int64_t> values;
    size_t address = 0;
    IdentifierType type;
//    std::vector<std::string> str_values;
//    ValType type = ValType::INTEGER;

    explicit NameTableItem(std::string item_name) :
    name(std::move(item_name)), size{0}, address{0}, type(IdentifierType::UNKNOWN)
    { }
};