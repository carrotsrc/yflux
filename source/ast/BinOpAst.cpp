#include "ast/BinOpAst.hpp"

using namespace yfx;

BinOpAst::BinOpAst(TokenType op, expr_uptr lhs, expr_uptr rhs)
    : _op(op), _lhs(std::move(lhs)), _rhs(std::move(rhs))
{ }

BinOpAst::BinOpAst(BinOpAst&& orig) 
    : _op(orig._op), _lhs(std::move(orig._lhs)), _rhs(std::move(orig._rhs))
{ }

BinOpAst::~BinOpAst() {
}

ExprAst& BinOpAst::lhsRef() {
    return *_lhs;
}

ExprAst& BinOpAst::rhsRef() {
    return *_rhs;
}

expr_uptr BinOpAst::lhs() {
    return std::move(_lhs);
}

expr_uptr BinOpAst::rhs() {
    return std::move(_rhs);
}

TokenType BinOpAst::op() {
    return _op;
}

void BinOpAst::accept(IAstVisitor& visitor) {
    visitor.visit(*this);
}

bool BinOpAst::hadRhs() {
    if(!_rhs) return false;
    
    return true;
}

