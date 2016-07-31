#ifndef CALLAST_HPP
#define CALLAST_HPP

#include "ast/ExprAst.hpp"


namespace yfx {

class CallAst : public ExprAst {
public:
	CallAst(std::string& calling, std::vector<expr_uptr> args);
	CallAst(const CallAst& orig) = delete;
	CallAst(CallAst& orig) = delete;
	CallAst(CallAst&& orig);
	~CallAst();
	
	void accept(IAstVisitor& visitor) override;

	const std::string& calling();
	const std::vector<expr_uptr>& argsRef();
	std::vector<expr_uptr> args();
private:	
	std::string _calling;
	std::vector<expr_uptr> _args;
};

}
#endif /* CALLAST_HPP */

