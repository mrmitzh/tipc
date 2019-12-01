#include "TIPtype.h"


std::string TipType::type()
{
    return "TipType";
}

std::string TipType::getType()
{
    return TipType::type();
}

std::string TipType::toString()
{
    return "TipType";
}

std::string TipInt::type()
{
    return "TipInt";
}

std::string TipInt::getType()
{
    return TipInt::type();
}

std::string TipInt::toString()
{
    return "int";
}

std::string TipFunction::type()
{
    return "TipFunction";
}

std::string TipFunction::getType()
{
    return TipFunction::type();
}

std::string TipFunction::toString()
{
    std::string params_str;
    for(int i=0; i<params.size(); i++){
        params_str += params[i]->toString();
        if(i!=params.size()-1){
            params_str += ",";
        }
    }
    std::string ret_str = ret->toString();
    return "("+params_str+") -> "+ret_str;
}

std::string TipRef::type()
{
    return "TipRef";
}

std::string TipRef::getType()
{
    return TipRef::type();
}

std::string TipRef::toString()
{
    return "&"+of->toString();
}

std::string TipMu::type()
{
    return "TipMu";
}

std::string TipMu::getType()
{
    return TipMu::type();
}

std::string TipVar::type()
{
    return "TipVar";
}

std::string TipVar::getType()
{
    return TipVar::type();
}

std::string TipVar::toString()
{
    return "[["+astNode->print()+"]]";
}

std::string TipRecord::type()
{
    return "TipRecord";
}

std::string TipRecord::getType()
{
    return TipRecord::type();
}

std::string TipRecord::toString()
{
    std::string rec_str;
    for(int i = 0; i < allFieldNames.size(); i++)
    {
        rec_str += allFieldNames[i] + ":" + args[i]->toString();
        if(i!=allFieldNames.size()){
            rec_str += ",";
        }
    }
    return rec_str;
}


std::string TipAlpha::type()
{
    return "TipAlpha";
}

std::string TipAlpha::getType()
{
    return TipAlpha::type();
}

std::string TipAlpha::toString()
{
    return "\u03B1<"+std::to_string(address)+">";
}


std::shared_ptr<Var> TipTypeOps::makeAlpha(std::shared_ptr<Var> x)
{
    if(x->getType() == TipVar::type())
    {
        auto tipVar = std::dynamic_pointer_cast<TipVar>(x);
        return std::make_shared<TipAlpha>(tipVar->astNode);
    }else if(x->getType() == TipAlpha::type())
    {
       return std::dynamic_pointer_cast<TipAlpha>(x); 
    }
}

std::shared_ptr<Mu> TipTypeOps::makeMu(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{
    return std::make_shared<TipMu>(v,t);
}

TipInt::TipInt()
{
    
}

std::shared_ptr<Term> TipInt::subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{
    return shared_from_this();
}

TipFunction::TipFunction(std::vector<std::shared_ptr<Term>> params,std::shared_ptr<Term> ret)
    :params(params),ret(ret)
{
    args = params;
    args.insert(args.begin(),ret);
}


std::shared_ptr<Term> TipFunction::subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{
    std::vector<std::shared_ptr<Term>> new_params;
    for(const auto& param:params)
    {
        new_params.push_back(param->subst(v,t));
    }
    return std::make_shared<TipFunction>(new_params,ret->subst(v,t));
}

TipRef::TipRef(std::shared_ptr<Term> of)
    :of(of)
{
    args = {of};
}

std::shared_ptr<Term> TipRef::subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{
    return std::make_shared<TipRef>(of->subst(v,t));
}

TipRecord::TipRecord(std::vector<std::shared_ptr<Term>> args,std::vector<std::string> allFieldNames)
    :args(args),allFieldNames(allFieldNames)
{}

std::shared_ptr<Term> TipRecord::subst(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
{
    std::vector<std::shared_ptr<Term>> new_args;
    for(const auto& arg:args)
    {
        new_args.push_back(arg->subst(v,t));
    }
    return std::make_shared<TipRecord>(new_args,allFieldNames);
}



TipAlpha::TipAlpha(std::shared_ptr<Node> root,std::string fieldName)
    :pointer(root),fieldName(fieldName)
{
    address = reinterpret_cast<uint64_t>(pointer.get());
}


TipMu::TipMu(std::shared_ptr<Var> v,std::shared_ptr<Term> t)
    :v(v),t(t)
{}

std::shared_ptr<Term> TipMu::subst(std::shared_ptr<Var> sv,std::shared_ptr<Term> to)
{
    if(sv == v)
    {
        return shared_from_this();
    }else
    {
        return std::make_shared<TipMu>(v,t->subst(sv,to));
    }
}