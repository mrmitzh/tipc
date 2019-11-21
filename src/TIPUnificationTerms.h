#pragma once
#include <map>
#include <memory>
#include <vector>
#include <set>
#include <string>

class Var;

class Term
{
public:
    virtual ~Term() = default;
    virtual std::set<std::shared_ptr<Var>> fv() = 0;
    virtual std::shared_ptr<Term> subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t) = 0;
    virtual std::string getType();
};


class Var: public Term
{
public:
    virtual std::set<std::shared_ptr<Var>> fv();
    virtual std::shared_ptr<Term> subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t);
    virtual std::string getType();
};

class Cons: public Term
{
public:
    std::vector<std::shared_ptr<Term>> args;
    int arity();
    bool doMatch(std::shared_ptr<Term> t);
    virtual std::set<std::shared_ptr<Var>> fv();
    virtual std::shared_ptr<Term> subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t);
    virtual std::string getType();
};



