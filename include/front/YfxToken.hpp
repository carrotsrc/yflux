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
	const Token peekToken();
	
	
	enum Mode {
		LhsGlobalScope,
		LhsModuleScope,
		LhsFuncScope,
		LhsExprScope,
		
		LhsVariableDeclare,
		LhsFunctionDeclare,
		
		RhsVariableBind,
		RhsTypeSpecifier,
		RhsPrimary,
		
		FuncFormalParams,
		FuncActualParams,
	};
	
	void push(YfxToken::Mode mode);
	void pop();
	YfxToken::Mode top();
	
	
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
	
	const Token processSpecLessThan();
	const Token processSpecGreaterThan();
	const Token processSpecAdd();
	const Token processSpecSub();
	const Token processSpecMul();
	

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

using SynMode = YfxToken::Mode;
}
#endif /* SOURCEPROCESSOR_HPP */

