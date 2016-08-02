#ifndef PROTOTYPEAST_HPP
#define PROTOTYPEAST_HPP

#include "ExprAst.hpp"

namespace yfx {

class PrototypeAst : public ExprAst {
public:
	PrototypeAst(std::string name, std::vector<std::string> args);
	PrototypeAst(const PrototypeAst& orig);
	~PrototypeAst();
	
	void accept(IAstVisitor& visitor) override;

	
	std::string& name();
	std::vector<std::string>& args();
private:
	std::string _name;
	std::vector<std::string> _args;
};

}
#endif /* PROTOTYPEAST_HPP */

