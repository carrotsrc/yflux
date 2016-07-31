#ifndef VARIABLEAST_HPP
#define VARIABLEAST_HPP

#include "ExprAst.hpp"

namespace yfx {

class VariableAst : public ExprAst {
public:
	VariableAst(std::string& name, bool mut);
	VariableAst(const VariableAst& orig);
	
	const std::string& name();
	bool mut();
	
	void accept(IAstVisitor& visitor) override;

private:
	std::string	  _name;
	bool		  _mut;
};

}

#endif /* VARIABLEAST_HPP */

