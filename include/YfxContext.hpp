#ifndef YFXCONTEXT_HPP
#define YFXCONTEXT_HPP
#include "LangCommon.hpp"
namespace yfx {


class YfxContext {
public:
	YfxContext();
	YfxContext(const YfxContext& orig);
	~YfxContext();

        llvm::LLVMContext& operator*();
private:
    
    llvm::LLVMContext _context;

};

}
#endif /* YFXCONTEXT_HPP */

