#include "TIPUnificationTerms.h"


std::string Term::type()
{
    return std::string("Term");
}

std::string Term::getType()
{
    return Term::type();
}

std::string Var::type()
{
    return std::string("Var");
}

std::string Var::getType()
{
    return Var::type();
}

std::string Cons::type()
{
    return std::string("Cons");
}

std::string Cons::getType()
{
    return Cons::type();
}


std::set<std::shared_ptr<Var>> Var::fv()
{
    std::set<std::shared_ptr<Var>> set;
    auto self = std::make_shared<Var>(*this);
    set.insert(self);
    return set;
}

std::shared_ptr<Term> Var::subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{
    // TODO: write the correct version
}


int Cons::arity()
{
    return args.size();
}

std::set<std::shared_ptr<Var>> Cons::fv()
{

}

std::shared_ptr<Term> Cons::subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{

}

bool doMatch(std::shared_ptr<Term> t)
{
    // TODO: check using typeid is ture in this case
    
    return false;
}
