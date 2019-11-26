#pragma once

#include "TIPtree.h"
#include "TIPUnificationTerms.h"


using namespace TIPtree;

class TipType
{
public:
    TipType() = default;
    virtual ~TipType() = default;
    static std::string type();
    virtual std::string getType() = 0;
    virtual std::string toString();
};

class TipMu;

class TipVar;

class TipAlpha;

class TipTypeOps: public TermOps
{
public:
    std::shared_ptr<Mu> makeMu(std::shared_ptr<Var> v,std::shared_ptr<Term> t) override;
    std::shared_ptr<Var> makeAlpha(std::shared_ptr<Var> x) override;
};


class TipInt:public TipType, public Cons, public std::enable_shared_from_this<TipInt>
{
public:
    TipInt() = default;
    ~TipInt() = default;
    static std::string type();
    std::string getType() override;
    std::vector<std::shared_ptr<Term>> args() override;
    std::shared_ptr<Term> subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t) override;
    std::string toString() override;
};

class TipFunction:public TipType, public Cons
{
private:
    std::vector<std::shared_ptr<Term>> params;
    std::shared_ptr<Term> ret;
public:
    TipFunction(std::vector<std::shared_ptr<Term>> params,std::shared_ptr<Term> ret);
    ~TipFunction() = default;
    static std::string type();
    std::string getType() override;
    std::vector<std::shared_ptr<Term>> args() override;
    std::shared_ptr<Term> subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t) override;
    std::string toString() override;
};


class TipRef:public TipType, public Cons
{
private:
    std::shared_ptr<Term> of;
public:
    TipRef(std::shared_ptr<Term> of);
    std::vector<std::shared_ptr<Term>> args() override;
    std::shared_ptr<Term> subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t) override;
    static std::string type();
    std::string getType() override;
    std::string toString() override;
};

class TipRecord:public TipType, public Cons
{
private:
    std::vector<std::shared_ptr<Term>> args;
    std::vector<std::string> allFieldNames;
public:
    TipRecord(std::vector<std::shared_ptr<Term>> args,std::vector<std::string> allFieldNames);
    ~TipRecord() = default;
    static std::string type();
    std::string getType() override;
    std::shared_ptr<Term> subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t) override;
    std::string toString() override;
};

class TipVar:public TipType, public Var
{
public:
    std::shared_ptr<Node> astNode;
    TipVar(std::shared_ptr<Node> astNode) :astNode(astNode) {};
    ~TipVar() = default;
    static std::string type();
    std::string getType() override;
    std::string toString() override;
};

class TipAlpha: public TipType, public Var
{
private:
    uint64_t address;
public:
    TipAlpha(uint64_t address);
    ~TipAlpha() = default;
    static std::string type();
    std::string getType() override;
    std::string toString() override;
};

class TipMu:public TipType, public Mu, public std::enable_shared_from_this<TipMu>
{
private:
    std::shared_ptr<Var> v;
    std::shared_ptr<Term> t;
public:
    TipMu(std::shared_ptr<Var> v,std::shared_ptr<Term> t);
    std::shared_ptr<Term> subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t) override;
    static std::string type();
    std::string getType() override;
};


