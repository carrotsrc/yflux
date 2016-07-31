#ifndef SOURCEPROCESSOR_HPP
#define SOURCEPROCESSOR_HPP
#include <queue>
#include <stack>
#include "front/ISourceContainer.hpp"
#include <iostream>
namespace yfx {

class YfxToken {
public:
	YfxToken();
	YfxToken(const YfxToken& orig);
	~YfxToken();
	
	void setBuffer(std::unique_ptr<ISourceContainer> source);
	const Token nextToken();
	
	enum Mode {
		LhsGlobalScope,
		LhsModuleScope,
		LhsFuncScope,
		
		LhsVariableDeclare,
		LhsFunctionDeclare,
		
		RhsVariableBind,
		RhsTypeSpecifier,
	};
	
private:
	std::unique_ptr<ISourceContainer> _source;
	std::string _line, _strtok;
	signed char _ch, _chprev;
	std::string::const_iterator _it;
	std::queue<Token> _bank;
	std::stack<Mode> _state;
	
	inline signed char nextChar();
	inline void rewindChar();
	
	const Token aheadChar();
	const Token extractNext();
	
	const Token processIdent(std::string& ident);
	const Token processSpecTilde();
	const Token processSpecPerc();
	const Token processSpecEquals();
	const Token processSpecComma();
	const Token processSpecSemi();
	
	
	std::map<std::string, PrimitiveType> _primitives = {
		{ "i16", PrimitiveType::I16 },
		{ "i32", PrimitiveType::I32 },
		{ "i64", PrimitiveType::I64 },
		{ "u16", PrimitiveType::U16 },
		{ "u32", PrimitiveType::U32 },
		{ "u64", PrimitiveType::U64 },
		{ "f32", PrimitiveType::F32 },
		{ "f64", PrimitiveType::F64 },
		{ "bool", PrimitiveType::Bool },
		{ "char", PrimitiveType::Char },
	};
	
};


inline signed char YfxToken::nextChar() {
	
	_chprev = _ch;
	_ch = _source->getChar();
}

inline void YfxToken::rewindChar() {
	_ch = _source->rewindChar();
	
}
}
#endif /* SOURCEPROCESSOR_HPP */

