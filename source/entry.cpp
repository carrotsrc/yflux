#include <iostream>
#include <streambuf>
#include <fstream>
#include "ast/visitors/PrinterVisitor.hpp"
#include "front/YfxSyntax.hpp"
#include "front/MemSourceContainer.hpp"

int main(int argc, char* argv[]) {
    
    if(argc == 1) {
        std::cerr << "Error: No file specified\n";
        return 1;
    }
    
    auto fname = std::string(argv[1]);
    auto srctxt = std::string();
    std::ifstream fs(fname, std::ifstream::in);
    if(!fs.is_open()) {
        std::cerr << "Error: Failed to open `"<<fname<<"`\n";
        return 1;
    }

    fs.seekg(0, std::ios::end);
    srctxt.reserve(fs.tellg());
    fs.seekg(0, std::ios::beg);
    srctxt.assign((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    
    std::cout << "flux(Y) Frontend\n";
    std::cout << "Parsing `"<<fname<<"`\n";

    yfx::YfxSyntax syntax;

    auto msc = new yfx::MemSourceContainer(srctxt);
    std::unique_ptr<yfx::ISourceContainer> src(msc);
    syntax.setBuffer(std::move(src));
    syntax.addVisitor(std::unique_ptr<yfx::IAstVisitor>(new yfx::PrinterVisitor()));
    syntax.run();
    std::cout << "Exiting OK\n";
    return 0;
}
