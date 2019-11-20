#include "TIPUnificationTerms.h"

template<typename T>
std::set<std::shared_ptr<Var<T>>> Var<T>::fv()
{
    std::set<std::shared_ptr<Var<T>>> set;
    auto self = std::make_shared<Var<T>>(*this);
    set.insert(self);
    return set;
}

template<typename T>
std::shared_ptr<Term<T>> Var<T>::subst(std::shared_ptr<Var<T>> v,std::shared_ptr<Term<T>> t)
{
    if(v.get() == this)
        return t;
    else
        return this; // TODO: can this compile??
}


