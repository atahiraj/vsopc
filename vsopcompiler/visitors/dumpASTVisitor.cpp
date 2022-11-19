/*!
 * \file dumpASTVisitor.cpp
 * \brief Source code containing the different classes allowing syntax analysis
 * through the visitor pattern. \author Tahiraj Arian \author Leroy Antoine
 * \version 0.1
 */

#include <typeinfo>
#include <visitors/dumpASTVisitor.hpp>

#ifndef INDENT
#define INDENT                                                                 \
    do                                                                         \
    {                                                                          \
        for (int i = 0; i < (this->indent_); ++i)                              \
            this->os_ << "\t";                                                 \
    } while (0)
#endif

#ifndef EXPRTYPE // Does not work with (node).exprType()
#define EXPRTYPE(node) (node.exprType() ? " : " + *node.exprType() : "")
#endif

DumpASTVisitor::DumpASTVisitor(std::ostream &ostream) : os_(ostream)
{
    this->indent_ = 0;
}

void DumpASTVisitor::visit(AstNode &astNode)
{
    // Get the list of classes
    std::vector<ClassNode *> &classes = astNode.classes();
    // Print all classes
    this->os_ << "[";
    for (auto it = classes.begin(); it != classes.end() - 1; ++it)
    {
        (*it)->accept(*this);
        this->os_ << "," << std::endl;
    }
    classes.back()->accept(*this);
    this->os_ << "]" << std::endl;

    return;
}

void DumpASTVisitor::visit(ClassNode &classNode)
{
    std::vector<FieldNode *> &fieldNodes = classNode.fieldNodes();
    std::vector<MethodNode *> &methodNodes = classNode.methodNodes();

    // Print the name of the class and the name of the super class if any
    this->os_ << "Class(" << classNode.className() << ", ";
    this->os_ << classNode.superClassName();
    this->os_ << ", ";

    // Print the FieldNodes contained in a class
    if (!fieldNodes.empty())
    {
        this->os_ << std::endl << "\t[";
        for (auto it = fieldNodes.begin(); it != fieldNodes.end() - 1; ++it)
        {
            this->indent_ = 1;
            (*it)->accept(*this);
            this->os_ << ",";
            this->os_ << std::endl << "\t";
        }
        fieldNodes.back()->accept(*this);
        this->os_ << "], ";
    }
    else
        this->os_ << "[], ";

    // Print the MethodNodes contained in a class
    if (!methodNodes.empty())
    {
        this->os_ << std::endl << "\t[";
        for (auto it = methodNodes.begin(); it != methodNodes.end() - 1; ++it)
        {
            this->indent_ = 1;
            (*it)->accept(*this);
            this->os_ << ",";
            this->os_ << std::endl << "\t";
        }
        methodNodes.back()->accept(*this);
        this->os_ << "])";
    }
    else
        this->os_ << "[])";

    return;
}

void DumpASTVisitor::visit(MethodNode &methodNode)
{
    // Print the name of the method
    this->os_ << "Method(";
    methodNode.objectID().accept(*this);
    this->os_ << ", ";

    // Print FormalsNode if any
    try
    {
        FormalsNode &node = dynamic_cast<FormalsNode &>(methodNode.formals());
        this->indent_++;
        this->os_ << std::endl;
        INDENT;
        this->os_ << "[";
        node.accept(*this);
        this->os_ << "], ";
    }
    catch (std::bad_cast &bc)
    {
        this->os_ << "[], ";
    }

    // Print the type of the Method
    this->os_ << methodNode.type() << ", ";
    // Print the block of a method
    methodNode.block().accept(*this);
    this->os_ << ")";
    return;
}

void DumpASTVisitor::visit(FormalsNode &formalsNode)
{
    std::vector<std::pair<ObjectIDNode *, std::string *> *> &formals =
        formalsNode.formals();

    // Loop on the formals vector
    for (auto it = formals.begin(); it != formals.end() - 1; ++it)
    {
        // Print the name
        (*it)->first->accept(*this);
        // Print the type
        this->os_ << " : " << *(*it)->second << ", " << std::endl;
        INDENT;
    }
    // Print the last element of the vector
    formals.back()->first->accept(*this);
    this->os_ << " : " << *formals.back()->second;

    return;
}

void DumpASTVisitor::visit(FieldNode &fieldNode)
{
    this->os_ << "Field(";
    // Print the name of the Field
    fieldNode.objectID().accept(*this);
    // Print the type of the Field
    this->os_ << ", " << fieldNode.type();

    // Print the init-expr if any
    try
    {
        Node &node = dynamic_cast<Node &>(fieldNode.assignExpr());
        this->os_ << ", ";
        node.accept(*this);
    }
    catch (std::bad_cast &bc)
    {
    }

    this->os_ << ")";
    return;
}

void DumpASTVisitor::visit(ObjectIDNode &objectIDNode)
{
    // Print the name of the node
    this->os_ << objectIDNode.name() << EXPRTYPE(objectIDNode);
    return;
}

void DumpASTVisitor::visit(IfNode &ifNode)
{
    std::vector<Node *> &exprs = ifNode.exprs();

    this->os_ << "If(";
    // Print the different expressions of the If expression
    for (auto it = exprs.begin(); it != exprs.end() - 1; ++it)
    {
        (*it)->accept(*this);
        this->os_ << ", ";
    }
    exprs.back()->accept(*this);
    this->os_ << ")" << EXPRTYPE(ifNode);
    return;
}

void DumpASTVisitor::visit(WhileNode &whileNode)
{
    this->os_ << "While(";
    // Print the cond expression
    whileNode.condExpr().accept(*this);
    this->os_ << ", ";
    // Print the body expression
    whileNode.bodyExpr().accept(*this);
    this->os_ << ")" << EXPRTYPE(whileNode);
    return;
}

