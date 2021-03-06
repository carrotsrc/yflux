#include <vector>
#include <iostream>
#include "front/YfxSyntax.hpp"
#include "ast/BinOpAst.hpp"
#include "ast/CallAst.hpp"
#include "LangCommon.hpp"
#include "TokenStrings.hpp"
#include "ast/ScopeBlockAst.hpp"
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

        if(tokPrec < exPrec) {
            return lhs;
        }
        
        auto op = type();
        nextToken();

        auto rhs = parsePrimary();
        
         if(!rhs) return nullptr;
        
        int nextPrec = getPrecedence(type());
        if(tokPrec < nextPrec) {
            rhs = parseBinaryOps(tokPrec+1, std::move(rhs));
            if(!rhs) return nullptr;
        }
        
        lhs = expr_uptr(new BinOpAst(op, std::move(lhs), std::move(rhs)));
    }
}


expr_uptr YfxSyntax::parseTopLevel() {
    
    auto proto = std::make_unique<PrototypeAst>("__module_entry",
                                                PrototypeAst::ArgList());

    auto scope = std::make_unique<ScopeBlockAst>();
    while(type() != TokenType::Eof) {

        auto e = parseExpression();
        if(type() == TokenType::Semicolon) {
            
            popToScope();
        }
        
        if(type() == TokenType::Comma) {
           if(top() == SynMode::RhsVariableBind) {
               popToMode(SynMode::LhsVariableDeclare);
           }
        }
        scope->push(std::move(e));
        nextToken();
    }

    auto mod = std::make_unique<FunctionAst>(std::move(proto), std::move(scope));
    visit(*mod);
    
    return std::move(mod);        
}

expr_uptr YfxSyntax::parseExpression() {

    switch(type()) {
        case TokenType::VariableDeclare: {
            push(YfxToken::Mode::LhsVariableDeclare);
            return parseVariableDeclare();
        }
        case TokenType::FunctionDeclare: {
            push(SynMode::LhsFunctionDeclare);
            auto f = parseFunctionDeclare();
            popBeyond(SynMode::LhsFunctionDeclare);

            return std::move(f);
        }
    }

    auto lhs = parsePrimary();
    return parseBinaryOps(0, std::move(lhs));
}


expr_uptr YfxSyntax::parsePrimary() {
    
    auto t = _token;
    switch(type()) {
        case TokenType::Integer:
            nextToken();
            return parseIntegerValue(t, PrimitiveType::I64);

        case TokenType::Float:
            nextToken();
            return parseFloatValue(t, PrimitiveType::F32);

        case TokenType::Identifier:
            return parseIdentifier();
            
        case TokenType::LeftParen:
            return parseSubExpression();
        default: return expr_uptr(nullptr);
    }
}

expr_uptr YfxSyntax::parseSubExpression() {
    nextToken(); // remove '('
    
    auto expr = parseExpression();
    
    if(type() != TokenType::RightParen) {
        std::cerr << "Expected ')' at end of sub expression\n";
        return nullptr;
    }
    nextToken();
    return std::move(expr);
    
}


expr_uptr YfxSyntax::parseVariableDeclare() {
    
    nextToken(); // Remove `let`

    expr_uptr decl;
    while(type() != TokenType::Semicolon) {
        auto mut = false;
        std::string name;
        expr_uptr v;
        VariableAst::DataType dt;
        _datatype = dt; // Flush old data type
        
        while(1) {
            switch(type()) {
                case TokenType::QualifierMutable: // `%` encountered
                    mut = true;
                    nextToken();
                    continue;

                case TokenType::Identifier: // Variable name encountered
                    _ident = _token;
                    name = _token.str;
                    

                    // Check for a type specifier
                    if(peekToken().type == TokenType::TypeSpecifier) {
                        nextToken();
                        dt = nextToken();
                        _token = _ident;
                    }
                    _datatype = dt;
                    v = std::make_unique<VariableAst>(name, mut, dt);
                    decl = std::make_unique<DeclareAst>(std::move(v), 
                                                        parseIdentifier());

                    break;
                    
                case TokenType::TypeSpecifier:
                    dt = nextToken();// get the type
                    nextToken(); // Onto next token
                    if(dt.type != TokenType::PrimitiveType
                    && dt.type != TokenType::Identifier) {
                        std::cerr << "Expected a primitive or identifier "
                                << "for type specification\n";
                        dt = VariableAst::DataType();
                    }
                    
                    continue;

                default:
                    std::cerr 
                        << "Syntax error on declaration, unexpected token " 
                        << TokenStrings[type()]
                        << " `" << _token.str << "`\n";
                    return expr_uptr(nullptr);
            }
            break;
        }
        if(type() == TokenType::Comma) {
            popToMode(SynMode::LhsVariableDeclare);
            nextToken();
        }
    }
    return std::move(decl);
}

