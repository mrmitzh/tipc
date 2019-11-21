#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "TIPUnificationTerms.h"

class UnionFindSolver
{

    void unify(std::shared_ptr<Term> t1,std::shared_ptr<Term> t2);
    std::shared_ptr<Term> find(std::shared_ptr<Term> p);
    std::map<std::shared_ptr<Term>,std::shared_ptr<Term>> getResult();
private:
    void makeUnion(std::shared_ptr<Term> t1,std::shared_ptr<Term> t2);
    void makeSet(std::shared_ptr<Term> t);
    std::map<std::shared_ptr<Term>,std::shared_ptr<Term>> parent;
};