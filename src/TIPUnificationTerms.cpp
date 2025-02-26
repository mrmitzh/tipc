#include "TypeMapping.h"
#include "TIPUnificationTerms.h"


std::string Term::type()
{
    return "Term";
}

std::string Term::getType()
{
    return Term::type();
}

std::string Term::toString()
{
    return "Term";
}

std::string Var::type()
{
    return "Var";
}

std::string Var::getType()
{
    return Var::type();
}

std::string Var::toString()
{
    return "Var";
}

std::string Cons::type()
{
    return std::string("Cons");
}

std::string Cons::getType()
{
    return Cons::type();
}

std::string Cons::toString()
{
    return "Cons";
}

std::string Mu::type()
{
    return std::string("Mu");
}

std::string Mu::getType()
{
    return Mu::type();
}

std::string Mu::toString()
{
    return "\u03bc"+v->toString()+"."+t->toString();
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
    return args.size();
}


std::set<std::shared_ptr<Var>> Cons::fv()
{
    std::set<std::shared_ptr<Var>> result;
    for(const auto& arg:args)
    {
        auto temp = arg->fv();
        result.insert(temp.begin(),temp.end());
    }
    return result;
}


bool Cons::doMatch(std::shared_ptr<Term> t)
{    
    auto cast_type = std::dynamic_pointer_cast<Cons>(t);
    if(cast_type){
        return arity() == cast_type->arity(); 
    } else {
        return false;
    }
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
    if(!t)
        return std::make_shared<Term>();
    t = TypeMapping::getTypeOrDefault(t);
    if(std::dynamic_pointer_cast<Var>(t))
    {
        auto v = std::dynamic_pointer_cast<Var>(t);
        if(env.find(v) == env.end())
        {
            return makeAlpha(v);
        }
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
    }else if(std::dynamic_pointer_cast<Cons>(t))
    {
        auto c = std::dynamic_pointer_cast<Cons>(t);
        auto c_fv = c->fv();
        auto acc = t;
        for(auto& v:c_fv)
        {
            acc = acc->subst(v,closeRec(v,env,visited));
        }
        return acc;
    }else if(std::dynamic_pointer_cast<Mu>(t))
    {
        auto m = std::dynamic_pointer_cast<Mu>(t);
        return makeMu(m->v,closeRec(m->t,env,visited));
    }
    std::cout << "UnMatch" << "\n";
    return std::make_shared<Term>();
}