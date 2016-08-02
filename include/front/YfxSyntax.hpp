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
	Token _token, _last, _ident;
	
	void runTopLevel();
	
	expr_uptr parseTopLevel();
	expr_uptr parseExpression();
	
	expr_uptr parsePrimary();
	expr_uptr parseVariableDeclare();
	expr_uptr parseFunctionDeclare();
	expr_uptr parseFunctionPrototype();
	expr_uptr parseScopeBody();
	
	
	expr_uptr parseValueBind(expr_uptr var);
	expr_uptr parseIdentifier();
	
	expr_uptr parseIntegerValue(Token& v, PrimitiveType t);
	expr_uptr parseFloatValue(Token& v, PrimitiveType t);
	
	expr_uptr parseBinaryOps(int xprec, expr_uptr lhs);
	
	
	int getPrecedence(TokenType token);
	
	inline Token nextToken();
	inline TokenType type();
	inline void push(SynMode mode);
	inline void pop();
	void popToScope();
	void popToMode(SynMode mode);
	void popBeyond(SynMode mode);
	inline YfxToken::Mode top();
	
	template<class AstType>
	void visit(AstType& t);
	
	std::map<TokenType, int> _precedence = {
		{ TokenType::RelationalLess, 10 },
		{ TokenType::ArithmeticAdd,  20 },
		{ TokenType::ArithmeticSub,  30 },
		{ TokenType::ArithmeticMul,  40 },
	};
};

Token YfxSyntax::nextToken() {
	_last = _token;
	_token = _processor.nextToken();
	return _token;
}

TokenType YfxSyntax::type() {
		return _token.type;
}

void YfxSyntax::push(SynMode mode) {
	_processor.push(mode);
}

void YfxSyntax::pop() {
	_processor.pop();
}

inline SynMode YfxSyntax::top() {
	return _processor.top();
}

template<class AstType>
void YfxSyntax::visit(AstType& t) {
	for(auto& v : _visitors) {
		t.accept(*v);
	}
}
	
}
#endif /* YFXSYNTAX_HPP */

