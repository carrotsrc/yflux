#ifndef PROTOTYPEAST_HPP
#define PROTOTYPEAST_HPP

#include "ExprAst.hpp"

namespace yfx {

class PrototypeAst : public ExprAst {
public:
	typedef std::pair<std::string,Token> FormalParameter;
public:
	PrototypeAst(std::string name,
				 std::vector<FormalParameter> args);

	PrototypeAst(const PrototypeAst& orig);
	~PrototypeAst();
	
	void accept(IAstVisitor& visitor) override;
	
	std::string& name();
	std::vector<FormalParameter>& args();
private:
	std::string _name;
	std::vector<FormalParameter> _args;
};

}
#endif /* PROTOTYPEAST_HPP */

