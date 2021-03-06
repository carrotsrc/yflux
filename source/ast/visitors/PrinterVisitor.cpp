
#include "ast/visitors/PrinterVisitor.hpp"
#include "ast/BinOpAst.hpp"
#include "ast/CallAst.hpp"
#include "TokenStrings.hpp"
#include "ast/ScopeBlockAst.hpp"
#include <cstdint>
#include <iostream>
using namespace yfx;

PrinterVisitor::PrinterVisitor() {
    _depth = 0;
}

PrinterVisitor::PrinterVisitor(const PrinterVisitor& orig) {
}

PrinterVisitor::~PrinterVisitor() {
}

void PrinterVisitor::visit(Int16Ast& node) {
    printTab();
    std::cout 
        << "i16 " << node.value() << "\n";
        
}

void PrinterVisitor::visit(Int32Ast& node) {
    printTab();
    std::cout 
        << "i32 " << node.value() << "\n";
}

void PrinterVisitor::visit(Int64Ast& node) {
        printTab();
        std::cout 
        << "i64 " << node.value() << "\n";
}

void PrinterVisitor::visit(UInt16Ast& node) {
    printTab();
    std::cout 
        << "u16 " << node.value() << "\n";
}

void PrinterVisitor::visit(UInt32Ast& node) {
    printTab();
    std::cout 
        << "u32 " << node.value() << "\n";
}

void PrinterVisitor::visit(UInt64Ast& node) {
    printTab();
    std::cout 
        << "u64 " << node.value() << "\n";
}

void PrinterVisitor::visit(Float32Ast& node) {
    printTab();
    std::cout 
        << "f32 " << node.value() << "\n";
}

void PrinterVisitor::visit(Float64Ast& node) {
    printTab();
    std::cout 
        << "f64 " << node.value() << "\n";
}

void PrinterVisitor::visit(VariableAst& node) {
    printTab();
    std::cout 
        << "Variable `" << node.name() << "` "
        << " ~" << node.type().str
        << " (mutable: " << node.mut()
        << ")\n";
}

void PrinterVisitor::visit(FunctionAst& node) {
    printTab();
    std::cout
        << "Function\n";
    
    _depth++;
    node.protoRef().accept(*this);
    _depth--;
    
    printTab();
    std::cout
        << " + Body\n";
    
    _depth++;
    node.bodyRef().accept(*this);
    _depth--;
}

void PrinterVisitor::visit(BinOpAst& node) {
    printTab();
    std::cout 
        << "Binary Operation node \n";
    printTab();
    std::cout 
        << "   Operator " << TokenStrings[node.op()] << "\n";

    printTab();
    std::cout 
        << " + LHS:\n";
    _depth++;
    node.lhsRef().accept(*this);
    _depth--;
    
    if(node.hadRhs()) {
        printTab();
        std::cout 
            << " + RHS:\n";
        _depth++;
        node.rhsRef().accept(*this);
        _depth--;
    }
}

void PrinterVisitor::visit(CallAst& node) {
    printTab();
    std::cout 
        << "Call node `"<<node.calling() <<"()`" 
        <<"(num args: "<< node.argsRef().size()
        << "): \n";
    _depth++;
        for(auto& arg : node.argsRef()) {
            arg->accept(*this);
        }
    _depth--;
}

void PrinterVisitor::visit(BindAst& node) {
    printTab();
    std::cout 
        << "Bind for:\n";
    
    _depth++;
    node.variableRef().accept(*this);
    _depth--;
    
    printTab();
    std::cout 
        << " + Primary:\n";
    _depth++;
    node.bindingRef().accept(*this);
    _depth--;
}

void PrinterVisitor::visit(DeclareAst& node) {
    printTab();
    std::cout 
        << "Declaration:\n";
    
    _depth++;
    node.variableRef().accept(*this);
    _depth--;
    

    
    if(node.hasBinding()) {
        printTab();
        std::cout 
            << " + With Binding:\n";
        _depth++;
        node.bindingRef().accept(*this);
        _depth--;
    }
    
}

void PrinterVisitor::printTab() {
    for(auto i = 0u; i < _depth; i++) {
        std::cout << "\t";
    }
}

void PrinterVisitor::visit(PrototypeAst& node) {
    printTab();
        std::cout 
            << "Prototype "
            << node.name() << "(";
        
        auto args = node.args();
        for(auto i = std::begin(args); i != std::end(args); i++) {
            std::string mut("");
            if(std::get<2>(*i)) {
                mut += "%";
            }
            std::cout << mut << std::get<0>(*i) <<" ~" << std::get<1>(*i).str;
            if(i+1 != std::end(args))
                std::cout << ", ";
        }
        
         std::cout << ")\n";
}

void PrinterVisitor::visit(ScopeBlockAst& node) {
    printTab();
        std::cout  << "Scope Block\n";
        
        _depth++;
        for(auto& e : node.blockRef()) {
            if(!e) continue;
            e->accept(*this);
        }
        _depth--;
}