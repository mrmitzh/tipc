#include "TIPUnificationTerms.h"

std::set<std::shared_ptr<Var>> Var::fv()
{
    std::set<std::shared_ptr<Var>> set;
    auto self = std::make_shared<Var>(*this);
    set.insert(self);
    return set;
}

std::string Term::getType()
{
    return std::string("Term");
}

std::string Var::getType()
{
    return std::string("Var");
}

std::string Cons::getType()
{
    return std::string("Cons");
}



std::shared_ptr<Term> Var::subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{
    // TODO: write the correct version
}


int Cons::arity()
{
    return args.size();
}

bool doMatch(std::shared_ptr<Term> t)
{
    // TODO: check using typeid is ture in this case
    
    return false;
}
