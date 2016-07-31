#ifndef EXPRAST_HPP
#define EXPRAST_HPP
//#include "llvm/IR/IRBuilder.h"
#include "LangCommon.hpp"
#include "ast/visitors/IAstVisitor.hpp"

namespace yfx {

class ExprAst {
public:
	ExprAst();
	ExprAst(const ExprAst& orig);
	virtual ~ExprAst();
	virtual void accept(IAstVisitor& visitor) = 0;
        
protected:

private:
};

using expr_uptr = std::unique_ptr<ExprAst>;

}
#endif /* EXPRAST_HPP */

