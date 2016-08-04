#ifndef TOKENSTRINGS_HPP
#define TOKENSTRINGS_HPP


#include <map>

namespace yfx {
static std::map<TokenType, std::string> TokenStrings {
	{ TokenType::Unknown,				"Unknown"				},
	{ TokenType::Semicolon,				"Semicolon"				},
	{ TokenType::Comma,					"Comma"					},
	{ TokenType::Identifier,			"Identifier"			},
	{ TokenType::Float,					"FloatValue"			},
	{ TokenType::Integer,				"IntegerValue"			},
	{ TokenType::ArithmeticAdd,			"ArithmeticAdd"			},
	{ TokenType::ArithmeticSub,			"ArithmeticSub"			},
	{ TokenType::ArithmeticMul,			"ArithmeticMul"			},
	{ TokenType::ArithmeticDiv,			"ArithmeticDiv"			},
	{ TokenType::ArithmeticModulo,		"ArithmeticModulo"		},		
	{ TokenType::LeftParen,				"LeftParens"			},
	{ TokenType::RightParen,			"RightParens"			},
	{ TokenType::OperatorBind,			"OperatorBind"			},
	{ TokenType::RelationalEquality,	"RelationalEquality"	},
	{ TokenType::RelationalGreater,		"RelationalGreater"		},
	{ TokenType::RelationalGreaterEqual,"RelationalGreaterEqual"},
	{ TokenType::RelationalLess,		"RelationalLess"		},
	{ TokenType::RelationalLessEqual,	"RelationalLessEqual"	},
	{ TokenType::RelationalNotEquality,	"RelationalNotEquality" },
	{ TokenType::QualifierMutable,		"RelationalNotEquality" },
	
};

}
#endif /* TOKENSTRINGS_HPP */