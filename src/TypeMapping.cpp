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


std::shared_ptr<TipInt> TypeMapping::makeTipInt()
{
    std::shared_ptr<TipInt> tipInt = std::make_shared<TipInt>();
    return std::dynamic_pointer_cast<TipInt>(getTypeOrDefault(tipInt));
}

std::shared_ptr<TipFunction> TypeMapping::makeTipFunction(std::vector<std::shared_ptr<Term>> params,std::shared_ptr<Term> ret)
{
    std::shared_ptr<TipFunction> tipFunction = std::make_shared<TipFunction>(params,ret);
    return std::dynamic_pointer_cast<TipFunction>(getTypeOrDefault(tipFunction));
}

std::shared_ptr<TipRef> TypeMapping::makeTipRef(std::shared_ptr<Term> of)
{
    std::shared_ptr<TipRef> tipRef = std::make_shared<TipRef>(of);
    return std::dynamic_pointer_cast<TipRef>(getTypeOrDefault(tipRef));
}

std::shared_ptr<TipRecord> TypeMapping::makeTipRecord(std::vector<std::shared_ptr<Term>> args,std::vector<std::string> allFieldNames)
{
    std::shared_ptr<TipRecord> tipRecord = std::make_shared<TipRecord>(args,allFieldNames);
    return std::dynamic_pointer_cast<TipRecord>(getTypeOrDefault(tipRecord));
}

std::shared_ptr<TipVar> TypeMapping::makeTipVar(std::shared_ptr<Node> astNode)
{
    std::shared_ptr<TipVar> tipVar = std::make_shared<TipVar>(astNode);
    return std::dynamic_pointer_cast<TipVar>(getTypeOrDefault(tipVar));
}

std::shared_ptr<TipAlpha> TypeMapping::makeTipAlpha(std::shared_ptr<Node> root,std::string fieldName)
{
    std::shared_ptr<TipAlpha> tipAlpha = std::make_shared<TipAlpha>(root,fieldName);
    return std::dynamic_pointer_cast<TipAlpha>(getTypeOrDefault(tipAlpha));
}

std::shared_ptr<TipMu> TypeMapping::makeTipMu(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{
    std::shared_ptr<TipMu> tipMu = std::make_shared<TipMu>(v,t);
    return std::dynamic_pointer_cast<TipMu>(getTypeOrDefault(tipMu));
}