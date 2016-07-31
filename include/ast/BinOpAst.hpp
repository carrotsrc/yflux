/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinOpAst.hpp
 * Author: cfg
 *
 * Created on 31 July 2016, 14:32
 */

#ifndef BINOPAST_HPP
#define BINOPAST_HPP

#include "ast/ExprAst.hpp"


namespace yfx {

class BinOpAst : public ExprAst{
public:
	BinOpAst(TokenType op, expr_uptr lhs, expr_uptr rhs);
	BinOpAst(const BinOpAst& orig) = delete;
	BinOpAst(BinOpAst& orig) = delete;
	BinOpAst(BinOpAst&& orig);

	~BinOpAst();

	ExprAst& lhsRef();
	ExprAst& rhsRef();
	
	expr_uptr lhs();
	expr_uptr rhs();
	
	TokenType op();
	
	void accept(IAstVisitor& visitor);

private:
	TokenType _op;
	expr_uptr _lhs, _rhs;
};

}
#endif /* BINOPAST_HPP */

