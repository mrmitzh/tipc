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


std::set<std::unique_ptr<Var>> Var::fv()
{
    std::set<std::unique_ptr<Var>> set;
    // set.insert(llvm::make_unique<Var>(*this));
    return set;
}

std::unique_ptr<Term> Var::subst(std::unique_ptr<Var> v,std::unique_ptr<Term> t)
{
    // TODO: write the correct version
}


int Cons::arity()
{
    return args.size();
}

std::set<std::unique_ptr<Var>> Cons::fv()
{

}

std::unique_ptr<Term> Cons::subst(std::unique_ptr<Var> v,std::unique_ptr<Term> t)
{

}

bool doMatch(std::unique_ptr<Term> t)
{
    // TODO: check using typeid is ture in this case
    
    return false;
}
