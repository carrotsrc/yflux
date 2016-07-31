#include "YfxContext.hpp"

using namespace yfx;
    
YfxContext::YfxContext() {
}

YfxContext::YfxContext(const YfxContext& orig) {
}

YfxContext::~YfxContext() {
}

llvm::LLVMContext& YfxContext::operator*() {
    return _context;
}

