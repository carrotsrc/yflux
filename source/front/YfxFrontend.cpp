#include "front/YfxFrontend.hpp"
using namespace yfx;

YfxFrontend::YfxFrontend()
    : _module(new llvm::Module("main", *_context))
    , _builder(*_context)
{
}

YfxFrontend::~YfxFrontend() {
}

