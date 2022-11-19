/*!
 * \file nodes.cpp
 * \brief Source code containing the different classes allowing the creation of
 * different nodes for the AST. \author Tahiraj Arian \author Leroy Antoine
 * \version 0.1
 */

#include <astTree/nodes.hpp>
#include <typeinfo>
#include <visitors/visitor.hpp>

/*******************************************************************************
 *                                  Class Node *
 *******************************************************************************/

Node::Node(YYLTYPE &location) : location_(location) {}

Node::~Node() { delete &this->location_; }

Node *Node::parent() { return this->parent_; }

void Node::setParent(Node *parent) { this->parent_ = parent; }

int &Node::scopeIndex() { return this->scopeIndex_; }

YYLTYPE &Node::location() { return this->location_; }

void Node::setExprType(std::string &type) { this->exprType_ = &type; }

std::string *Node::exprType(void) { return this->exprType_; }

/*******************************************************************************
 *                              Class ObjectIdNode *
 *******************************************************************************/

ObjectIDNode::ObjectIDNode(YYLTYPE &location, std::string &name)
    : Node(location), name_(name)
{
}

ObjectIDNode::~ObjectIDNode() { delete &this->name_; }

void ObjectIDNode::accept(Visitor &visitor) { visitor.visit(*this); }

std::string &ObjectIDNode::name(void) { return this->name_; }

/*******************************************************************************
 *                                 Class IfNode *
 *******************************************************************************/

IfNode::IfNode(YYLTYPE &location, std::vector<Node *> &exprs)
    : Node(location), exprs_(exprs)
{
    for (auto x : this->exprs_)
        x->setParent(this);
}

IfNode::~IfNode()
{
    for (auto x : this->exprs_)
        delete x;
    delete &this->exprs_;
}

void IfNode::accept(Visitor &visitor) { visitor.visit(*this); }

std::vector<Node *> &IfNode::exprs(void) { return this->exprs_; }

/*******************************************************************************
 *                             Class WhileNode *
 *******************************************************************************/

WhileNode::WhileNode(YYLTYPE &location, Node &condExpr, Node &bodyExpr)
    : Node(location), condExpr_(condExpr), bodyExpr_(bodyExpr)
{
    this->condExpr_.setParent(this);
    this->bodyExpr_.setParent(this);
}

WhileNode::~WhileNode()
{
    delete &this->condExpr_;
    delete &this->bodyExpr_;
}

void WhileNode::accept(Visitor &visitor) { visitor.visit(*this); }

Node &WhileNode::condExpr() { return this->condExpr_; }

Node &WhileNode::bodyExpr() { return this->bodyExpr_; }

/*******************************************************************************
 *                                 Class LetNode *
 *******************************************************************************/

LetNode::LetNode(YYLTYPE &location, ObjectIDNode &objectID,
                 DummyNode &assignExpr, Node &inExpr, std::string &type)
    : Node(location), objectID_(objectID), assignExpr_(assignExpr),
      inExpr_(inExpr), type_(type)
{
    new DummyNode();
    this->objectID_.setParent(this);
    try
    {
        Node &node = dynamic_cast<Node &>(this->assignExpr_);
        node.setParent(this);
    }
    catch (std::bad_cast &bc)
    {
    }

    this->inExpr_.setParent(this);
}

LetNode::~LetNode()
{
    delete &this->objectID_;
    delete &this->assignExpr_;
    delete &this->inExpr_;
    delete &this->type_;
}

void LetNode::accept(Visitor &visitor) { visitor.visit(*this); }

ObjectIDNode &LetNode::objectID(void) { return this->objectID_; }

DummyNode &LetNode::assignExpr(void) { return this->assignExpr_; }

Node &LetNode::inExpr(void) { return this->inExpr_; }

std::string &LetNode::type(void) { return this->type_; }

/*******************************************************************************
 *                             Class AssignNode *
 *******************************************************************************/

AssignNode::AssignNode(YYLTYPE &location, ObjectIDNode &objectID,
                       Node &assignExpr)
    : Node(location), objectID_(objectID), assignExpr_(assignExpr)
{
    this->objectID_.setParent(this);
    this->assignExpr_.setParent(this);
}

AssignNode::~AssignNode()
{
    delete &this->objectID_;
    delete &this->assignExpr_;
}

void AssignNode::accept(Visitor &visitor) { visitor.visit(*this); }

ObjectIDNode &AssignNode::objectID(void) { return this->objectID_; }

