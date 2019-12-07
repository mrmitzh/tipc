#pragma once
#include <unordered_map>
#include <memory>
#include "TIPtype.h"

class TypeMapping
{
public:
    static std::unordered_map<std::string,std::shared_ptr<Term>> typeMapping;
    static std::shared_ptr<Term> getTypeOrDefault(std::shared_ptr<Term> type);
};