
#ifndef IASTVISITOR_HPP
#define IASTVISITOR_HPP

// Forward Declarations
#include "ast/AstForward.hpp"

namespace yfx {


class IAstVisitor {
public:
	virtual void visit(Int16Ast& node) = 0;
	virtual void visit(Int32Ast& node) = 0;
	virtual void visit(Int64Ast& node) = 0;
	
	virtual void visit(UInt16Ast& node) = 0;
	virtual void visit(UInt32Ast& node) = 0;
	virtual void visit(UInt64Ast& node) = 0;
	
	
	virtual void visit(Float32Ast& node) = 0;
	virtual void visit(Float64Ast& node) = 0;
	
	virtual void visit(VariableAst& node) = 0;
	virtual void visit(FunctionAst& node) = 0;
	virtual void visit(CallAst& node) = 0;
	virtual void visit(BinOpAst& node) = 0;
	virtual void visit(BindAst& node) = 0;
	virtual void visit(DeclareAst& node) = 0;
	virtual void visit(PrototypeAst& node) = 0;
};

}
#endif /* IASTVISITOR_HPP */

