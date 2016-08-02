/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FunctionAst.cpp
 * Author: cfg
 * 
 * Created on 30 July 2016, 16:14
 */

#include "ast/FunctionAst.hpp"
using namespace yfx;
FunctionAst::FunctionAst(expr_uptr proto, expr_uptr body)
    : _proto(std::move(proto)), _body(std::move(body))
{ }

FunctionAst::FunctionAst(FunctionAst&& orig) 
    : _proto(std::move(orig._proto)), _body(std::move(orig._body))
{ }

FunctionAst::~FunctionAst()
{ }

void FunctionAst::accept(IAstVisitor& visitor) {
    visitor.visit(*this);
}

expr_uptr FunctionAst::proto() {
    return std::move(_proto);
}

ExprAst& FunctionAst::protoRef() {
    return *_proto;
}

expr_uptr FunctionAst::body() {
    return std::move(_body);
}

ExprAst& FunctionAst::bodyRef() {
    return *_body;
}







