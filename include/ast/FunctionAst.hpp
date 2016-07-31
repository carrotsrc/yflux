/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FunctionAst.hpp
 * Author: cfg
 *
 * Created on 30 July 2016, 16:14
 */

#ifndef FUNCTIONAST_HPP
#define FUNCTIONAST_HPP

#include "ast/ExprAst.hpp"

namespace yfx {


class FunctionAst : ExprAst {
public:
	FunctionAst();
	FunctionAst(const FunctionAst& orig);
	virtual ~FunctionAst();
	void accept(IAstVisitor& visitor) override;

private:

};

}
#endif /* FUNCTIONAST_HPP */

