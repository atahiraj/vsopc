/**@mainpage
## Lexical analysis
The lexical analysis is realized thanks to the Flex tool which allows to generate a token when a lexeme is found.

See lexer.hpp for the documentation.

## Syntax analysis
The parsing algorithm used for this part is the bottom-up parsing. This one can be easily implemented with the Bison tool.
With this grammar, it will be possible to create an AST where each node represents a basic VSOP statement.
In addition, the structure chosen for the AST is the visitor pattern and makes it easier to use for this and future steps.

See nodes.hpp and dumpASTVisitor.hpp for the documentation of the AST and the syntax analysis.

## Semantic analysis
The semantic analysis is done in 4 passes, thus 1 visitor was implemented for each of them:

+ InheritanceTreeAugmentorVisitor: Class allowing to create mainly the inheritance tree and the different tables about methods.
+ ScopeCheckerAugmentorVisitor: Class allowing mainly scope checking.
+ TypeSetterAugmentorVisitor: Class allowing mainly to set the types used in the vsop file.
+ TypeCheckerAugmentorVisitor: This class allows to perform type checking of the semantic analysis.

Each of these classes are documented in the augmentASTVisitor.hpp file.

## Code generation
See codeGeneratorVisitor.hpp for the documentation.
*/
