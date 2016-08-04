#ifndef SCOPEBLOCKAST_HPP
#define SCOPEBLOCKAST_HPP
#include "ast/ExprAst.hpp"
namespace yfx {

class ScopeBlockAst : public ExprAst {
public:
	typedef std::vector<expr_uptr> ScopeBlock;
	typedef ScopeBlock::iterator iterator;
	typedef ScopeBlock::const_iterator const_iterator;
public:
	ScopeBlockAst();
	ScopeBlockAst(const ScopeBlockAst& orig) = delete;
	ScopeBlockAst(ScopeBlockAst& orig) = delete;
	ScopeBlockAst(ScopeBlockAst&& orig);
	
	~ScopeBlockAst();
	void accept(IAstVisitor& visitor) override;
	
	void push(expr_uptr expression);
	void pop();
	ScopeBlock& blockRef();
	ScopeBlock block();
	
	iterator begin();
	iterator end();

private:
	
	std::vector<expr_uptr> _block;
	

};

}
#endif /* SCOPEBLOCKAST_HPP */

