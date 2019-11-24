#pragma once

#include "TIPUnificationTerms.h"

class TipType
{

};

class TipTypeOps:public TipType, public TermOps
{
public:
    std::shared_ptr<Mu> makeMu(std::shared_ptr<Var> v,std::shared_ptr<Term> t) override;
    std::shared_ptr<Var> makeAlpha(std::shared_ptr<Var> x) override;
};

class TipInt:public TipType, public Cons
{
public:

};


class TipRef:public TipType, public Cons
{
public:
    TipRef(std::unique_ptr<Term> of);
};

// How to implement TipAlpha???