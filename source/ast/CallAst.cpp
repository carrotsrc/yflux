#include "ast/CallAst.hpp"


using namespace yfx;

CallAst::CallAst(std::string& calling, std::vector<expr_uptr> args) 
    : _calling(calling), _args(std::move(args))
{ }

CallAst::CallAst(CallAst&& orig) 
    : _calling(orig._calling), _args(std::move(orig._args))
{ } 

CallAst::~CallAst() {
}

void CallAst::accept(IAstVisitor& visitor) {
    visitor.visit(*this);
}

std::vector<expr_uptr> CallAst::args() {
    return std::move(_args);
}

const std::vector<expr_uptr>& CallAst::argsRef() {
    return _args;
}

const std::string& CallAst::calling() {
    return _calling;
}


