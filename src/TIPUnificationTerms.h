#pragma once
#include <map>
#include <memory>
#include <set>

template<typename T>
class Var;

template<typename T>
class Term
{
public:
    virtual ~Term() {}
    virtual std::set<std::shared_ptr<Var<T>>> fv() = 0;
    virtual std::shared_ptr<Term<T>> subst(std::shared_ptr<Var<T>> v,std::shared_ptr<Term<T>> t) = 0;
};


template<typename T>
class Var: public Term<T>
{
public:
    virtual std::set<std::shared_ptr<Var<T>>> fv();
    virtual std::shared_ptr<Term<T>> subst(std::shared_ptr<Var<T>> v,std::shared_ptr<Term<T>> t);
};

template<typename T>
class Cons: public Term<T>
{
public:

};

template<typename T>
class TermOPs
{

};



