#ifndef DECLAREAST_HPP
#define DECLAREAST_HPP

#include "ExprAst.hpp"
#include "BindAst.hpp"


namespace yfx {

class DeclareAst : public ExprAst {
public:
	DeclareAst(expr_uptr variable, expr_uptr binding);
	DeclareAst(const DeclareAst& orig) = delete;
	DeclareAst(DeclareAst& orig) = delete;
	DeclareAst(DeclareAst&& orig);
	virtual ~DeclareAst();

	void accept(IAstVisitor& visitor) override;
	ExprAst& variableRef();
	ExprAst& bindingRef();
	
	bool hasBinding();
	
	expr_uptr variable();
	expr_uptr Binding();
private:
	expr_uptr _variable, _binding;
};

}
#endif /* DECLAREAST_HPP */

