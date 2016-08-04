#include <iostream>
#include "ast/VariableAst.hpp"
#include "LangCommon.hpp"
using namespace yfx;

using DataType = VariableAst::DataType;

VariableAst::VariableAst(std::string& name, bool mut)
    : _name(name), _mut(mut), _type()
{ }

VariableAst::VariableAst(std::string& name, bool mut, DataType type)
    : _name(name), _mut(mut), _type(type)
{ }

VariableAst::VariableAst(const VariableAst& orig)
    : _name(orig._name), _mut(orig._mut), _type(orig._type)
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

DataType VariableAst::type() {
    return _type;
}

