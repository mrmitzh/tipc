#pragma once

#include "TIPUnificationTerms.h"

class TipType
{

};

class TipTypeOps:public TipType, public TermOps
{
public:

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