Node &AssignNode::assignExpr(void) { return this->assignExpr_; }

/*******************************************************************************
 *                            Class BinaryOpNode *
 *******************************************************************************/

BinaryOpNode::BinaryOpNode(YYLTYPE &location, enum binaryType binaryType,
                           Node &leftExpr, Node &rightExpr)
    : Node(location), binaryType_(binaryType), leftExpr_(leftExpr),
      rightExpr_(rightExpr)
{
    this->leftExpr_.setParent(this);
    this->rightExpr_.setParent(this);
}

BinaryOpNode::~BinaryOpNode()
{
    delete &this->leftExpr_;
    delete &this->rightExpr_;
}

Node &BinaryOpNode::leftExpr() { return this->leftExpr_; }

Node &BinaryOpNode::rightExpr() { return this->rightExpr_; }

enum BinaryOpNode::binaryType BinaryOpNode::binaryType(void)
{
    return this->binaryType_;
}

void BinaryOpNode::accept(Visitor &visitor) { visitor.visit(*this); }

/*******************************************************************************
 *                           Class UnaryOpNode *
 *******************************************************************************/

UnaryOpNode::UnaryOpNode(YYLTYPE &location, enum unaryType unaryType,
                         Node &expr)
    : Node(location), unaryType_(unaryType), expr_(expr)
{
    this->expr_.setParent(this);
}

UnaryOpNode::~UnaryOpNode() { delete &this->expr_; }

void UnaryOpNode::accept(Visitor &visitor) { visitor.visit(*this); }

enum UnaryOpNode::unaryType UnaryOpNode::unaryType()
{
    return this->unaryType_;
}

Node &UnaryOpNode::expr() { return this->expr_; }

/*******************************************************************************
 *                              Class CallNode *
 *******************************************************************************/

CallNode::CallNode(YYLTYPE &location, Node &object, ObjectIDNode &objectID,
                   std::vector<Node *> &args)
    : Node(location), expr_(object), objectID_(objectID), args_(args)
{
    this->expr_.setParent(this);
    this->objectID_.setParent(this);

    for (auto x : this->args_)
        x->setParent(this);
}

CallNode::~CallNode()
{
    delete &this->expr_;
    delete &this->objectID_;
    for (auto x : this->args_)
        delete x;
    delete &args_;
}

void CallNode::accept(Visitor &visitor) { visitor.visit(*this); }

Node &CallNode::expr(void) { return this->expr_; }

ObjectIDNode &CallNode::objectID(void) { return this->objectID_; }

std::vector<Node *> &CallNode::args(void) { return this->args_; }

/*******************************************************************************
 *                               Class NewNode *
 *******************************************************************************/

NewNode::NewNode(YYLTYPE &location, std::string &typeID)
    : Node(location), typeID_(typeID)
{
}

NewNode::~NewNode() { delete &this->typeID_; }

void NewNode::accept(Visitor &visitor) { visitor.visit(*this); }

std::string &NewNode::typeID(void) { return this->typeID_; }

/*******************************************************************************
 *                             Class LiteralNode *
 *******************************************************************************/

LiteralNode::LiteralNode(YYLTYPE &location, enum literalType literalType,
                         std::string &value)
    : Node(location), literalType_(literalType), value_(value)
{
}

LiteralNode::~LiteralNode() { delete &this->value_; }

void LiteralNode::accept(Visitor &visitor) { visitor.visit(*this); }

std::string &LiteralNode::value(void) { return this->value_; }

enum LiteralNode::literalType LiteralNode::literalType()
{
    return this->literalType_;
}

/*******************************************************************************
 *                             Class BlockNode *
 *******************************************************************************/

BlockNode::BlockNode(YYLTYPE &location, std::vector<Node *> &exprs)
    : Node(location), exprs_(exprs)
{
    for (auto x : this->exprs_)
        x->setParent(this);
}

BlockNode::~BlockNode()
{
    for (auto x : this->exprs_)
        delete x;
    delete &this->exprs_;
}

void BlockNode::accept(Visitor &visitor) { visitor.visit(*this); }

std::vector<Node *> &BlockNode::exprs(void) { return this->exprs_; }

/*******************************************************************************
 *                            Class UnitNode *
 *******************************************************************************/

UnitNode::UnitNode(YYLTYPE &location) : Node(location) {}

void UnitNode::accept(Visitor &visitor) { visitor.visit(*this); }

