/*!
 * \file main.cpp
 * \brief Main file allowing to run the VSOP compiler depending on different
 * arguments. \author Tahiraj Arian \author Leroy Antoine \version 0.1
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include <astTree/nodes.hpp>
#include <lexer/lexer.hpp>
#include <parser/parser.hpp>
#include <visitors/augmentASTVisitor.hpp>
#include <visitors/codeGeneratorVisitor.hpp>
#include <visitors/dumpASTVisitor.hpp>

int main(int argc, char **argv)
{
    char *fileName;
    std::string option;

    if (argc < 2)
    {
        std::cerr << "Expected 2 arguments but found " << argc - 1 << std::endl;
        return -1;
    }
    else if (argc == 2)
    {
        fileName = argv[1];
        option = std::string("");
    }
    else
    {
        fileName = argv[2];
        option = std::string(argv[1]);
    }

    DumpASTVisitor dumper = DumpASTVisitor(std::cout);
    AugmentASTVisitor augmentor = AugmentASTVisitor(std::string(fileName));
    CodeGeneratorVisitor generator = CodeGeneratorVisitor();

    /**************************** LEXICAL ANALYSIS ****************************/
    yylex_init(fileName);
    if (option == "-lex")
        return yylex_dump();

    /***************************** SYNTAX ANALYSIS ****************************/
    std::unique_ptr<AstNode> ast = std::unique_ptr<AstNode>(parse(fileName));
    if (!ast) // nullptr
        return -1;
    if (option == "-parse")
    {
        ast->accept(dumper);
        return 0;
    }

    /**************************** SEMANTIC ANALYSIS ***************************/
    ast->accept(augmentor);
    if (augmentor.flag())
        exit(-1); // Avoiding segfault when freeing astNode

    if (option == "-check")
    {
        ast->accept(dumper);
        return 0;
    }

    /***************************** CODE GENERATION ***************************/
    ast->accept(generator);
    if (option == "-llvm")
    {
        std::cout << generator.code() << std::endl;
        return 0;
    }

    // Llvm file
    const std::string &fName = std::string(fileName);
    const std::string &oName =
        fName.substr(0, fName.find(std::string(".vsop")));
    std::cout << "Creating the temporary llvm file...";
    std::ofstream os(oName + ".ll");
    if (!os)
    {
        std::cerr << "Failed to create llvm temporary file: ";
        perror(NULL);
        return -1;
    }
    os << generator.code();
    os.close();
    std::cout << " Done" << std::endl;

    // Optimizing llvm code
    std::cout << "Optimizing the llvm code...";
    const std::string optOptions("-O3 -S -o " + oName + ".opt ");
    int ret = std::system(("opt " + optOptions + oName + ".ll").c_str());
    if (ret)
        return -1;
    std::cout << " Done" << std::endl;

    // Object file
    std::cout << "Creating the temporary object file...";
    ret = std::system(("llc -filetype=obj " + oName + ".ll").c_str());
    if (ret)
        return -1;
    std::cout << " Done" << std::endl;

    // Executable
    std::cout << "Creating the executable file...";
    ret = std::system(("clang -o " + oName + " " + oName + ".o").c_str());
    if (ret)
        return -1;
    std::cout << " Done" << std::endl;

    // Cleaning up
    std::cout << "Cleaning up...";
    ret = std::system(
        ("rm " + oName + ".ll " + oName + ".opt " + oName + ".o").c_str());
    if (ret)
        return -1;
    std::cout << " Done" << std::endl;

    return 0;
}
