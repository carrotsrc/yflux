#ifndef ASTFORWARD_HPP
#define ASTFORWARD_HPP


#include <cstdint>


namespace yfx {

template<typename DataType, int Bits, bool Signed> class IntegerAst;

using Int16Ast = IntegerAst<std::int16_t,16,true>;
using Int32Ast = IntegerAst<std::int32_t,32,true>;
using Int64Ast = IntegerAst<std::int64_t,64,true>;

using UInt16Ast = IntegerAst<std::uint16_t,16,false>;
using UInt32Ast = IntegerAst<std::uint32_t,32,false>;
using UInt64Ast = IntegerAst<std::uint64_t,64,false>;

using Sample16Ast = Int16Ast;




template<typename DataType, int Bits> class FloatAst;

using Float32Ast = FloatAst<float, 32>;
using Float64Ast = FloatAst<double, 64>;
using Sample32Ast = Float32Ast;

class VariableAst;
class FunctionAst;
class CallAst;
class BinOpAst;
class BindAst;
class DeclareAst;

}
#endif /* ASTFORWARD_HPP */

