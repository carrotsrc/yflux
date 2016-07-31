#ifndef PRINTERVISITOR_HPP
#define PRINTERVISITOR_HPP
#include "ast/visitors/IAstVisitor.hpp"
#include "ast/Ast.hpp"

namespace yfx {
	

class PrinterVisitor : public IAstVisitor {
public:
	PrinterVisitor();
	PrinterVisitor(const PrinterVisitor& orig);
	virtual ~PrinterVisitor();
	
	void visit(Int16Ast& node) override; 
	void visit(Int32Ast& node) override;
	void visit(Int64Ast& node) override;
	
	void visit(UInt16Ast& node) override;
	void visit(UInt32Ast& node) override;
	void visit(UInt64Ast& node) override;
	
	void visit(Float32Ast& node) override;
	void visit(Float64Ast& node) override;
	
	void visit(VariableAst& node) override;
	void visit(FunctionAst& node) override;
private:

};

}
#endif /* PRINTERVISITOR_HPP */

