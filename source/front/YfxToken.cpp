#include "front/YfxToken.hpp"
#include "ast/FloatAst.hpp"
#include <cctype>

using namespace yfx;

YfxToken::YfxToken() {
}

YfxToken::YfxToken(const YfxToken& orig) {
}

YfxToken::~YfxToken() {
}

void YfxToken::setBuffer(std::unique_ptr<ISourceContainer> source) {
    _source = std::move(source);
    _ch = ' ';
    _chprev = ' ';
    
    _state.push(Mode::LhsGlobalScope);
}

const Token YfxToken::nextToken() {
    if(!_source) return Token(TokenType::Eof);
    if(!_bank.empty()) {
        auto t = _bank.front();
        _bank.pop();
        return t;
    }

    return extractNext();
}

const Token YfxToken::peekToken() {
    auto t = extractNext();
    _bank.push(t);
    return t;
}


const Token YfxToken::extractNext() {
    std::string ident, number;
    unsigned int dp = 0;
    while(isspace(_ch)) nextChar(); 
    
    if(_ch == EOF) return Token(TokenType::Eof);

    // special _chars
    switch(_ch) {
        case '~': nextChar(); return processSpecTilde();
        case '%': nextChar(); return processSpecPerc();
        case '=': nextChar(); return processSpecEquals();
        case ',': nextChar(); return processSpecComma();
        case ';': nextChar(); return processSpecSemi();
        
        case '<': nextChar(); return processSpecLessThan();
        
        case '*': nextChar(); return processSpecMul();
        case '+': nextChar(); return processSpecAdd();
        case '-': nextChar(); return processSpecSub();
        case '(': nextChar(); return Token(TokenType::LeftParen);
        case ')': nextChar(); return Token(TokenType::RightParen);
        
        case '{': nextChar(); return Token(TokenType::LeftBrace);
        case '}': nextChar(); return Token(TokenType::RightBrace);
    }
    
    // Identifier
    if(isalpha(_ch)) {
        ident.push_back(_ch);
        nextChar();
        while(isalnum(_ch)) { 
            ident.push_back(_ch);
            nextChar();
        }

        return processIdent(ident);
    }
    
    // Number
    if(isdigit(_ch)) {
        
        number.push_back(_ch);
        nextChar();
        
        // get number
        while(isdigit(_ch) || _ch == '.') {
            if(_ch == '.'){ dp++; }
            number.push_back(_ch);
            nextChar();
        }
        
        Token t;        
        if(dp) {
            t.type = TokenType::Float;
        } else {
            t.type = TokenType::Integer;
        }

        t.str = number;
        return t;
    }
    std::string out;
    out.push_back(_ch);
    return Token(TokenType::Unknown, out);
}

const Token YfxToken::processIdent(std::string& ident) {
    
    auto it = _primitives.find(ident);
    if( it != std::end(_primitives)) {
        Token t(TokenType::PrimitiveType);
        t.primitive = it->second;
        t.str = ident;
        return t;
    }
    
    // Keywords
    if(ident == "func") {        
        return Token(TokenType::FunctionDeclare); 
    }
    if(ident == "let") {
        return Token(TokenType::VariableDeclare); 
    }
    
    // Otherwise it's an Ident
    Token t(TokenType::Identifier);
    t.str = ident;
    
    return t;
}

const Token YfxToken::processSpecTilde() {
    
    if(top() == SynMode::LhsVariableDeclare
    || top() == SynMode::LhsFunctionDeclare) {
        return Token(TokenType::TypeSpecifier);
    }
    return Token(TokenType::BitwiseNot);


}

const Token YfxToken::processSpecPerc() {

    switch(_state.top()) {
        
        case Mode::LhsVariableDeclare:
        case Mode::LhsFunctionDeclare:
            return Token(TokenType::QualifierMutable);

        default: return Token(TokenType::ArithmeticModulo);
    }
}

const Token YfxToken::processSpecEquals() {
    
    switch(_state.top()) {
        case Mode::LhsVariableDeclare:
            return Token(TokenType::OperatorBind);

        default: break;
    }

    auto ch = _source->peekChar();
    switch(ch) {
        case '=':
            _source->closeDelta();
            return Token(TokenType::RelationalEquality);

        default: {
            std::string out;
            out.push_back(_ch);
            return Token(TokenType::Unknown, std::string(out));
        }
    }
    
}

const Token YfxToken::processSpecComma() {
    return Token(TokenType::Comma);
}

const Token YfxToken::processSpecSemi() {
    return Token(TokenType::Semicolon);
}

const Token YfxToken::processSpecLessThan() {
    return Token(TokenType::RelationalLess);
}

const Token YfxToken::processSpecGreaterThan() {
    return Token(TokenType::RelationalGreater);
}

const Token YfxToken::processSpecMul() {
    return Token(TokenType::ArithmeticMul);
}

const Token YfxToken::processSpecAdd() {
    return Token(TokenType::ArithmeticAdd);
}

const Token YfxToken::processSpecSub() {
    return Token(TokenType::ArithmeticSub);
}

void YfxToken::push(YfxToken::Mode mode) {
    _state.push(mode);
}

void YfxToken::pop() {
    _state.pop();
}

YfxToken::Mode YfxToken::top() {
    return _state.top();
}








