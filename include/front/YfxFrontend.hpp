#ifndef YFXFRONTEND_HPP
#define YFXFRONTEND_HPP

#include "YfxContext.hpp"
#include "ast/Ast.hpp"


namespace yfx {

class YfxFrontend {
public:
	YfxFrontend();
	virtual ~YfxFrontend();
private:
    YfxContext _context;
    llvm::Module* _module;
    llvm::IRBuilder<> _builder;
};

}
#endif /* YFXFRONTEND_HPP */