/*******************************************************************************
 *                             Class FieldNode *
 *******************************************************************************/

FieldNode::FieldNode(YYLTYPE &location, ObjectIDNode &objectID,
                     DummyNode &assignExpr, std::string &type)
    : Node(location), objectID_(objectID), assignExpr_(assignExpr), type_(type)
{
    this->objectID_.setParent(this);

    try
    {
        Node &node = dynamic_cast<Node &>(this->assignExpr_);
        node.setParent(this);
    }
    catch (std::bad_cast &bc)
    {
    }
}

FieldNode::~FieldNode()
{
    delete &this->objectID_;
    delete &this->assignExpr_;
    delete &this->type_;
}

void FieldNode::accept(Visitor &visitor) { visitor.visit(*this); }

ObjectIDNode &FieldNode::objectID(void) { return this->objectID_; }

DummyNode &FieldNode::assignExpr(void) { return this->assignExpr_; }

std::string &FieldNode::type(void) { return this->type_; }

/*******************************************************************************
 *                          Class FormalsNode *
 *******************************************************************************/

FormalsNode::FormalsNode(
    YYLTYPE &location,
    std::vector<std::pair<ObjectIDNode *, std::string *> *> &formals)
    : Node(location), formals_(formals)
{
    for (auto x : this->formals_)
        if (x->first)
            x->first->setParent(this);
}

FormalsNode::~FormalsNode()
{
    for (auto x : this->formals_)
    {
        if (x)
        {
            delete x->first;
            delete x->second;
        }
        delete x;
    }
    delete &this->formals_;
}

void FormalsNode::accept(Visitor &visitor) { visitor.visit(*this); }

std::vector<std::pair<ObjectIDNode *, std::string *> *> &
FormalsNode::formals(void)
{
    return this->formals_;
}

/*******************************************************************************
 *                             Class MethodNode *
 *******************************************************************************/

MethodNode::MethodNode(YYLTYPE &location, BlockNode &block,
                       ObjectIDNode &objectID, DummyNode &formals,
                       std::string &type)
    : Node(location), block_(block), objectID_(objectID), formals_(formals),
      type_(type)
{
    this->block_.setParent(this);
    this->objectID_.setParent(this);

    try
    {
        Node &node = dynamic_cast<Node &>(this->formals_);
        node.setParent(this);
    }
    catch (std::bad_cast &bc)
    {
    }
}

MethodNode::~MethodNode()
{
    delete &this->block_;
    delete &this->objectID_;
    delete &this->formals_;
    delete &this->type_;
}

void MethodNode::accept(Visitor &visitor) { visitor.visit(*this); }

ObjectIDNode &MethodNode::objectID(void) { return this->objectID_; }

DummyNode &MethodNode::formals(void) { return this->formals_; }

std::string &MethodNode::type(void) { return this->type_; }

BlockNode &MethodNode::block(void) { return this->block_; }

/*******************************************************************************
 *                            Class ClassNode *
 *******************************************************************************/

ClassNode::ClassNode(YYLTYPE &location, std::string &className,
                     std::string &superClassName,
                     std::vector<FieldNode *> &fieldNodes,
                     std::vector<MethodNode *> &methodNodes)
    : Node(location), className_(className), superClassName_(superClassName),
      fieldNodes_(fieldNodes), methodNodes_(methodNodes)
{
    for (auto x : this->fieldNodes_)
        if (x)
            x->setParent(this);
    for (auto x : this->methodNodes_)
        if (x)
            x->setParent(this);

    this->marked_ = false;
}

ClassNode::~ClassNode()
{
    delete &this->className_;
    delete &this->superClassName_;

    for (auto x : this->fieldNodes_)
        delete x;

    delete &this->fieldNodes_;

    for (auto x : this->methodNodes_)
        delete x;

    delete &this->methodNodes_;
}

bool ClassNode::marked(void) { return this->marked_; }

void ClassNode::setMarked(bool marked) { this->marked_ = marked; }

void ClassNode::accept(Visitor &visitor) { visitor.visit(*this); }

std::string &ClassNode::className(void) { return this->className_; }

std::string &ClassNode::superClassName(void) { return this->superClassName_; }

std::vector<FieldNode *> &ClassNode::fieldNodes(void)
{
    return this->fieldNodes_;
}

std::vector<MethodNode *> &ClassNode::methodNodes(void)
{
    return this->methodNodes_;
}

/*******************************************************************************
 *                              Class AstNode *
 *******************************************************************************/

