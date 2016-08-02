#include "ast/PrototypeAst.hpp"

using namespace yfx;

PrototypeAst::PrototypeAst(std::string name, std::vector<std::string> args)
    : _name(name), _args(args)
{ }

PrototypeAst::PrototypeAst(const PrototypeAst& orig)
    : _name(orig._name), _args(orig._args)
{ }

PrototypeAst::~PrototypeAst()
{
}

std::vector<std::string>& PrototypeAst::args() {
    return _args;
}

std::string& PrototypeAst::name() {
    return _name;
}

void PrototypeAst::accept(IAstVisitor& visitor) {
    visitor.visit(*this);
}