
#include "ast/visitors/PrinterVisitor.hpp"
#include "ast/BinOpAst.hpp"
#include "ast/CallAst.hpp"
#include <cstdint>
#include <iostream>
using namespace yfx;

PrinterVisitor::PrinterVisitor() {
}

PrinterVisitor::PrinterVisitor(const PrinterVisitor& orig) {
}

PrinterVisitor::~PrinterVisitor() {
}

void PrinterVisitor::visit(Int16Ast& node) {
    std::cout 
        << "[Printer] i16 " << node.value() << "\n";
        
}

void PrinterVisitor::visit(Int32Ast& node) {
    std::cout 
        << "[Printer] i32 " << node.value() << "\n";
}

void PrinterVisitor::visit(Int64Ast& node) {
        std::cout 
        << "[Printer] i64 " << node.value() << "\n";
}

void PrinterVisitor::visit(UInt16Ast& node) {
    std::cout 
        << "[Printer] u16 " << node.value() << "\n";
}

void PrinterVisitor::visit(UInt32Ast& node) {
    std::cout 
        << "[Printer] u32 " << node.value() << "\n";
}

void PrinterVisitor::visit(UInt64Ast& node) {
    std::cout 
        << "[Printer] u64 " << node.value() << "\n";
}

void PrinterVisitor::visit(Float32Ast& node) {
    std::cout 
        << "[Printer] f32 " << node.value() << "\n";
}

void PrinterVisitor::visit(Float64Ast& node) {
    std::cout 
        << "[Printer] f64 " << node.value() << "\n";
}

void PrinterVisitor::visit(VariableAst& node) {
    std::cout 
        << "[Printer] Variable `" << node.name() << "` "
        << "(mutable: " << node.mut()
        << ")\n";
}

void PrinterVisitor::visit(FunctionAst& node) {
    std::cout
        << "Function node\n";
    
}

void PrinterVisitor::visit(BinOpAst& node) {
    std::cout 
        << "[Printer] Binary Op node\n";
}

void PrinterVisitor::visit(CallAst& node) {
    std::cout 
        << "[Printer] Call node `"<<node.calling() <<"()`" 
        <<"(num args: "<< node.argsRef().size()
        << "): \n";
        for(auto& arg : node.argsRef()) {
            std::cout << "\t";
            arg->accept(*this);
        }
}