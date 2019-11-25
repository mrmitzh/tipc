#include "TIPUnificationTerms.h"


std::string Term::type()
{
    return std::string("Term");
}

std::string Term::getType()
{
    return Term::type();
}

std::string Var::type()
{
    return std::string("Var");
}

std::string Var::getType()
{
    return Var::type();
}

std::string Cons::type()
{
    return std::string("Cons");
}

std::string Cons::getType()
{
    return Cons::type();
}

std::string Mu::type()
{
    return std::string("Mu");
}

std::string Mu::getType()
{
    return Mu::type();
}

std::set<std::shared_ptr<Var>> Var::fv()
{
    std::set<std::shared_ptr<Var>> set;
    set.insert(shared_from_this());
    return set;
}

std::shared_ptr<Term> Var::subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{
    if(v == shared_from_this())
    {
        return t;
    }else
    {
        return shared_from_this();
    }
}


int Cons::arity()
{
    return args().size();
}

std::vector<std::shared_ptr<Term>> Cons::args()
{
    return std::vector<std::shared_ptr<Term>>{};
}

std::set<std::shared_ptr<Var>> Cons::fv()
{
    std::set<std::shared_ptr<Var>> result;
    for(const auto& arg:args())
    {
        auto temp = arg->fv();
        result.insert(temp.begin(),temp.end());
    }
    return result;
}


bool Cons::doMatch(std::shared_ptr<Term> t)
{    
    return getType() == t->getType() && arity() == std::dynamic_pointer_cast<Cons>(t)->arity();
}


std::set<std::shared_ptr<Var>> Mu::fv()
{
    auto result = t->fv();
    result.erase(v);
    return result;
}


std::shared_ptr<Term> TermOps::close(std::shared_ptr<Term> t,std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> env)
{
    std::unordered_set<std::shared_ptr<Var>> visited;
    return closeRec(t,env,visited);
}

std::shared_ptr<Term> TermOps::closeRec(std::shared_ptr<Term> t,std::unordered_map<std::shared_ptr<Var>,std::shared_ptr<Term>> env, std::unordered_set<std::shared_ptr<Var>>& visited)
{
    if(t->getType() == Var::type())
    {
        auto v = std::dynamic_pointer_cast<Var>(t);
        if(visited.find(v) == visited.end() && env[v] != v)
        {
            visited.insert(v);
            auto cterm = closeRec(env[v],env,visited);
            visited.erase(v);
            auto newV = makeAlpha(v);
            
            auto cterm_fv = cterm->fv();
            if(cterm_fv.find(newV) != cterm_fv.end())
            {
                return makeMu(newV,cterm->subst(v,newV));
            }else
            {
                return cterm;
            }
        }else
        {
            return makeAlpha(v);
        }
    }else if(t->getType() == Cons::type())
    {
        auto c = std::dynamic_pointer_cast<Cons>(t);
        auto c_fv = c->fv();
        auto acc = t;
        for(auto& v:c_fv)
        {
            acc->subst(v,closeRec(v,env,visited));
        }
        return acc;
    }else if(t->getType() == Mu::type())
    {
        auto m = std::dynamic_pointer_cast<Mu>(t);
        return makeMu(m->v,closeRec(m->t,env,visited));
    }
}