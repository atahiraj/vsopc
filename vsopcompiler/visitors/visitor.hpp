#ifndef VISITOR_H
#define VISITOR_H

/*!
 * \file visitor.hpp
 * \brief Header containing the different function declarations allowing a
 * visitor pattern interface. \author Tahiraj Arian \author Leroy Antoine
 * \version 0.1
 */

class Node;
class AstNode;
class ClassNode;
class MethodNode;
class FieldNode;
class FormalsNode;
class ObjectIDNode;
class IfNode;
class WhileNode;
class LetNode;
class AssignNode;
class BinaryOpNode;
class UnaryOpNode;
class CallNode;
class NewNode;
class LiteralNode;
class BlockNode;
class UnitNode;

/*! \class Visitor
 * \brief This class implements the visitor pattern for the AST.
 *
 *  Contains multiple functions to visit each of the nodes created to implement
 * the AST.
 */
class Visitor
{
  public:
    /*!
     *  \brief Visit function of an AstNode
     *
     *  \param astNode : An AstNode object.
     */
    virtual void visit(AstNode &astNode) = 0;

    /*!
     *  \brief Visit function of a ClassNode
     *
     *  \param classNode : A ClassNode object.
     */
    virtual void visit(ClassNode &classNode) = 0;

    /*!
     *  \brief Visit function of a MethodNode
     *
     *  \param methodNode : A MethodNode object.
     */
    virtual void visit(MethodNode &methodNode) = 0;

    /*!
     *  \brief Visit function of a FieldNode
     *
     *  \param fieldNode : A FieldNode object.
     */
    virtual void visit(FieldNode &fieldNode) = 0;

    /*!
     *  \brief Visit function of a FormalsNode
     *
     *  \param formalsNode : A FormalsNode object.
     */
    virtual void visit(FormalsNode &formalsNode) = 0;

    /*!
     *  \brief Visit function of an ObjectIDNode
     *
     *  \param objectIDNode : An ObjectIDNode object.
     */
    virtual void visit(ObjectIDNode &objectIDNode) = 0;

    /*!
     *  \brief Visit function of an IfNode
     *
     *  \param ifNode : An IfNode object.
     */
    virtual void visit(IfNode &ifNode) = 0;

    /*!
     *  \brief Visit function of a WhileNode
     *
     *  \param whileNode : A WhileNode object.
     */
    virtual void visit(WhileNode &whileNode) = 0;

    /*!
     *  \brief Visit function of a LetNode
     *
     *  \param letNode : A LetNode object.
     */
    virtual void visit(LetNode &letNode) = 0;

    /*!
     *  \brief Visit function of an AssignNode
     *
     *  \param assignNode : An AssignNode object.
     */
    virtual void visit(AssignNode &assignNode) = 0;

    /*!
     *  \brief Visit function of a BinaryOpNode
     *
     *  \param binaryOpNode : A BinaryOpNode object.
     */
    virtual void visit(BinaryOpNode &binaryOpNode) = 0;

    /*!
     *  \brief Visit function of an UnaryOpNode
     *
     *  \param unaryOpNode : An UnaryOpNode object.
     */
    virtual void visit(UnaryOpNode &unaryOpNode) = 0;

    /*!
     *  \brief Visit function of a CallNode
     *
     *  \param callNode : A CallNode object.
     */
    virtual void visit(CallNode &callNode) = 0;

    /*!
     *  \brief Visit function of a NewNode
     *
     *  \param newNode : A NewNode object.
     */
    virtual void visit(NewNode &newNode) = 0;

    /*!
     *  \brief Visit function of a LiteralNode
     *
     *  \param literalNode : A LiteralNode object.
     */
    virtual void visit(LiteralNode &literalNode) = 0;

    /*!
     *  \brief Visit function of a BlockNode
     *
     *  \param blockNode : A BlockNode object.
     */
    virtual void visit(BlockNode &blockNode) = 0;

    /*!
     *  \brief Visit function of an UnitNode
     *
     *  \param unitNode : An UnitNode object.
     */
    virtual void visit(UnitNode &unitNode) = 0;
};

#endif
