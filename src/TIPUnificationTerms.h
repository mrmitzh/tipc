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
    virtual std::set<std::unique_ptr<Var>> fv() = 0;
    virtual std::unique_ptr<Term> subst(std::unique_ptr<Var> v,std::unique_ptr<Term> t) = 0;
    static std::string type();
    virtual std::string getType();
};


class Var: public Term
{
public:
    std::set<std::unique_ptr<Var>> fv() override;
    std::unique_ptr<Term> subst(std::unique_ptr<Var> v,std::unique_ptr<Term> t) override;
    static std::string type();
    std::string getType() override;
};

class Cons: public Term
{
public:
    std::vector<std::unique_ptr<Term>> args;
    int arity();
    bool doMatch(std::unique_ptr<Term> t);
    std::set<std::unique_ptr<Var>> fv() override;
    std::unique_ptr<Term> subst(std::unique_ptr<Var> v,std::unique_ptr<Term> t) override;
    static std::string type();
    std::string getType() override;
};

class Mu: public Term
{
public:

};

class TermOps
{
public:

};