void DumpASTVisitor::visit(LetNode &letNode)
{
    this->os_ << "Let(";
    // Print the name of the Let expression
    letNode.objectID().accept(*this);
    // Print the type of the Let expression
    this->os_ << ", " << letNode.type() << ", ";
    // Print the init expression if any
    try
    {
        Node &node = dynamic_cast<Node &>(letNode.assignExpr());
        node.accept(*this);
        this->os_ << ", ";
    }
    catch (std::bad_cast &bc)
    {
    }

    // Print the scope expression
    letNode.inExpr().accept(*this);
    this->os_ << ")" << EXPRTYPE(letNode);
    return;
}

void DumpASTVisitor::visit(AssignNode &assignNode)
{
    this->os_ << "Assign(";
    // Print the name of the Assign expression
    assignNode.objectID().accept(*this);
    this->os_ << ", ";
    // Print the expression of the Assign expression
    assignNode.assignExpr().accept(*this);
    this->os_ << ")" << EXPRTYPE(assignNode);
    return;
}

void DumpASTVisitor::visit(BinaryOpNode &binaryOpNode)
{
    this->os_ << "BinOp(";
    // Print the operator of the Binary operator expression
    switch (binaryOpNode.binaryType())
    {
    case BinaryOpNode::binaryType::AND:
        this->os_ << "and, ";
        break;
    case BinaryOpNode::binaryType::EQUAL:
        this->os_ << "=, ";
        break;
    case BinaryOpNode::binaryType::LOWER:
        this->os_ << "<, ";
        break;
    case BinaryOpNode::binaryType::LOWERQ:
        this->os_ << "<=, ";
        break;
    case BinaryOpNode::binaryType::PLUS:
        this->os_ << "+, ";
        break;
    case BinaryOpNode::binaryType::MINUS:
        this->os_ << "-, ";
        break;
    case BinaryOpNode::binaryType::TIMES:
        this->os_ << "*, ";
        break;
    case BinaryOpNode::binaryType::DIVIDE:
        this->os_ << "/, ";
        break;
    case BinaryOpNode::binaryType::POW:
        this->os_ << "^, ";
        break;
    }
    // Print the left expression
    binaryOpNode.leftExpr().accept(*this);
    this->os_ << ", ";
    // Print the right expression
    binaryOpNode.rightExpr().accept(*this);
    this->os_ << ")" << EXPRTYPE(binaryOpNode);
    return;
}

void DumpASTVisitor::visit(UnaryOpNode &unaryOpNode)
{
    this->os_ << "UnOp(";

    // Print the Unary operator
    switch (unaryOpNode.unaryType())
    {
    case UnaryOpNode::unaryType::NOT:
        this->os_ << "not, ";
        break;
    case UnaryOpNode::unaryType::ISNULL:
        this->os_ << "isnull, ";
        break;
    case UnaryOpNode::unaryType::MINUS:
        this->os_ << "-, ";
        break;
    }
    // Print the expression of the unary operator expression
    unaryOpNode.expr().accept(*this);
    this->os_ << ")" << EXPRTYPE(unaryOpNode);
    return;
}

void DumpASTVisitor::visit(CallNode &callNode)
{
    ObjectIDNode &name = callNode.objectID();
    Node &object = callNode.expr();
    std::vector<Node *> &args = callNode.args();

    this->os_ << "Call(";
    // Print the object expression of the Call expression
    object.accept(*this);
    this->os_ << ", ";

    // Print the method name of the Call expression
    name.accept(*this);
    this->os_ << ", ";
    // Print the expression list contained in the Call expression
    if (!args.empty())
    {
        this->indent_++;
        this->os_ << std::endl;
        INDENT;
        this->os_ << "[";
        int buffer = this->indent_;
        for (auto it = args.begin(); it != args.end() - 1; ++it)
        {
            (*it)->accept(*this);
            this->os_ << ", " << std::endl;
            INDENT;
        }
        args.back()->accept(*this);
        this->os_ << "])" << EXPRTYPE(callNode);
        this->indent_ = buffer;
    }
    else
        this->os_ << "[])" << EXPRTYPE(callNode);
    return;
}

void DumpASTVisitor::visit(NewNode &newNode)
{
    // Print the type-name of the New expression
    this->os_ << "New(" << newNode.typeID() << ")" << EXPRTYPE(newNode);
    return;
}

void DumpASTVisitor::visit(LiteralNode &literalNode)
{
    // Print the value of the literal expression
    this->os_ << literalNode.value() << EXPRTYPE(literalNode);
    return;
}

void DumpASTVisitor::visit(BlockNode &blockNode)
{
    std::vector<Node *> &exprs = blockNode.exprs();
    // Print the expression as a list if vector of Node greater than 1
    if (exprs.size() > 1)
    {
        this->indent_++;
        this->os_ << std::endl;
        INDENT;
        this->os_ << "[";
        for (auto it = exprs.begin(); it != exprs.end() - 1; ++it)
        {
            int buffer = this->indent_;
            (*it)->accept(*this);
            this->indent_ = buffer;
            this->os_ << ", " << std::endl;
            INDENT;
        }
        exprs.back()->accept(*this);
        this->os_ << "]" << EXPRTYPE(blockNode);
    }
    // Else print the expression directly (Not a list)
    else if (exprs.size() == 1)
        exprs.back()->accept(*this);
    return;
}

void DumpASTVisitor::visit(UnitNode &unitNode)
{
    this->os_ << "()" << EXPRTYPE(unitNode);
    return;
}
