#include <iostream>
#include "ast/VariableAst.hpp"
#include "LangCommon.hpp"
using namespace yfx;

VariableAst::VariableAst(std::string& name, bool mut)
    : _name(name), _mut(mut)
{ }

VariableAst::VariableAst(const VariableAst& orig)
    : _name(orig._name), _mut(orig._mut)
{ }
	
const std::string& VariableAst::name() {
    return _name;
}

void VariableAst::accept(IAstVisitor& visitor) {
    visitor.visit(*this);
}

bool VariableAst::mut() {
    return _mut;
}
