#include <iostream>
#include "ast/visitors/PrinterVisitor.hpp"
#include "front/YfxSyntax.hpp"
#include "front/MemSourceContainer.hpp"

std::string srctxt = "  \
let meta;               \
let foo = 1000*5+2;       \
func1();                \
func2(a);               \
let d = func3(a,b),     \
    e = 123;            \
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
