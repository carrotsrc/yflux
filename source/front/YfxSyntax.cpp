#include <vector>
#include <iostream>
#include "front/YfxSyntax.hpp"

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

expr_uptr YfxSyntax::parseTopLevel() {
    std::cout << "Parsing top level\n";
    while(type() != TokenType::Eof) {
        parsePrimary();
        nextToken();
    }
}

expr_uptr YfxSyntax::parsePrimary() {
    switch(type()) {
        case TokenType::VariableDeclare:
            return parseVariableDeclare();
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
        auto v = new VariableAst(name, mut);
        visit(*v);
        return expr_uptr(nullptr);
    }    
    
    if(type() == TokenType::OperatorBind) {
        auto v = new VariableAst(name, mut);
        visit(*v);
        return  parseValueBind();
    }
}

expr_uptr YfxSyntax::parseValueBind() {
    auto value = nextToken();
    Token vtype;

    if(nextToken().type == TokenType::TypeSpecifier) {
        vtype = nextToken();
        nextToken(); // Get to the next part of expression
    }
    
    auto finisher = [this](auto ptr) {
        auto p = std::move(ptr);
        if(type() == TokenType::Semicolon) {
            return std::move(p);
        } else if(type() == TokenType::Comma) {
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







