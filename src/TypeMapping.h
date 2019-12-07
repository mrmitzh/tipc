#pragma once
#include <unordered_map>
#include <memory>
#include "TIPtype.h"

class TypeMapping
{
public:
    static std::unordered_map<std::string,std::shared_ptr<Term>> typeMapping;
    static std::shared_ptr<Term> getTypeOrDefault(std::shared_ptr<Term> type);
    static std::shared_ptr<TipInt> makeTipInt();
    static std::shared_ptr<TipFunction> makeTipFunction(std::vector<std::shared_ptr<Term>> params,std::shared_ptr<Term> ret);
    static std::shared_ptr<TipRef> makeTipRef(std::shared_ptr<Term> of);
    static std::shared_ptr<TipRecord> makeTipRecord(std::vector<std::shared_ptr<Term>> args,std::vector<std::string> allFieldNames);
    static std::shared_ptr<TipVar> makeTipVar(std::shared_ptr<Node> astNode);
    static std::shared_ptr<TipAlpha> makeTipAlpha(std::shared_ptr<Node> root,std::string fieldName = "");
    static std::shared_ptr<TipMu> makeTipMu(std::shared_ptr<Var> v,std::shared_ptr<Term> t);
};