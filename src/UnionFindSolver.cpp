#include "TypeMapping.h"
#include "UnionFindSolver.h"

void UnionFindSolver::unify(std::shared_ptr<Term> t1,std::shared_ptr<Term> t2)
{
    t1 = TypeMapping::getTypeOrDefault(t1);
    t2 = TypeMapping::getTypeOrDefault(t2);

    makeSet(t1);
    makeSet(t2);

    auto parent_t1 = find(t1);
    auto parent_t2 = find(t2);

    if(parent_t1 == parent_t2)
        return;

    if(std::dynamic_pointer_cast<Var>(parent_t1) && std::dynamic_pointer_cast<Var>(parent_t2))
    {
        auto v1 = std::dynamic_pointer_cast<Var>(parent_t1);
        auto v2 = std::dynamic_pointer_cast<Var>(parent_t2);
        makeUnion(v1,v2);
    }else if(std::dynamic_pointer_cast<Var>(parent_t1) && std::dynamic_pointer_cast<Term>(parent_t2))
    {
        auto v1 = std::dynamic_pointer_cast<Var>(parent_t1);
        auto v2 = std::dynamic_pointer_cast<Term>(parent_t2);
        makeUnion(v1,v2);
    }else if(std::dynamic_pointer_cast<Term>(parent_t1) && std::dynamic_pointer_cast<Var>(parent_t2))
    {
        auto v1 = std::dynamic_pointer_cast<Term>(parent_t1);
        auto v2 = std::dynamic_pointer_cast<Var>(parent_t2);
        makeUnion(v2,v1);
    }else if(std::dynamic_pointer_cast<Cons>(parent_t1) && std::dynamic_pointer_cast<Cons>(parent_t2))
    {
        auto f1 = std::dynamic_pointer_cast<Cons>(parent_t1);
        auto f2 = std::dynamic_pointer_cast<Cons>(parent_t2);
        if(f1->doMatch(f2))
        {
            makeUnion(f1,f2);
            auto arg1 = f1->args;
            auto arg2 = f2->args;
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


std::shared_ptr<Term> UnionFindSolver::find(std::shared_ptr<Term> t)
{
    makeSet(t);
    if (parent[t] != t)
      parent[t] = find(parent[t]);
    return parent[t];
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
        auto var = std::dynamic_pointer_cast<Var>(pair.first);
        if(var)
        {
            ret[var] = find(pair.first);
        }
    }
    return ret;
}