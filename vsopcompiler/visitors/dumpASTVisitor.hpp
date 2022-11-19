#ifndef DUMP_AST_VISITOR_H
#define DUMP_AST_VISITOR_H

/*!
 * \file dumpASTVisitor.hpp
 * \brief Header containing the different classes allowing syntax analysis
 * through the visitor pattern. \author Tahiraj Arian \author Leroy Antoine
 * \version 0.1
 */

#include <astTree/nodes.hpp>
#include <cstddef>
#include <ostream>
#include <string>
#include <vector>
#include <visitors/visitor.hpp>

/*! \class DumpASTVisitor
 * \brief Main class for syntax analysis through visitor pattern.
 *
 * The class, implemented with the visitor pattern, allows the syntax analysis
 * of a vsop file.
 */
class DumpASTVisitor : public Visitor
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the DumpASTVisitor class.
     *
     * \param ostream : An output stream objects which is used to print the
     * nodes.
     */
    DumpASTVisitor(std::ostream &ostream);

    /*!
     * \brief Visitor pattern of an AstNode
     *
     * Visit function of the AstNode class with visitor pattern. This visit
     * function prints the list of classes, in the same order as in the
     * input file.
     *
     * \param astNode : An AstNode object
     */
    void visit(AstNode &astNode) override;

    /*!
     * \brief Visitor pattern of an ClassNode
     *
     * Visit function of the ClassNode class for visitor pattern. This visit
     * function prints all classes with respect to the statement:
     * 									Class(<name>,
     * <parent>, <fields>, <methods>)
     *
     * \param classNode : An ClassNode object
     */
    void visit(ClassNode &classNode) override;

    /*!
     * \brief Visitor pattern of an MethodNode
     *
     * Visit function of the MethodNode class for visitor pattern. This
     * visit function prints all Methods with respect to the statement:
     * 									Method(<name>,
     * <formals>, <ret-type>, <block>)
     *
     * \param methodNode : An MethodNode object
     */
    void visit(MethodNode &methodNode) override;

    /*!
     * \brief Visitor pattern of an FieldNode
     *
     * Visit function of the FieldNode class for visitor pattern. This visit
     * function prints all field arguments with respect to the statement:
     * 													Field(<name>,
     *<type>) OR Field(<name>, <type>, <init-expr>)
     *
     * \param fieldNode : An FieldNode object
     */
    void visit(FieldNode &fieldNode) override;

    /*!
     * \brief Visitor pattern of an FormalsNode
     *
     * Visit function of the FormalsNode class for visitor pattern. This
     * visit function prints all formal arguments with respect to the
     * statement: <name> : <type>
     *
     * \param formalsNode : An FormalsNode object
     */
    void visit(FormalsNode &formalsNode) override;

    /*!
     * \brief Visitor pattern of an ObjectIDNode
     *
     * Visit function of the ObjectIDNode class for visitor pattern. This
     *visit function prints all object ID arguments with respect to the
     *statement: <name>
     *
     * \param objectIDNode : An ObjectIDNode object
     */
    void visit(ObjectIDNode &objectIDNode) override;

    /*!
     * \brief Visitor pattern of an IfNode
     *
     * Visit function of the IfNode class for visitor pattern. This visit
     * function prints all if-else node expression with respect to the
     *statement: If(<cond-expr>, <then-expr>) OR If(<cond-expr>,
     *<then-expr>, <else-expr>)
     *
     * \param ifNode : An IfNode object
     */
    void visit(IfNode &ifNode) override;

    /*!
     * \brief Visitor pattern of an WhileNode
     *
     * Visit function of the WhileNode class for visitor pattern. This visit
     * function prints all while expression with respect to the statement:
     *									While(<cond-expr>,
     *<body-expr>)
     *
     * \param whileNode : An WhileNode object
     */
    void visit(WhileNode &whileNode) override;

    /*!
     * \brief Visitor pattern of an LetNode
     *
     * Visit function of the LetNode class for visitor pattern. This visit
     * function prints all Let expression with respect to the statement:
     *									Let(<name>,
     *<type>, <scope-expr>) OR Let(<name>, <type>, <init-expr>,
     *<scope-expr>)
     *
     * \param letNode : An LetNode object
     */
    void visit(LetNode &letNode) override;

    /*!
     * \brief Visitor pattern of an AssignNode
     *
     * Visit function of the AssignNode class for visitor pattern. This
     *visit function prints all Assign expression with respect to the
     *statement: Assign(<name>, <expr>)
     *
     * \param assignNode : An AssignNode object
     */
    void visit(AssignNode &assignNode) override;

    /*!
     * \brief Visitor pattern of an BinaryOpNode
     *
     * Visit function of the BinaryOpNode class for visitor pattern. This
     *visit function prints all Binary operator expression with respect to
     *the statement: BinOp(<op>, <left-expr>, <right-expr>)
     *
     * \param binaryOpNode : An BinaryOpNode object
     */
    void visit(BinaryOpNode &binaryOpNode) override;

    /*!
     * \brief Visitor pattern of an UnaryOpNode
     *
     * Visit function of the UnaryOpNode class for visitor pattern. This
     *visit function prints all unary operator expression with respect to
     *the statement: UnOp(not, <expr>) OR UnOp(-, <expr>) OR UnOp(isnull,
     *<expr>)
     *
     * \param unaryOpNode : An UnaryOpNode object
     */
    void visit(UnaryOpNode &unaryOpNode) override;

    /*!
     * \brief Visitor pattern of an CallNode
     *
     * Visit function of the CallNode class for visitor pattern. This visit
     * function prints all Call expression with respect to the statement:
     *								Call(<obj-expr>,
     *<method-name>, <expr-list>)
     *
     * \param callNode : An CallNode object
     */
    void visit(CallNode &callNode) override;

    /*!
     * \brief Visitor pattern of an NewNode
     *
     * Visit function of the NewNode class for visitor pattern. This visit
     * function prints all New expression with respect to the statement:
     *													New(<type-name>)
     *
     * \param newNode : An NewNode object
     */
    void visit(NewNode &newNode) override;

    /*!
     * \brief Visitor pattern of an LiteralNode
     *
     * Visit function of the LiteralNode class for visitor pattern. This
     *visit function prints all literal expression with respect to the
     *statement: <literal-value> (In string)
     *
     * \param literalNode : An LiteralNode object
     */
    void visit(LiteralNode &literalNode) override;

    /*!
     * \brief Visitor pattern of an BlockNode
     *
     * Visit function of the BlockNode class for visitor pattern. This visit
     * function prints all block expression with respect to the statement:
     *														<expr-list>
     *																OR
     *															<expr>
     *
     * \param blockNode : An BlockNode object
     */
    void visit(BlockNode &blockNode) override;

    /*!
     * \brief Visitor pattern of an UnitNode
     *
     * Visit function of the UnitNode class for visitor pattern. This visit
     * function prints all unit expression with respect to the statement.
     *
     * \param unitNode : An UnitNode object
     */
    void visit(UnitNode &unitNode) override;

  private:
    std::ostream &os_; /*!< An output stream object which is used to print
                          the nodes. */
    int indent_;       /*!< An integer allowing the output to be indented in the
                          best possible way. */
};

#endif