AstNode::AstNode(YYLTYPE &location, std::vector<ClassNode *> &classes)
    : Node(location), classes_(classes), inheritanceTree_(*new InheriTree()),
      variableTableTree_(*new VariableTableTree()),
      functionTableTree_(*new FunctionTableTree()),
      classMap_(*new std::unordered_map<std::string, ClassNode *>())
{
    for (auto x : this->classes_)
        if (x)
            x->setParent(this);

    // Adding Object Node
    this->dumpName_ = new std::string("Object");
    this->dumpMethodInfo_ = new std::vector<MethodInfo *>();
    this->inheritanceTree_.insertRoot(*this->dumpName_);
    this->variableTableTree_.insertRoot(*this->dumpName_);
    this->functionTableTree_.insertRoot(*this->dumpName_);

    FunctionTable &funTable = *this->functionTableTree_.table(*this->dumpName_);

    std::vector<std::string *> names = std::vector<std::string *>();
    std::vector<std::string *> types = std::vector<std::string *>();
    std::vector<std::string *> parameters = std::vector<std::string *>();

    // Adding methods
    names.push_back(new std::string("print"));
    names.push_back(new std::string("printBool"));
    names.push_back(new std::string("printInt32"));
    names.push_back(new std::string("inputLine"));
    names.push_back(new std::string("inputBool"));
    names.push_back(new std::string("inputInt32"));

    types.push_back(new std::string("Object"));
    types.push_back(new std::string("Object"));
    types.push_back(new std::string("Object"));
    types.push_back(new std::string("string"));
    types.push_back(new std::string("bool"));
    types.push_back(new std::string("int32"));

    parameters.push_back(new std::string("string"));
    parameters.push_back(new std::string("bool"));
    parameters.push_back(new std::string("int32"));

    for (int i = 0; i < 6; ++i)
    {
        std::vector<std::string *> &formals = *new std::vector<std::string *>();
        if (i < 3)
            formals.push_back(parameters[i]);

        MethodInfo &methodInfo = *new MethodInfo(
            this->location_, *types[i], *names[i], formals, *this->dumpName_);
        funTable.insert(*names[i], methodInfo);

        this->dumpMethodInfo_->push_back(&methodInfo);
    }

    this->parent_ = nullptr;
}

AstNode::~AstNode()
{
    // Freeing non class variable infos
    for (auto x : this->variableTableTree_.otherKeys())
    {
        for (auto y : this->variableTableTree_.table(*x)->keys())
        {
            delete this->variableTableTree_.table(*x)->value(*y);
            if (*y == "self")
                delete y;
        }
    }

    // Freeing Info objects
    for (auto classIt : this->classes_)
        if (this->inheritanceTree_.contains(classIt->className()))
        {
            FunctionTable &functionTable =
                *this->functionTableTree_.table(classIt->className());
            VariableTable &variableTable =
                *this->variableTableTree_.table(classIt->className());

            for (auto methodIt : classIt->methodNodes())
            {
                MethodInfo &methodInfo =
                    *functionTable.value(methodIt->objectID().name());
                delete &methodInfo.formals();
                delete &methodInfo;
            }

            for (auto fieldIt : classIt->fieldNodes())
                delete variableTable.value(fieldIt->objectID().name());
        }

    // Freeing trees and mapping
    delete &this->inheritanceTree_;
    delete &this->variableTableTree_;
    delete &this->functionTableTree_;
    delete &this->classMap_;

    // Recursive freeing
    for (auto x : this->classes_)
        delete x;
    delete &this->classes_;

    // Freeing Object class
    for (auto x : *this->dumpMethodInfo_)
    {
        delete &x->name();
        delete &x->type();
        for (auto y : x->formals())
            delete y;
        delete &x->formals();
        delete x;
    }
    delete this->dumpMethodInfo_;
    delete this->dumpName_;
}

void AstNode::accept(Visitor &visitor) { visitor.visit(*this); }

InheriTree &AstNode::inheritanceTree() { return this->inheritanceTree_; }

VariableTableTree &AstNode::variableTableTree()
{
    return this->variableTableTree_;
}
FunctionTableTree &AstNode::functionTableTree()
{
    return this->functionTableTree_;
}

std::unordered_map<std::string, ClassNode *> &AstNode::classMap(void)
{
    return this->classMap_;
}

std::vector<ClassNode *> &AstNode::classes() { return this->classes_; }
