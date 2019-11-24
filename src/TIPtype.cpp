#include "TIPtype.h"


TipRef::TipRef(std::unique_ptr<Term> of)
{
    
}


std::shared_ptr<Mu> TipTypeOps::makeMu(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{
    
}


std::shared_ptr<Var> TipTypeOps::makeAlpha(std::shared_ptr<Var> x)
{

}



TipMu::TipMu(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{
    this->v = v;
    this->t = t;
}

std::shared_ptr<Term> TipMu::subst(std::shared_ptr<Var> sv,std::shared_ptr<Term> to)
{
    if(sv == v)
    {
        return shared_from_this();
    }else
    {
        return std::make_shared<TipMu>(v,t->subst(sv,to));
    }
}