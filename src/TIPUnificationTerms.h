#pragma once
#include <map>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>

class Var;

class Term
{
public:
    virtual ~Term() = default;
    virtual std::set<std::shared_ptr<Var>> fv() {};
    virtual std::shared_ptr<Term> subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t) {};
    static std::string type();
    virtual std::string getType();
};


class Var: public Term
{
public:
    std::set<std::shared_ptr<Var>> fv() override;
    std::shared_ptr<Term> subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t) override;
    static std::string type();
    std::string getType() override;
};

class Cons: public Term
{
public:
    std::vector<std::shared_ptr<Term>> args;
    int arity();
    bool doMatch(std::shared_ptr<Term> t);
    std::set<std::shared_ptr<Var>> fv() override;
    static std::string type();
    std::string getType() override;
};

class Mu: public Term
{
public:
    std::shared_ptr<Var> v;
    std::shared_ptr<Term> t;

    virtual std::set<std::shared_ptr<Var>> fv() override;

    static std::string type();
    std::string getType() override;
};

class TermOps
{
public:
    virtual std::shared_ptr<Mu> makeMu(std::shared_ptr<Var> v,std::shared_ptr<Term> t) = 0;
    virtual std::shared_ptr<Var> makeAlpha(std::shared_ptr<Var> x) = 0;
    std::shared_ptr<Term> close(std::shared_ptr<Term> t,std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> env);
private:
    std::shared_ptr<Term> closeRec(std::shared_ptr<Term> t,std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> env, std::unordered_set<std::shared_ptr<Var>>& visited);
};