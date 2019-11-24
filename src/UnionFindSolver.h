#pragma once
#include <map>
#include <memory>
#include <unordered_map>
#include <iostream>
#include "TIPUnificationTerms.h"

class UnionFindSolver
{
public:
    std::unordered_map<std::unique_ptr<Term>,std::unique_ptr<Term>> parent;
    void unify(std::unique_ptr<Term> t1,std::unique_ptr<Term> t2);
    std::unique_ptr<Term> find(std::shared_ptr<Term> p);
    void makeUnion(std::unique_ptr<Term> t1,std::unique_ptr<Term> t2);
    void makeSet(std::unique_ptr<Term> t);
    std::unordered_map<std::unique_ptr<Var>,std::unique_ptr<Term>> solution();
};