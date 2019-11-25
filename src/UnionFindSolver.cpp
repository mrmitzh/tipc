#include "UnionFindSolver.h"


void UnionFindSolver::unify(std::shared_ptr<Term> t1,std::shared_ptr<Term> t2)
{
    makeSet(t1);
    makeSet(t2);

    auto parent_t1 = find(t1);
    auto parent_t2 = find(t2);

    if(parent_t1 == parent_t2)
        return;

    auto type_of_t1 = t1->getType();
    auto type_of_t2 = t2->getType();

    if(type_of_t1 == Var::type() && type_of_t2 == Var::type())
    {
        auto v1 = std::dynamic_pointer_cast<Var>(t1);
        auto v2 = std::dynamic_pointer_cast<Var>(t2);
        makeUnion(v1,v2);
    }else if(type_of_t1 == Var::type() && type_of_t2 == Term::type())
    {
        auto v1 = std::dynamic_pointer_cast<Var>(t1);
        auto v2 = std::dynamic_pointer_cast<Term>(t2);
        makeUnion(v1,v2);
    }else if(type_of_t1 == Term::type() && type_of_t2 == Var::type())
    {
        auto v1 = std::dynamic_pointer_cast<Term>(t1);
        auto v2 = std::dynamic_pointer_cast<Var>(t2);
        makeUnion(v2,v1);
    }else if(type_of_t1 == Cons::type() && type_of_t2 == Cons::type())
    {
        auto f1 = std::dynamic_pointer_cast<Cons>(t1);
        auto f2 = std::dynamic_pointer_cast<Cons>(t2);
        if(f1->doMatch(f2))
        {
            makeUnion(f1,f2);
            auto arg1 = f1->args();
            auto arg2 = f2->args();
            for(int i = 0; i < f1->arity();i++)
            {
                makeUnion(arg1[i],arg2[i]);
            }
        }
    }else
    {
        std::cerr << "Can't unify " << t1->getType() << " and " << t2->getType() << "\n";
    }
}


std::shared_ptr<Term> UnionFindSolver::find(std::shared_ptr<Term> p)
{
    makeSet(p);
    auto copy = p;
    while(parent[p] != p)
    {
        p = parent[p];
    }
    parent[copy] = p;
    return p;
}

void UnionFindSolver::makeUnion(std::shared_ptr<Term> t1,std::shared_ptr<Term> t2)
{
    parent[t1] = t2;
}

void UnionFindSolver::makeSet(std::shared_ptr<Term> t)
{
    if(parent.find(t) == parent.end())
    {
        parent[t] = t;
    }
}


std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> UnionFindSolver::solution()
{
    std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> ret;
    for(const auto& pair:parent)
    {
        if(pair.first->getType() == Var::type())
        {
            auto var = std::dynamic_pointer_cast<Var>(pair.first);
            ret[var] = find(pair.first);
        }
    }
    return ret;
}