expr_uptr YfxSyntax::parseIdentifier() {
    
    _ident = _token;
    auto t = _token;
    nextToken();
    
    if(type() != TokenType::LeftParen && type() != TokenType::OperatorBind) {
       auto v = std::make_unique<VariableAst>(t.str, false);

       
       // If we're in a variable declare and there is no binding, we don't
       // need this node since it's a duplicate of the one in the `declare`
       // node
       if(top() == SynMode::LhsVariableDeclare) return nullptr;
       
       // We need the node
       return v;
    }
    
    if(type() == TokenType::OperatorBind) {
        push(SynMode::RhsVariableBind);
        auto binding = parseValueBind(
                            std::make_unique<VariableAst>(t.str, false, _datatype)
                        );
        popBeyond(SynMode::RhsVariableBind);
        return std::move(binding);
    }
    
    // We are in a call
    
    nextToken();
    std::vector<expr_uptr> args;
    push(SynMode::FuncActualParams);
    
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
    popBeyond(SynMode::FuncActualParams);
    nextToken();
    
    auto call = std::make_unique<CallAst>(t.str, std::move(args));
    

    
    return std::move(call);   
}


expr_uptr YfxSyntax::parseValueBind(expr_uptr var) {

    nextToken(); // remove `=`
    auto expression = parseExpression();
    return std::make_unique<BindAst>(std::move(var), std::move(expression));
}

expr_uptr YfxSyntax::parseIntegerValue(Token& i, PrimitiveType t) {
    
    switch(t) {
        case PrimitiveType::I16: {
            auto v = new Int16Ast(std::stoll(i.str));
            return expr_uptr(v);
        }
        case PrimitiveType::I32: {
            auto v = new Int32Ast(std::stoll(i.str));
            return expr_uptr(v);
        }
        case PrimitiveType::I64: {
            auto v = new Int64Ast(std::stoll(i.str));
            return expr_uptr(v);
        }
            
        case PrimitiveType::U16: {
            auto v = new UInt16Ast(std::stoull(i.str));
            return expr_uptr(v);
        }
        case PrimitiveType::U32: {
            auto v = new UInt32Ast(std::stoull(i.str));
            return expr_uptr(v);
        }
        case PrimitiveType::U64: {
            auto v = new UInt64Ast(std::stoull(i.str));
            return expr_uptr(v);
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
            return expr_uptr(v);
        }
        case PrimitiveType::F64: {
            auto v = new Float64Ast(std::stod(i.str));
            return expr_uptr(v);
        }
            
        default:
            std::cerr << "Explicit type does not match floating point value\n";
            return expr_uptr(nullptr);
    }
}

expr_uptr YfxSyntax::parseFunctionDeclare() {
  
    auto proto = parseFunctionPrototype();

    if(nextToken().type == TokenType::Semicolon) {

        return std::move(proto);
    }
    
    if(type() == TokenType::LeftBrace) {
        push(SynMode::LhsFuncScope);
        auto body = parseScopeBody();
        popBeyond(SynMode::LhsFuncScope);
        
        return std::make_unique<FunctionAst>(std::move(proto), 
                                             std::move(body));
    }

    return nullptr;
}

expr_uptr YfxSyntax::parseFunctionPrototype() {

    if(nextToken().type != TokenType::Identifier) {
        std::cerr << "Function prototype expects a name identifier\n";
        return nullptr;
    }
    
    auto fname = _token.str;
    std::vector<PrototypeAst::FormalParameter> args;
    
    if(nextToken().type != TokenType::LeftParen) {
        std::cerr << "Expected '(' in function prototype\n";
        return nullptr;
    }
    
    nextToken();
    std::string varlabel;
    //push(SynMode::FuncFormalParams);
    bool mut = false;
    while(type() != TokenType::RightParen) {

        if(type() ==  TokenType::Identifier) {
            varlabel = _token.str;
        } else if(type() == TokenType::QualifierMutable) {
            mut = true;
        } else if(type() == TokenType::TypeSpecifier) {
            nextToken();
            args.push_back(std::make_tuple(varlabel, _token, mut));
            mut = false;
        } else if(type() != TokenType::Comma) {
            std::cout << "Expected identifier, ',' or ')' `"<<TokenStrings[type()]<<"`\n";
            break;
        }
        nextToken();        
    }
    //popBeyond(SynMode::FuncFormalParams);
    return std::make_unique<PrototypeAst>(fname, args);
    
}

expr_uptr YfxSyntax::parseScopeBody() {
    
    auto scope = std::make_unique<ScopeBlockAst>();

    while(nextToken().type != TokenType::RightBrace) {
        if(type() == TokenType::LeftBrace) {
            push(SynMode::LhsExprScope);
            scope->push(parseScopeBody());
            popBeyond(SynMode::LhsExprScope);
            continue;
        }
        
        scope->push(parseExpression());
    }
    return std::move(scope);
}




int YfxSyntax::getPrecedence(TokenType token) {
    auto it = _precedence.find(token);
    if(it == std::end(_precedence)) return -1;
    
    return it->second;
}


void YfxSyntax::popToScope() {
    while(top() != SynMode::LhsFuncScope 
    && top()    != SynMode::LhsModuleScope
    && top()    != SynMode::LhsGlobalScope
    && top()    != SynMode::LhsExprScope) {
        pop();
    }
}

void YfxSyntax::popToMode(SynMode mode) {
    while(top() != mode && top() != SynMode::LhsGlobalScope) {
        pop();
    }
    
    if(top() == SynMode::LhsGlobalScope && mode != top()) {
        std::cerr << "Error: Asymmetric state stack, popped to global scope\n";
    }
}

void YfxSyntax::popBeyond(SynMode mode) {
    popToMode(mode);
    pop();
}
