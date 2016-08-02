#ifndef FUNCTIONAST_HPP
#define FUNCTIONAST_HPP

#include "ast/ExprAst.hpp"
#include "ast/PrototypeAst.hpp"

namespace yfx {


class FunctionAst : public ExprAst {
public:
	FunctionAst(expr_uptr proto, expr_uptr body);
	FunctionAst(const FunctionAst& orig) = delete;
	FunctionAst(FunctionAst& orig) = delete;
	FunctionAst(FunctionAst&& orig);
	~FunctionAst();
	
	void accept(IAstVisitor& visitor) override;
	
	ExprAst& protoRef();
	expr_uptr proto();
	
	ExprAst& bodyRef();
	expr_uptr body();

private:
	expr_uptr _proto, _body;
	
};

}
#endif /* FUNCTIONAST_HPP */

