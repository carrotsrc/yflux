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
FunctionAst::FunctionAst() {
}

FunctionAst::FunctionAst(const FunctionAst& orig) {
}

FunctionAst::~FunctionAst() {
}

void FunctionAst::accept(IAstVisitor& visitor) {
    visitor.visit(*this);
}

