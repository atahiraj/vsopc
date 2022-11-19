
#ifndef CODE_GENERATOR_VISITOR_H
#define CODE_GENERATOR_VISITOR_H

/*!
 * \file codeGeneratorVisitor.hpp
 * \brief Header containing the different classes allowing code generation
 * through the visitor pattern and llvm. \author Tahiraj Arian \author Leroy
 * Antoine \version 0.1
 */

#include <astTree/nodes.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <visitors/visitor.hpp>

/*! \class CodeGeneratorVisitor
 * \brief Main class for code generation.
 *
 * This class visits each node and generates the corresponding llvm code.
 */
class CodeGeneratorVisitor : public Visitor
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the CodeGeneratorVisitor class.
     */
    CodeGeneratorVisitor(void);

    /*!
     * \brief Destructor
     *
     * Destructor of the CodeGeneratorVisitor class.
     */
    ~CodeGeneratorVisitor(void) = default;

    /*!
     * \brief Visitor pattern of an AstNode
     *
     * Visits a AstNode and generates the corresponding llvm code.
     *
     * \param astNode : An AstNode object
     */
    void visit(AstNode &astNode) override;

    /*!
     * \brief Visitor pattern of an ClassNode
     *
     * Visits a ClassNode and generates the corresponding llvm code.
     *
     * \param classNode : An ClassNode object
     */
    void visit(ClassNode &classNode) override;

    /*!
     * \brief Visitor pattern of an MethodNode
     *
     * Visits a MethodNode and generates the corresponding llvm code.
     *
     * \param methodNode : An MethodNode object
     */
    void visit(MethodNode &methodNode) override;

    /*!
     * \brief Visitor pattern of an FieldNode
     *
     * Visits a FieldNode and generates the corresponding llvm code.
     *
     * \param fieldNode : An FieldNode object
     */
    void visit(FieldNode &fieldNode) override;

    /*!
     * \brief Visitor pattern of an FormalsNode
     *
     * Visits a FormalsNode and generates the corresponding llvm code.
     *
     * \param formalsNode : An FormalsNode object
     */
    void visit(__attribute__((unused)) FormalsNode &formalsNode) override;

    /*!
     * \brief Visitor pattern of an ObjectIDNode
     *
     * Visits a ObjectIDNode and generates the corresponding llvm code.
     *
     * \param objectIDNode : An ObjectIDNode object
     */
    void visit(ObjectIDNode &objectIDNode) override;

    /*!
     * \brief Visitor pattern of an IfNode
     *
     * Visits a IfNode and generates the corresponding llvm code.
     *
     * \param ifNode : An IfNode object
     */
    void visit(IfNode &ifNode) override;

    /*!
     * \brief Visitor pattern of an WhileNode
     *
     * Visits a WhileNode and generates the corresponding llvm code.
     *
     * \param whileNode : An WhileNode object
     */
    void visit(WhileNode &whileNode) override;

    /*!
     * \brief Visitor pattern of an LetNode
     *
     * Visits a LetNode and generates the corresponding llvm code.
     *
     * \param letNode : An LetNode object
     */
    void visit(LetNode &letNode) override;

    /*!
     * \brief Visitor pattern of an AssignNode
     *
     * Visits a AssignNode and generates the corresponding llvm code.
     *
     * \param assignNode : An AssignNode object
     */
    void visit(AssignNode &assignNode) override;

    /*!
     * \brief Visitor pattern of an BinaryOpNode
     *
     * Visits a BinaryOpNode and generates the corresponding llvm code.
     *
     * \param binaryOpNode : An BinaryOpNode object
     */
    void visit(BinaryOpNode &binaryOpNode) override;

    /*!
     * \brief Visitor pattern of an UnaryOpNode
     *
     * Visits a UnaryOpNode and generates the corresponding llvm code.
     *
     * \param unaryOpNode : An UnaryOpNode object
     */
    void visit(UnaryOpNode &unaryOpNode) override;

    /*!
     * \brief Visitor pattern of an CallNode
     *
     * Visits a CallNode and generates the corresponding llvm code.
     *
     * \param callNode : An CallNode object
     */
    void visit(CallNode &callNode) override;

    /*!
     * \brief Visitor pattern of an NewNode
     *
     * Visits a NewNode and generates the corresponding llvm code.
     *
     * \param newNode : An NewNode object
     */
    void visit(NewNode &newNode) override;

    /*!
     * \brief Visitor pattern of an LiteralNode
     *
     * Visits a LiteralNode and generates the corresponding llvm code.
     *
     * \param literalNode : An LiteralNode object
     */
    void visit(LiteralNode &literalNode) override;

    /*!
     * \brief Visitor pattern of an BlockNode
     *
     * Visits a BlockNode and generates the corresponding llvm code.
     *
     * \param blockNode : An BlockNode object
     */
    void visit(BlockNode &blockNode) override;

    /*!
     * \brief Visitor pattern of an UnitNode
     *
     * This node is not visited but this method must be implemented since
     * it is a pure virtual method in the parent class.
     *
     * \param unitNode : An UnitNode object (unused).
     */
    void visit(__attribute__((unused)) UnitNode &unitNode) override;

    /*!
     * \brief Getter of the variable code_.
     *
     * This method is the getter of the variable code_.
     *
     * \return code_: the llvm code this visitor has generated.
     */
    std::string &code(void);

  private:
    /*!
     * \brief Converts a vsop type to a llvm type.
     *
     * This methods converts a vsop type to a llvm type. For instance
     * it converts the type "int32" to "%int32" or "Object" to
     * "%struct.Object*".
     *
     * \param type: vsop type.
     *
     * \return the corresponding llvm type.
     */
    std::string convertType(std::string type);

    /*!
     * \brief Converts a register number to its llvm form.
     *
     * Converts a register number to its llvm form. Basically converts the
     * unsigned "x" to "%x"
     *
     * \param ssa: register number.
     *
     * \return the register conerted to a string with the character %
     * prepended to it.
     */
    std::string registerToLlvm(const unsigned &ssa);

    /*!
     * \brief Generates the llvm code to allocate a variable on the stack.
     *
     * \param ssaDest: the register number of the variable that will contain
     * the pointer to the new allocation.
     * \param type: llvm type of the variable to be allocated on the stack.
     */
    void allocaGen(const unsigned &ssaDest, const std::string &type);

    /*!
     * \brief Generates code to load a variable.
     *
     * Generates the llvm code to load the value of a variable given a
     * pointer.
     *
     * \param ssaDest: the register number of the variable that will contain
     * loaded value.
     * \param type: type of the variable to be loaded.
     * \param src: the llvm pointer variable from whom we make the load.
     */
    void loadGen(const unsigned &ssaDest, const std::string &type,
                 const std::string &src);

    /*!
     * \brief Generates code to store a variable at a location.
     *
     * Generates the llvm code to store a llvm variable at a location given
     * by a llvm pointer.
     *
     * \param type: type of the variable to be stored.
     * \param src: the llvm variable to be stored.
     * \param dest: the llvm pointer variable pointing to the location where
     * the src variable will be stored.
     */
    void storeGen(const std::string &type, const std::string &src,
                  const std::string &dest);

    /*!
     * \brief Generates code for a binary operation.
     *
     * \param ssaDest: the register number of the variable that will contain
     * the result of the operation.
     * \param op: the operation.
     * \param type: the llvm type of the operation's result.
     * \param ssaLeft: the register number of the left operand.
     * \param ssaRight: the register number of the right operand.
     */
    void binaryGen(const unsigned &ssaDest, const char *const &op,
                   const std::string &type, const unsigned &ssaLeft,
                   const unsigned &ssaRight);

    /*!
     * \brief Generates code for a bitcast operation.
     *
     * \param ssaDest: the register number of the variable that will contain
     * the result of the operation.
     * \param fromType: source llvm type of the bitcast.
     * \param ssa: the register number of the variable to be bitcasted.
     * \param toType: destination type of the llvm bitcast.
     */
    void bitcastGen(const unsigned &ssaDest, const std::string &fromType,
                    const unsigned &ssa, const std::string &toType);

    /*!
     * \brief Generates code for a function call.
     *
     * \param ssaDest: the register number of the variable that will contain
     * the result of the call.
     * \param retType: llvm return type of the function.
     * \param methodName: name of the function to be called.
     * \param args: vector containing the arguments for the call (e.g. an
     * element of the vector could be the string "%struct.Object* %3").
     */
    void callGen(const unsigned &ssaDest, const std::string &retType,
                 const std::string &methodName,
                 const std::vector<std::string> &args);

    /*!
     * \brief Generates code for a getelementptr operation.
     *
     * \param ssaDest: the register number of the variable that will contain
     * the result of the operation.
     * \param type: llvm type of the struct from which we want to get an
     * element from.
     * \param ptr: llvm pointer variable to the struct we want to get an
     * element from.
     * \param idx: index of element of struct we want to get.
     */
    void getEleGen(const unsigned &ssaDest, const std::string &type,
                   const std::string &ptr, const unsigned &idx);

    /*!
     * \brief Generates code for a conditionnal branch instruction.
     *
     * \param ssaCond: the register number of the llvm variable containing
     * the condition of the branching.
     * \param label1: the llvm label to which we jump if the condition is
     * true.
     * \param label2: the llvm label to which we jump if the condition is
     * false.
     */
    void branchGen(const unsigned &ssaCond, const std::string &label1,
                   const std::string &label2);

    /*!
     * \brief Generates code for a branch instruction.
     *
     * \param label: the llvm label to which we jump.
     */
    void branchGen(const std::string &label);

    /*!
     * \brief Generates code for the phi operation.
     *
     * \param ssa: the register number of the variable that will contain
     * the result of the operation.
     * \param type: the llvm type of the new llvm variable (and thus of the
     * 2 candidates).
     * \param ssa1: the register number of the first candidate.
     * \param label1: the llvm label of the first candidate.
     * \param ssa2: the register number of the second candidate.
     * \param label2: the llvm label of the second candidate.
     */
    void phiGen(const unsigned &ssa, const std::string &type,
                const unsigned &ssa1, const std::string &label1,
                const unsigned &ssa2, const std::string &label2);

    /*!
     * \brief Generates code for the ret instruction.
     *
     * \param type: the llvm type of the returned variable.
     * \param ssa: the register number of the llvm variable to be returned.
     */
    void retGen(const std::string &type, const unsigned &ssa);

    /*!
     * \brief Generates code to load a llvm string.
     *
     * This method generates the llvm code to load a string. Since strings
     * are immutable in vsop, all the strings are enumarated in the llvm
     * code. Therefore the size and the index (in the enumeration) of are
     * needed to load it.
     *
     * \param ssa: the register number of the variable that will contain
     * the result of the loading.
     * \param size: the size of the llvm string.
     * \param idx: the index of the llvm string in the enumeration.
     */
    void getStrGen(const unsigned &ssa, const unsigned &size,
                   const unsigned &idx);

    /*!
     * \brief Generates code that initializes a variable for a given type.
     *
     * Generates code that initializes a variable for a given type. For
     * instance, generates code to declare and integer and set it to 0.
     *
     * \param type: llvm type for which to generate the code.
     */
    void init(const std::string &type);

    unsigned labelNb_;     /*!< Label counter used to avoid conflicts. */
    unsigned ssaNb_;       /*!< Current register counter. */
    unsigned strNb_;       /*!< Current string index counter. */
    std::string code_;     /*!< Current generated code. */
    std::string cClass_;   /*!< Name of the current visited class. */
    std::stringstream ss_; /*!< stringstream used thorough all the visits. */
    std::unordered_map<std::string, unsigned>
        fMap_; /*!< Maps the name of the fields with their index in the llvm
                      struct of the object. */
    std::unordered_map<std::string, unsigned>
        mMap_; /*!< Maps the name of the methods with their index in the
                      llvm struct of the function table. */
    std::unordered_map<std::string, unsigned>
        sMap_;          /*!< Maps a llvm string with its index in the string
                               enumeration. */
    InheriTree *iTree_; /*!< Inheritance tree of the visited AST. */
    FunctionTableTree *fTree_; /*!< Function table tree of the visited AST. */
    VariableTableTree *vTree_; /*!< Variable table tree of the visited AST. */
    VariableTable *cScope_;    /*!< Current scope the visitor is in. */
};

#endif
