#include <vector>
#include <iostream>
#include "front/YfxSyntax.hpp"
#include "ast/BinOpAst.hpp"
#include "ast/CallAst.hpp"

using namespace yfx;

YfxSyntax::YfxSyntax() {
}

YfxSyntax::YfxSyntax(const YfxSyntax& orig) {
}

YfxSyntax::~YfxSyntax() {
}

void YfxSyntax::addVisitor(std::unique_ptr<IAstVisitor> visitor) {
    _visitors.push_back(std::move(visitor));
}

void YfxSyntax::setBuffer(std::unique_ptr<ISourceContainer> source) {
    _processor.setBuffer(std::move(source));
}


void YfxSyntax::run() {
    runTopLevel();
}

void YfxSyntax::runTopLevel() {
    
    while(nextToken().type != TokenType::Eof) {
        parseTopLevel();
    } 
}

expr_uptr YfxSyntax::parseBinaryOps(int exPrec, expr_uptr lhs) {
    while(true) {
        auto tokPrec = getPrecedence(type());
        
        if(tokPrec < exPrec)
            return lhs;
        
        auto op = type();
        nextToken();
        auto rhs = parsePrimary();
        
        // if(!rhs) return nullptr;
        
        int nextPrec = getPrecedence(type());
        if(tokPrec < nextPrec) {
            rhs = parseBinaryOps(tokPrec+1, std::move(rhs));
            // if(!rhs) return nullptr;
        }
        
        lhs = expr_uptr(new BinOpAst(op, std::move(lhs), std::move(rhs)));
    }
}


expr_uptr YfxSyntax::parseTopLevel() {
    std::cout << "Parsing top level\n";
    while(type() != TokenType::Eof) {
        parseExpression();
        nextToken();
    }
}

expr_uptr YfxSyntax::parseExpression() {
    
    switch(type()) {
        case TokenType::VariableDeclare:
            push(YfxToken::Mode::LhsVariableDeclare);
            return parseVariableDeclare();
    }
    
    auto lhs = parsePrimary();
    return parseBinaryOps(0, std::move(lhs));
}

expr_uptr YfxSyntax::parsePrimary() {
    switch(type()) {
        case TokenType::Integer:
            return parseIntegerValue(_token, PrimitiveType::I32);
        case TokenType::Float:
            return parseFloatValue(_token, PrimitiveType::F32);
        case TokenType::Identifier:
            return parseIdentifier();
        default: return expr_uptr(nullptr);
    }
}

expr_uptr YfxSyntax::parseVariableDeclare() {
    nextToken();
    auto mut = false;
    std::string name;
    
    while(1) {
        switch(type()) {
            case TokenType::QualifierMutable:
                mut = true;
                nextToken();
                continue;
                break;
                
            case TokenType::Identifier:
                name = _token.str;
                break;

            default:
                std::cerr << "Syntax error on declaration, unexpected token" << std::endl;
                return expr_uptr(nullptr);
        }
        break;
    }
    nextToken();
    
    if(type() == TokenType::Semicolon) {
        popToScope();
        auto v = new VariableAst(name, mut);
        visit(*v);
        return expr_uptr(nullptr);
    }    
    
    if(type() == TokenType::OperatorBind) {
        push(YfxToken::RhsVariableBind);
        auto v = new VariableAst(name, mut);
        visit(*v);
        return  parseValueBind();
    }
}

expr_uptr YfxSyntax::parseIdentifier() {
    auto t = _token;
    nextToken();
    
    if(type() != TokenType::LeftParen) {
       auto v = std::make_unique<VariableAst>(t.str, false);
       visit(*v);
       return v;
    }
    
    // We are in a call
    
    nextToken();
    std::vector<expr_uptr> args;
    
    if(type() != TokenType::RightParen) {
        while(true) {
            if(auto arg = parseExpression()) {
                args.push_back(std::move(arg));
            } else {
                return nullptr;
            }
            
            if(type() == TokenType::RightParen)
                break;
            
            if(type() != TokenType::Comma) {
                std::cerr << "Expected `)` or `,` in argument list";
                return nullptr;
            }
            
            nextToken();
        }
    }    
    nextToken();
    
    auto call = std::make_unique<CallAst>(t.str, std::move(args));
    
    visit(*call);
    
    return std::move(call);   
}


