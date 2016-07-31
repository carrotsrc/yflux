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
    }
    
    // Identifier
    if(isalpha(_ch)) {
        ident.push_back(_ch);
        nextChar();
        while(isalnum(_ch)) { 
            ident.push_back(_ch);
            nextChar();
        }
        //rewindChar();
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

    return Token(TokenType::Unknown);
}

const Token YfxToken::processIdent(std::string& ident) {
    
    auto it = _primitives.find(ident);
    if( it != std::end(_primitives)) {
        Token t(TokenType::PrimitiveType);
        t.primitive = it->second;
        return t;
    }
    
    // Keywords
    if(ident == "func") {
        _state.push(Mode::LhsFunctionDeclare);
        return Token(TokenType::FunctionDeclare); 
    }
    if(ident == "let") {
        _state.push(Mode::LhsVariableDeclare);
        return Token(TokenType::VariableDeclare); 
    }
    
    // Otherwise it's an Ident
    Token t(TokenType::Identifier);
    t.str = ident;
    
    return t;
}

const Token YfxToken::processSpecTilde() {
    auto t = extractNext();
    _bank.push(t);
    
    
    switch(t.type) {
        case TokenType::PrimitiveType:
            _state.push(Mode::RhsTypeSpecifier);
            return Token(TokenType::TypeSpecifier);
            
        default: return Token(TokenType::OperatorBitwiseNot);
    }
}

const Token YfxToken::processSpecPerc() {
    switch(_state.top()) {
        case Mode::LhsVariableDeclare: return Token(TokenType::QualifierMutable);
        default: return Token(TokenType::OperatorModulus);
    }
}

const Token YfxToken::processSpecEquals() {
    auto ch = _source->peekChar();
    
    switch(_state.top()) {
        case Mode::LhsVariableDeclare:
            _state.push(Mode::RhsVariableBind);
            return Token(TokenType::OperatorBind);

        default: break;
    }
    switch(ch) {
        case '=':
            _source->closeDelta();
            return Token(TokenType::OperatorEquality);

        default: return Token(TokenType::Unknown);
    }
    
}

const Token YfxToken::processSpecComma() {
    if(_state.top() == Mode::RhsVariableBind
    || _state.top() == RhsTypeSpecifier) {
        while(_state.top() != Mode::LhsVariableDeclare) {
            _state.pop();
        }
    }
    
    return Token(TokenType::Comma);
}

const Token YfxToken::processSpecSemi() {
    // End of expression, pop till in scope
    while(_state.top() != Mode::LhsFuncScope
    && _state.top() != Mode::LhsModuleScope
    && _state.top() != Mode::LhsGlobalScope) {
        _state.pop();
    }

    return Token(TokenType::Semicolon);
}





