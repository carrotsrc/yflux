#include "ast/DeclareAst.hpp"
using namespace yfx;
        

DeclareAst::DeclareAst(expr_uptr variable, expr_uptr binding)
    : _variable(std::move(variable)), _binding(std::move(binding))
{ }

DeclareAst::DeclareAst(DeclareAst&& orig)
    : _variable(std::move(orig._variable)), _binding(std::move(orig._binding))
{ }

DeclareAst::~DeclareAst() {
}

void DeclareAst::accept(IAstVisitor& visitor) {
    visitor.visit(*this);
}

expr_uptr DeclareAst::Binding() {
    return std::move(_binding);
}

ExprAst& DeclareAst::bindingRef() {
    return *_binding;
}

expr_uptr DeclareAst::variable() {
    return std::move(_variable);
}

ExprAst& DeclareAst::variableRef() {
    return *_variable;
}

bool DeclareAst::hasBinding() {
    if(!_binding) return false;
    
    return true;
}





