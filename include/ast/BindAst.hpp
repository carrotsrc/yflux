/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BindAst.hpp
 * Author: cfg
 *
 * Created on 01 August 2016, 14:29
 */

#ifndef BINDAST_HPP
#define BINDAST_HPP

#include "ast/ExprAst.hpp"

namespace yfx {

class BindAst : public ExprAst {
public:
	BindAst(expr_uptr variable, expr_uptr binding);
	BindAst(const BindAst& orig) = delete;
	BindAst(BindAst& orig) = delete;
	BindAst(BindAst&& orig);
	
	~BindAst();
	
	void accept(IAstVisitor& visitor) override;
	ExprAst& variableRef();
	ExprAst& bindingRef();
	
	expr_uptr variable();
	expr_uptr binding();
	

private:
	
	expr_uptr _variable, _binding;

};

}
#endif /* BINDAST_HPP */

