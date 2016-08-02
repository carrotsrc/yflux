#ifndef LANGCOMMON_HPP
#define LANGCOMMON_HPP
#include <string>
//#include <cstdint>
#include <stdexcept>
#include <memory>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"



namespace yfx {

enum class TokenType {
	Undefined,
	Unknown,

	Eof,
	
	Semicolon,
	Comma,

	LeftParen,
	RightParen,
	LeftBrace,
	RightBrace,
	LeftSquare,
	RightSquare,
	
	Identifier,
	TypeSpecifier,
	
	FunctionDeclare,
	VariableDeclare,
	
	PrimitiveType,

	Integer,
	Float,
	
	OperatorBind,

	BitwiseNot,
	BitwiseAnd,	
	BitwiseOr,
	
	ArithmeticAdd,
	ArithmeticSub,
	ArithmeticMul,
	ArithmeticDiv,
	ArithmeticModulo,
	ArithemeticIncrement,
	ArithemeticDecrement,
	
	RelationalLess,
	RelationalLessEqual,
	RelationalGreater,
	RelationalGreaterEqual,
	RelationalEquality,
	RelationalNotEquality,
	
	LogicalAnd,
	LogicalOr,
	LogicalNot,
	
	QualifierMutable,	
};


enum class PrimitiveType {
	Unknown,
	I16, I32, I64,
	U16, U32, U64,
	F32, F64,
	Bool, Char
};

struct Token {
	Token()
		: type(TokenType::Undefined), str(), i64(0), f32(0.0), d64(0.0) 
	{};
	
	Token(TokenType type)
		: type(type), str(), i64(0), f32(0.0), d64(0.0)
	{};
	
	Token(TokenType type, std::string tokstr)
		: type(type), str(tokstr), i64(0), f32(0.0), d64(0.0)
	{ }
	TokenType     type;
	PrimitiveType primitive;
	std::string   str;
	std::int64_t  i64;
	float         f32;
	double        d64;
};

}

#endif /* LANGCOMMON_HPP */