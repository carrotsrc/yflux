#ifndef FLOATAST_HPP
#define FLOATAST_HPP
#include <cstdint>

#include "ast/ExprAst.hpp"
namespace yfx {
	
template<typename DataType, int Bits>
class FloatAst : public ExprAst {
public:
	FloatAst(DataType value)
		: _value(value)
	{ }

	FloatAst(const FloatAst& orig)
		: _value(orig._value)
	{ }
	
	~FloatAst() { }
	
    DataType value() {
		return _value;
	};
	
	int width() {
		return Bits;
	}

	void accept(IAstVisitor& visitor) override {
		visitor.visit(*this);
	}

private:
	DataType _value; 

};

}
#endif /* INTEGERAST_HPP */

