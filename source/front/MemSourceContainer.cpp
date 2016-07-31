#include <string>
#include <stdexcept>

#include "front/MemSourceContainer.hpp"

using namespace yfx;

MemSourceContainer::MemSourceContainer(std::string source)
    : _source(source), _it(_source.begin()), _delta(_it)
{ }

MemSourceContainer::MemSourceContainer(const MemSourceContainer& orig) {
}

MemSourceContainer::~MemSourceContainer() {
}

std::string MemSourceContainer::getAll() {
    return _source;
}

void MemSourceContainer::rewind() {
    _it = _source.begin();
}

signed char MemSourceContainer::getChar() {
    if(_it == std::end(_source)) return EOF;
    
    char c = *_it;
    ++_it; _delta = _it;
    return c;
}

signed char MemSourceContainer::peekChar() {
   if(_delta == std::end(_source)) return EOF;
    
    char c = *_delta;
    ++_delta;
    return c;    
}

void MemSourceContainer::closeDelta() {
    _it = _delta;
}

void MemSourceContainer::rewindPeek() {
    _delta--;
}

signed char MemSourceContainer::rewindChar() {
    --_it;
    return *_it;
}

