#include "TypeMapping.h"

std::unordered_map<std::string,std::shared_ptr<Term>> TypeMapping::typeMapping;

std::shared_ptr<Term> TypeMapping::getTypeOrDefault(std::shared_ptr<Term> type)
{
    if(typeMapping.find(type->toString()) != typeMapping.end())
    {
        return typeMapping[type->toString()];
    }
    typeMapping[type->toString()] = type;
    return type;
}