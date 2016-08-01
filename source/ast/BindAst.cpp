/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BindAst.cpp
 * Author: cfg
 * 
 * Created on 01 August 2016, 14:29
 */

#include "ast/BindAst.hpp"
using namespace yfx;
BindAst::BindAst(expr_uptr variable, expr_uptr binding)
    : _variable(std::move(variable)), _binding(std::move(binding))
{ }

BindAst::BindAst(BindAst&& orig)
    : _variable(std::move(orig._variable)), _binding(std::move(orig._binding))
{ }

BindAst::~BindAst() {
    
}

void BindAst::accept(IAstVisitor& visitor) {
    visitor.visit(*this);
}

expr_uptr BindAst::binding() {
    return std::move(_binding);
}

ExprAst& BindAst::bindingRef() {
    return *_binding;
}

expr_uptr BindAst::variable() {
    return std::move(_variable);
}

ExprAst& BindAst::variableRef() {
    return *_variable;
}



