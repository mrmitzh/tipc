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
        makeUnion(t1,t2);
    }else if(type_of_t1 == Var::type() && type_of_t2 == Term::type())
    {
        makeUnion(t1,t2);
    }else if(type_of_t1 == Term::type() && type_of_t2 == Var::type())
    {
        makeUnion(t2,t1);
    }else if(type_of_t1 == Cons::type() && type_of_t2 == Cons::type())
    {
        makeUnion(t1,t2);
        auto cast_t1 = std::dynamic_pointer_cast<Cons>(t1);
        auto cast_t2 = std::dynamic_pointer_cast<Cons>(t2);
        for(int i = 0; i < std::min(cast_t1->arity,cast_t2->arity); i++)
        {
            makeUnion(cast_t1->args[i],cast_t2->args[i]);
        }
    }else
    {
        std::cerr << "Can't unify " << t1->getType() << " and " << t2->getType() << "\n";
    }
}

std::map<std::shared_ptr<Term>,std::shared_ptr<Term>> UnionFindSolver::getResult()
{
    return parent;
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

