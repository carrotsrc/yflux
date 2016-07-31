#ifndef INTEGERAST_HPP
#define INTEGERAST_HPP
#include <cstdint>

#include "ast/ExprAst.hpp"
namespace yfx {
	
template<typename DataType, int Bits, bool Signed>
class IntegerAst : public ExprAst {
public:
	IntegerAst(DataType value)
		: _value( static_cast<DataType>(value))
	{ }

	IntegerAst(const IntegerAst& orig)
		: _value(orig._value)
	{ }
	
	~IntegerAst() 
	{ }
		
    DataType value() {
		return _value;
	};
	
	int width() {
		return Bits;
	};
	
	bool isSigned() {
		return Signed;
	};
	
	void accept(IAstVisitor& visitor) override {
		visitor.visit(*this);
	}


private:
    DataType _value; 

};

}
#endif /* INTEGERAST_HPP */

