#pragma once
#include <map>
#include <memory>
#include <unordered_map>
#include <iostream>
#include "TIPUnificationTerms.h"


class UnionFindSolver
{
public:
    std::unordered_map<std::shared_ptr<Term>,std::shared_ptr<Term>> parent;
    void unify(std::shared_ptr<Term> t1,std::shared_ptr<Term> t2);
    std::shared_ptr<Term> find(std::shared_ptr<Term> p);
    void makeUnion(std::shared_ptr<Term> t1,std::shared_ptr<Term> t2);
    void makeSet(std::shared_ptr<Term> t);
    std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> solution();
};