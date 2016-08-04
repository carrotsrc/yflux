#ifndef VARIABLEAST_HPP
#define VARIABLEAST_HPP

#include "ExprAst.hpp"

namespace yfx {

class VariableAst : public ExprAst {
public:
	typedef Token DataType;
public:
	VariableAst(std::string& name, bool mut);
	VariableAst(std::string& name, bool mut, DataType type);
	VariableAst(const VariableAst& orig);
	
	const std::string& name();
	bool mut();
	DataType type();
	
	void accept(IAstVisitor& visitor) override;

private:
	std::string	  _name;
	bool		  _mut;
	DataType	  _type;
};

}

#endif /* VARIABLEAST_HPP */

