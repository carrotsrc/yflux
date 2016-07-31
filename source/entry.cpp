#include <iostream>
#include "ast/visitors/PrinterVisitor.hpp"
#include "front/YfxSyntax.hpp"
#include "front/MemSourceContainer.hpp"

std::string srctxt = "  \
let% mvar;              \
let  ival = 34;         \
let  jval = 34   ~u64,  \
   % kval = 455  ~i64,  \
     lval = 1283 ~u32;  \
let% fval = 34.5 ~f32;  \
";

int main() {
	std::cout << "flux(Y) Frontend\n";
        
        yfx::YfxSyntax syntax;
        
        auto msc = new yfx::MemSourceContainer(srctxt);
        std::unique_ptr<yfx::ISourceContainer> src(msc);
        syntax.setBuffer(std::move(src));
        syntax.addVisitor(std::unique_ptr<yfx::IAstVisitor>(new yfx::PrinterVisitor()));
        syntax.run();
	std::cout << "Exiting OK\n";
	return 0;
}