expr_uptr YfxSyntax::parseValueBind() {
    nextToken();
    return parseExpression();
    
    // all this will be ploughed
    /*
    auto value = nextToken();
    Token vtype;

    if(nextToken().type == TokenType::TypeSpecifier) {
        vtype = nextToken();
        nextToken(); // Get to the next part of expression
    }
    
    auto finisher = [this](auto ptr) {
        auto p = std::move(ptr);
        if(type() == TokenType::Semicolon) {
            popToScope();
            return std::move(p);
        } else if(type() == TokenType::Comma) {
            popToMode(SynMode::LhsVariableDeclare);
            parseVariableDeclare();
            return std::move(p);
        } else {
            std::cerr << "Expected end of expression `;`\n";
            return expr_uptr(nullptr);
        }
    };
    
    if(value.type == TokenType::Integer) {

          if(vtype.type != TokenType::Undefined 
          && vtype.type == TokenType::PrimitiveType) {
              // Type has been specified
                return finisher(parseIntegerValue(value, vtype.primitive));
         } else {
              // No type specified
              // Todo: Infer integer type here
              return finisher(parseIntegerValue(value, PrimitiveType::I32));
          }
      }

      if(value.type == TokenType::Float) {
          if(vtype.type != TokenType::Undefined 
          && vtype.type == TokenType::PrimitiveType) {
              // Type has been specified
            return finisher(parseFloatValue(value, vtype.primitive));
          } else {
              // No type specified
              // Todo: Infer integer type here
            return finisher(parseFloatValue(value, PrimitiveType::F32));
          }

      }
     */
}

expr_uptr YfxSyntax::parseIntegerValue(Token& i, PrimitiveType t) {

    switch(t) {
        case PrimitiveType::I16: {
            auto v = new Int16Ast(std::stoll(i.str));
            visit(*v);
            return expr_uptr(nullptr);
        }
        case PrimitiveType::I32: {
            auto v = new Int32Ast(std::stoll(i.str));
            visit(*v);
            return expr_uptr(nullptr);
        }
        case PrimitiveType::I64: {
            auto v = new Int64Ast(std::stoll(i.str));
            visit(*v);
            return expr_uptr(nullptr);
        }
            
        case PrimitiveType::U16: {
            auto v = new UInt16Ast(std::stoull(i.str));
            visit(*v);
            return expr_uptr(nullptr);
        }
        case PrimitiveType::U32: {
            auto v = new UInt32Ast(std::stoull(i.str));
            visit(*v);
            return expr_uptr(nullptr);
        }
        case PrimitiveType::U64: {
            auto v = new UInt64Ast(std::stoull(i.str));
            visit(*v);
            return expr_uptr(nullptr);
        }
            
        default:
            std::cerr << "Explicit type does not match integer value\n";
            return expr_uptr(nullptr);
    }
}

expr_uptr YfxSyntax::parseFloatValue(Token& i, PrimitiveType t) {
    switch(t) {
        case PrimitiveType::F32: {
            auto v = new Float32Ast(std::stof(i.str));
            visit(*v);
            return expr_uptr(nullptr);
        }
        case PrimitiveType::F64: {
            auto v = new Float64Ast(std::stod(i.str));
            visit(*v);
            return expr_uptr(nullptr);
        }
            
        default:
            std::cerr << "Explicit type does not match floating point value\n";
            return expr_uptr(nullptr);
    }
}

int YfxSyntax::getPrecedence(TokenType token) {
    auto it = _precedence.find(token);
    if(it == std::end(_precedence)) return -1;
    
    return it->second;
}


void YfxSyntax::popToScope() {
    while(top() != SynMode::LhsFuncScope 
    && top()    != SynMode::LhsModuleScope
    && top()    != SynMode::LhsGlobalScope) {
        pop();
    }
}

void YfxSyntax::popToMode(SynMode mode) {
    while(top() != mode && top() != SynMode::LhsGlobalScope) {
        pop();
    }
}