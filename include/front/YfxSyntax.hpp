#ifndef YFXSYNTAX_HPP
#define YFXSYNTAX_HPP
#include "ast/visitors/IAstVisitor.hpp"
#include "ast/Ast.hpp"
#include "front/YfxToken.hpp"
namespace yfx {
	

class YfxSyntax {
public:
	YfxSyntax();
	YfxSyntax(const YfxSyntax& orig);
	virtual ~YfxSyntax();
	
	void addVisitor(std::unique_ptr<IAstVisitor> visitor);
	void setBuffer(std::unique_ptr<ISourceContainer> source);
	
	void run();
private:
	std::vector< std::unique_ptr<IAstVisitor> > _visitors;
	YfxToken _processor;
	Token _token;
	
	void runTopLevel();
	expr_uptr parseTopLevel();
	
	expr_uptr parsePrimary();
	expr_uptr parseVariableDeclare();
	expr_uptr parseValueBind();
	
	expr_uptr parseIntegerValue(Token& v, PrimitiveType t);
	expr_uptr parseFloatValue(Token& v, PrimitiveType t);
	
	inline Token nextToken();
	
	inline TokenType type();
	
	template<class AstType>
	void visit(AstType& t);
};

Token YfxSyntax::nextToken() {
	_token = _processor.nextToken();
	return _token;
}

TokenType YfxSyntax::type() {
		return _token.type;
}

template<class AstType>
void YfxSyntax::visit(AstType& t) {
	for(auto& v : _visitors) {
		t.accept(*v);
	}
}
	
}
#endif /* YFXSYNTAX_HPP */

