#include "ast/ScopeBlockAst.hpp"


using namespace yfx;

ScopeBlockAst::ScopeBlockAst()
{ }

ScopeBlockAst::ScopeBlockAst(ScopeBlockAst&& orig)

{ }

ScopeBlockAst::~ScopeBlockAst()
{ }

void ScopeBlockAst::accept(IAstVisitor& visitor) {
    visitor.visit(*this);
}

void ScopeBlockAst::push(expr_uptr expression) {
    _block.push_back(std::move(expression));
}

ScopeBlockAst::ScopeBlock& ScopeBlockAst::blockRef() {
    return _block;
}

ScopeBlockAst::ScopeBlock ScopeBlockAst::block() {
    return std::move(_block);
}

ScopeBlockAst::iterator ScopeBlockAst::begin() {
    return _block.begin();
}

ScopeBlockAst::iterator ScopeBlockAst::end() {
    return _block.end();
}




