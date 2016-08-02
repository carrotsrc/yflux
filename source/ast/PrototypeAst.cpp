#include "ast/PrototypeAst.hpp"

using namespace yfx;
using FormalParameter = PrototypeAst::FormalParameter;
PrototypeAst::PrototypeAst(std::string name,
                           std::vector<FormalParameter> args)
    : _name(name), _args(args)
{ }

PrototypeAst::PrototypeAst(const PrototypeAst& orig)
    : _name(orig._name), _args(orig._args)
{ }

PrototypeAst::~PrototypeAst()
{ }

std::vector<FormalParameter>& PrototypeAst::args() {
    return _args;
}

std::string& PrototypeAst::name() {
    return _name;
}

void PrototypeAst::accept(IAstVisitor& visitor) {
    visitor.visit(*this);
}