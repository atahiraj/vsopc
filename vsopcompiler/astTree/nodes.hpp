#ifndef NODES_H
#define NODES_H

/*!
 * \file nodes.hpp
 * \brief Header containing the different classes allowing the creation of
 * different nodes for the AST. \author Tahiraj Arian \author Leroy Antoine
 * \version 0.1
 */

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

class Visitor;
typedef struct YYLTYPE YYLTYPE;

#include <parser/parser.hpp>
#include <templates/info.hpp>
#include <templates/inheritanceTree.hpp>
#include <templates/tableTree.hpp>

#ifndef TABLE_TREE_TYPES
#define TABLE_TREE_TYPES

typedef InheritanceTree<std::string> InheriTree;
typedef Info<YYLTYPE, std::string> VariableInfo;
typedef TableTree<std::string, int, std::string, VariableInfo>
    VariableTableTree;
typedef Table<std::string, VariableInfo> VariableTable;
typedef FunctionInfo<YYLTYPE, std::string, std::string,
                     std::vector<std::string *>, std::string>
    MethodInfo;
typedef TableTree<std::string, int, std::string, MethodInfo> FunctionTableTree;
typedef Table<std::string, MethodInfo> FunctionTable;

#endif

/*! \class DummyNode
 * \brief Abstract class used as a basis for each AST node.
 */
class DummyNode
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the DummyNode class.
     */
    virtual ~DummyNode() = default;
};

/*! \class Node
 * \brief Abstract class representing a node.
 *
 * This class representing a node contains all the information that all the
 * different nodes of the AST must carry.
 */
class Node : public DummyNode
{
  public:
    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *corresponding expression.
     *
     * Constructor of the Node class.
     */
    Node(YYLTYPE &location);
    /*!
     * \brief Destructor
     *
     * Destructor of the Node class.
     */
    virtual ~Node() = 0;

    /*!
     * \brief Getter of the parent Node.
     *
     * This function is the getter of the variable object parent.
     *
     * \return Pointer to the object's parent (Node*).
     */
    Node *parent(void);

    /*!
     * \brief Getter of the scopeIndex variable.
     *
     * This function is the getter of the variable scopeIndex.
     *
     * \return The value of the variable scopeIndex (int).
     */
    int &scopeIndex(void);

    /*!
     * \brief Getter of the variable location.
     *
     * This function is the getter of the variable location.
     *
     * \return The value of the variable location (YYLTYPE).
     */
    YYLTYPE &location(void);

    /*!
     * \brief Setter of the parent Node.
     *
     * This function is the setter of the variable object parent.
     *
     * \param parent: Pointer to the object's new parent (Node*).
     */
    void setParent(Node *parent);

    /*!
     * \brief Setter of the variable exprType_.
     *
     * This function is the setter of the variable exprType_.
     *
     * \param type: The type of the Node (string).
     */
    void setExprType(std::string &type);

    /*!
     * \brief getter of the variable exprType_.
     *
     * This function is the getter of the variable exprType_.
     *
     * \return exprType_: Pointer to the object's exprType_ (string*).
     */
    std::string *exprType(void);

    /*!
     * \brief Visitor pattern of Node
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    virtual void accept(Visitor &visitor) = 0;

  protected:
    int scopeIndex_ = 0; /*!< Variable representing the index of a scope */
    YYLTYPE &location_;  /*!< Variable representing the location of the node in
                            the vsop file */
    Node *parent_;       /*!< Pointer to an object's parent*/
    std::string *exprType_ =
        nullptr; /*!< String representing the type of the node*/
};

/*! \class ObjectIDNode
 * \brief Class representing an Object-Identifier.
 *
 * This class representing a Object-Identifier contains all the information
 * necessary to represent it.
 */
class ObjectIDNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *Object-Identifier expression. \param name: String representing the name of
     *the Object-Identifier
     *
     * Constructor of the ObjectIDNode class.
     */
    ObjectIDNode(YYLTYPE &location, std::string &name);

    /*!
     * \brief Destructor
     *
     * Destructor of the ObjectIDNode class.
     */
    ~ObjectIDNode() override;

    /*!
     * \brief Visitor pattern of Node
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable name.
     *
     * This function is the getter of the variable name.
     *
     * \return name: the name of the Object-Identifier (string).
     */
    std::string &name(void);

  private:
    std::string
        &name_; /*!< String representing the name of the Object-Identifier*/
};

/*! \class IfNode
 * \brief Class representing an If expression.
 *
 * This class representing a if expression contains all the information
 * necessary to represent it.
 */
class IfNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *If expression. \param exprs: Vector containing pointers to Node objects.
     *
     * Constructor of the IfNode class.
     */
    IfNode(YYLTYPE &location, std::vector<Node *> &exprs);

    /*!
     * \brief Destructor
     *
     * Destructor of the IfNode class.
     */
    ~IfNode() override;

    /*!
     * \brief Visitor pattern of IfNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable exprs_.
     *
     * This function is the getter of the variable exprs_.
     *
     * \return exprs_: Vector containing pointers to Node objects.
     * (vector<Node*>).
     */
    std::vector<Node *> &exprs(void);

  private:
    std::vector<Node *>
        &exprs_; /*!< Vector containing pointers to Node objects.*/
};

/*! \class WhileNode
 * \brief Class representing a while expression.
 *
 * This class representing a while expression contains all the information
 * necessary to represent it.
 */
class WhileNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *while expression. \param condExpr: Node representing the expression of the
     *condition of the while. \param bodyExpr: Node representing the body of the
     *while.
     *
     * Constructor of the WhileNode class.
     */
    WhileNode(YYLTYPE &location, Node &condExpr, Node &bodyExpr);

    /*!
     * \brief Destructor
     *
     * Destructor of the WhileNode class.
     */
    ~WhileNode() override;

    /*!
     * \brief Visitor pattern of WhileNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable condExpr_.
     *
     * This function is the getter of the variable condExpr_.
     *
     * \return condExpr_: A Node representing the expression of the condition of
     * the while. (Node).
     */
    Node &condExpr();

    /*!
     * \brief Getter of the variable bodyExpr_.
     *
     * This function is the getter of the variable bodyExpr_.
     *
     * \return bodyExpr_: A Node representing the body of the while. (Node).
     */
    Node &bodyExpr();

  private:
    Node &condExpr_; /*!< Node representing the expression of the condition of
                        the while.*/
    Node &bodyExpr_; /*!< A Node representing the body of the while.*/
};

/*! \class LetNode
 * \brief Class representing a Let expression.
 *
 * This class representing a Let expression contains all the information
 * necessary to represent it.
 */
class LetNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *Let expression. \param objectID: Node representing an Object-Identifier.
     *\param assignExpr: Dummy Node representing the assign expression.
     *\param inExpr: Node representing the in expression.
     *\param type: String representing the type of the Let expression.
     *
     * Constructor of the LetNode class.
     */
    LetNode(YYLTYPE &location, ObjectIDNode &objectID, DummyNode &assignExpr,
            Node &inExpr, std::string &type);

    /*!
     * \brief Destructor
     *
     * Destructor of the LetNode class.
     */
    ~LetNode() override;

    /*!
     * \brief Getter of the variable objectID_.
     *
     * This function is the getter of the variable objectID_.
     *
     * \return objectID_: A Node representing an Object-Identifier.
     * (ObjectIDNode).
     */
    ObjectIDNode &objectID(void);

    /*!
     * \brief Getter of the variable assignExpr_.
     *
     * This function is the getter of the variable assignExpr_.
     *
     * \return assignExpr_: A Dummy Node representing the assign expression.
     * (DummyNode).
     */
    DummyNode &assignExpr(void);

    /*!
     * \brief Getter of the variable inExpr_.
     *
     * This function is the getter of the variable inExpr_.
     *
     * \return inExpr_: A Node representing the in expression. (Node).
     */
    Node &inExpr(void);

    /*!
     * \brief Getter of the variable type_.
     *
     * This function is the getter of the variable type_.
     *
     * \return type_: String representing the type of the Let expression.
     */
    std::string &type(void);

    /*!
     * \brief Visitor pattern of LetNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

  private:
    ObjectIDNode &objectID_; /*!< A Node representing an Object-Identifier.*/
    DummyNode
        &assignExpr_; /*!< A Dummy Node representing the assign expression.*/
    Node &inExpr_;    /*!< A Node representing the in expression.*/
    std::string
        &type_; /*!< String representing the type of the Let expression.*/
};

/*! \class AssignNode
 * \brief Class representing an Asssign expression.
 *
 * This class representing an Asssign expression contains all the information
 * necessary to represent it.
 */
class AssignNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *Assign expression. \param objectID: Node representing an
     *Object-Identifier. \param assignExpr: Node representing the assign
     *expression.
     *
     * Constructor of the AssignNode class.
     */
    AssignNode(YYLTYPE &location, ObjectIDNode &objectID, Node &assignExpr);

    /*!
     * \brief Destructor
     *
     * Destructor of the AssignNode class.
     */
    ~AssignNode() override;

    /*!
     * \brief Visitor pattern of AssignNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable objectID_.
     *
     * This function is the getter of the variable objectID_.
     *
     * \return objectID_: A Node representing an Object-Identifier.
     * (ObjectIDNode).
     */
    ObjectIDNode &objectID(void);

    /*!
     * \brief Getter of the variable assignExpr_.
     *
     * This function is the getter of the variable assignExpr_.
     *
     * \return assignExpr_: A Node representing the assign expression. (Node).
     */
    Node &assignExpr(void);

  private:
    ObjectIDNode &objectID_; /*!< A Node representing an Object-Identifier.*/
    Node &assignExpr_;       /*!< A Node representing the assign expression.*/
};

/*! \class BinaryOpNode
 * \brief Class representing a Binary operator.
 *
 * This class representing a Binary operator contains all the information
 * necessary to represent it.
 */
class BinaryOpNode : public Node
{
  public:
    /*!
     * \enum binaryType
     * \brief Binary perators implemented in the VSOP language.
     *
     * binaryType is a series of predefined constants to represent a binary
     * operator.
     */
    enum class binaryType
    {
        AND,
        EQUAL,
        LOWER,
        LOWERQ,
        PLUS,
        MINUS,
        TIMES,
        DIVIDE,
        POW
    };

    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *binary operator. \param binaryType: constant representing the type of the
     *binary operator. \param leftExpr: Node representing the right expression
     *of the binary operator. \param rightExpr: Node representing the left
     *expression of the binary operator.
     *
     * Constructor of the BinaryOpNode class.
     */
    BinaryOpNode(YYLTYPE &location, enum binaryType binaryType, Node &leftExpr,
                 Node &rightExpr);

    /*!
     * \brief Destructor
     *
     * Destructor of the BinaryOpNode class.
     */
    ~BinaryOpNode() override;

    /*!
     * \brief Getter of the variable leftExpr_.
     *
     * This function is the getter of the variable leftExpr_.
     *
     * \return leftExpr_: A Node representing the left expression of the
     * Operator. (Node).
     */
    Node &leftExpr(void);

    /*!
     * \brief Getter of the variable rightExpr_.
     *
     * This function is the getter of the variable rightExpr_.
     *
     * \return rightExpr_: A Node representing the right expression of the
     * binary operator. (Node).
     */
    Node &rightExpr(void);

    /*!
     * \brief Getter of the variable binaryType_.
     *
     * This function is the getter of the variable binaryType_.
     *
     * \return binaryType_: A constant representing the type of the binary
     * operator. (binaryType).
     */
    enum binaryType binaryType(void);

    /*!
     * \brief Visitor pattern of BinaryOpNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

  private:
    enum binaryType binaryType_; /*!< A constant representing the type of the
                                    binary operator.*/
    Node &leftExpr_; /*!< A Node representing the right expression of the binary
                        operator.*/
    Node &rightExpr_; /*!< A Node representing the left expression of the binary
                         operator.*/
};

/*! \class UnaryOpNode
 * \brief Class representing an Unary operator.
 *
 * This class representing an unary operator contains all the information
 * necessary to represent it.
 */
class UnaryOpNode : public Node
{
  public:
    /*!
     * \enum unaryType
     * \brief Unary operators implemented in the VSOP language.
     *
     * unaryType is a series of predefined constants to represent an unary
     * operator.
     */
    enum class unaryType
    {
        NOT,
        MINUS,
        ISNULL
    };

    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *unary operator. \param unaryType: constant representing the type of the
     *unary operator. \param expr: Node representing the expression of the unary
     *operator.
     *
     * Constructor of the UnaryOpNode class.
     */
    UnaryOpNode(YYLTYPE &location, enum unaryType unaryType, Node &expr);

    /*!
     * \brief Destructor
     *
     * Destructor of the UnaryOpNode class.
     */
    ~UnaryOpNode() override;

    /*!
     * \brief Visitor pattern of BinaryOpNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable unaryType_.
     *
     * This function is the getter of the variable unaryType_.
     *
     * \return unaryType_: A constant representing the type of the unary
     * operator. (unaryType).
     */
    enum unaryType unaryType(void);

    /*!
     * \brief Getter of the variable expr_.
     *
     * This function is the getter of the variable expr_.
     *
     * \return expr_: A Node representing the expression of the unary operator.
     * (Node).
     */
    Node &expr();

  private:
    enum unaryType unaryType_; /*!< A constant representing the type of the
                                  unary operator.*/
    Node
        &expr_; /*!< A Node representing the expression of the unary operator.*/
};

/*! \class CallNode
 * \brief Class representing a call expression.
 *
 * This class representing a call expression contains all the information
 * necessary to represent it.
 */
class CallNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *call. \param expr: Node representing an expression. \param objectID: Node
     *representing an Object-Identifier. \param args: Vector containing pointer
     *to nodes that represents the arguments of the call expression.
     *
     * Constructor of the CallNode class.
     */
    CallNode(YYLTYPE &location, Node &expr, ObjectIDNode &objectID,
             std::vector<Node *> &args);
    /*!
     * \brief Destructor
     *
     * Destructor of the CallNode class.
     */
    ~CallNode() override;

    /*!
     * \brief Visitor pattern of CallNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable expr_.
     *
     * This function is the getter of the variable expr_.
     *
     * \return expr_: A Node representing an expression. (Node).
     */
    Node &expr(void);

    /*!
     * \brief Getter of the variable objectID_.
     *
     * This function is the getter of the variable objectID_.
     *
     * \return objectID_: A Node representing an Object-Identifier.
     * (ObjectIDNode).
     */
    ObjectIDNode &objectID(void);

    /*!
     * \brief Getter of the variable args_.
     *
     * This function is the getter of the variable args_.
     *
     * \return args_: A vector containing pointer to nodes that represents the
     * arguments of the call expression. (vector<Node*>).
     */
    std::vector<Node *> &args(void);

  private:
    Node &expr_;             /*!< A Node representing an expression.*/
    ObjectIDNode &objectID_; /*!< A Node representing an Object-Identifier.*/
    std::vector<Node *>
        &args_; /*!< A vector containing pointer to nodes that represents the
                   arguments of the call expression.*/
};

/*! \class NewNode
 * \brief Class representing a New expression.
 *
 * This class representing a new expression contains all the information
 * necessary to represent it.
 */
class NewNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *new expression. \param typeID: String representing the type expression of
     *the node.
     *
     * Constructor of the NewNode class.
     */
    NewNode(YYLTYPE &location, std::string &typeID);

    /*!
     * \brief Destructor
     *
     * Destructor of the NewNode class.
     */
    ~NewNode() override;

    /*!
     * \brief Visitor pattern of NewNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable typeID_.
     *
     * This function is the getter of the variable typeID_.
     *
     * \return typeID_: A string representing the type expression of the node.
     */
    std::string &typeID(void);

  private:
    std::string
        &typeID_; /*!< A string representing the type expression of the node.*/
};

/*! \class LiteralNode
 * \brief Class representing a Literal expression.
 *
 * This class representing a Literal expression contains all the information
 * necessary to represent it.
 */
class LiteralNode : public Node
{
  public:
    /*!
     * \enum literalType
     * \brief Literals implemented in the VSOP language.
     *
     * literalType is a series of predefined constants to represent a literal
     * type.
     */
    enum class literalType
    {
        INTEGER,
        STRING,
        BOOL
    };

    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *literal. \param literalType: Constant representing the type of the
     *literal. \param value: String representing the value of the literal.
     *
     * Constructor of the LiteralNode class.
     */
    LiteralNode(YYLTYPE &location, enum literalType literalType,
                std::string &value);

    /*!
     * \brief Destructor
     *
     * Destructor of the LiteralNode class.
     */
    ~LiteralNode() override;

    /*!
     * \brief Getter of the variable literalType_.
     *
     * This function is the getter of the variable literalType_.
     *
     * \return literalType_: A constant representing the type of the literal.
     * (literalType).
     */
    enum literalType literalType(void);

    /*!
     * \brief Visitor pattern of literalType
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable value_.
     *
     * This function is the getter of the variable value_.
     *
     * \return value_: A string representing the value of the literal.
     */
    std::string &value(void);

  private:
    enum literalType
        literalType_;    /*!< A constant representing the type of the literal.*/
    std::string &value_; /*!< A string representing the value of the literal.*/
};

/*! \class BlockNode
 * \brief Class representing a Block expression.
 *
 * This class representing a Block expression contains all the information
 * necessary to represent it.
 */
class BlockNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *block. \param exprs: Vector containing pointers to Node representing
     *expressions of the block.
     *
     * Constructor of the BlockNode class.
     */
    BlockNode(YYLTYPE &location, std::vector<Node *> &exprs);

    /*!
     * \brief Destructor
     *
     * Destructor of the BlockNode class.
     */
    ~BlockNode() override;

    /*!
     * \brief Visitor pattern of BlockNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable exprs_.
     *
     * This function is the getter of the variable exprs_.
     *
     * \return exprs_: A vector containing pointers to Node representing
     * expressions of the block. (vector<Node*>)
     */
    std::vector<Node *> &exprs();

  private:
    std::vector<Node *> &exprs_; /*!< A vector containing pointers to Node
                                    representing expressions of the block.*/
};

/*! \class UnitNode
 * \brief Class representing an Unit expression.
 *
 *\param location: The location in the VSOP file of the declaration of the unit.
 *
 * This class representing an Unit expression contains all the information
 *necessary to represent it.
 */
class UnitNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the UnitNode class.
     */
    UnitNode(YYLTYPE &location);

    /*!
     * \brief Destructor
     *
     * Destructor of the UnitNode class.
     */
    ~UnitNode(void) = default;

    /*!
     * \brief Visitor pattern of UnitNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;
};

/*! \class FieldNode
 * \brief Class representing a Field expression.
 *
 * This class representing a Field expression contains all the information
 * necessary to represent it.
 */
class FieldNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     *\param location: The location in the VSOP file of the declaration of the
     *field. \param objectID: Node representing an Object-Identifier in the
     *field expression. \param assignExpr: Node representing an assign
     *expression in the field expression. \param type: String representing the
     *type of the field expression.
     *
     * Constructor of the FieldNode class.
     */
    FieldNode(YYLTYPE &location, ObjectIDNode &objectID, DummyNode &assignExpr,
              std::string &type);

    /*!
     * \brief Destructor
     *
     * Destructor of the FieldNode class.
     */
    ~FieldNode() override;

    /*!
     * \brief Visitor pattern of FieldNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable objectID_.
     *
     * This function is the getter of the variable objectID_.
     *
     * \return objectID_: A Node representing an Object-Identifier in the field
     * expression. (ObjectIDNode)
     */
    ObjectIDNode &objectID(void);
    /*!
     * \brief Getter of the variable assignExpr_.
     *
     * This function is the getter of the variable assignExpr_.
     *
     * \return assignExpr_: A Node representing an assign expression in the
     * field expression. (DummyNode)
     */
    DummyNode &assignExpr(void);
    /*!
     * \brief Getter of the variable type_.
     *
     * This function is the getter of the variable type_.
     *
     * \return type_: A String representing the type of the field expression.
     */
    std::string &type(void);

  private:
    ObjectIDNode &objectID_; /*!< A Node representing an Object-Identifier in
                                the field expression.*/
    DummyNode &assignExpr_; /*!< A Node representing an assign expression in the
                               field expression.*/
    std::string
        &type_; /*!< A String representing the type of the field expression.*/
};

/*! \class FormalsNode
 * \brief Class representing Formals.
 *
 * This class representing Formals contains all the information necessary to
 * represent it.
 */
class FormalsNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the FormalsNode class.
     *
     *\param location: The location in the VSOP file of the declaration of the
     *formals. \param formals: Vector containing pairs of pointer to
     *ObjectIDNode and String.
     */
    FormalsNode(
        YYLTYPE &location,
        std::vector<std::pair<ObjectIDNode *, std::string *> *> &formals);

    /*!
     * \brief Destructor
     *
     * Destructor of the FormalsNode class.
     */
    ~FormalsNode() override;

    /*!
     * \brief Visitor pattern of FormalsNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable formals_.
     *
     * This function is the getter of the variable formals_.
     *
     * \return formals_: A vector containing pairs of pointer to ObjectIDNode
     * and String. (vector<std::pair<ObjectIDNode*, std::string*>*>)
     */
    std::vector<std::pair<ObjectIDNode *, std::string *> *> &formals(void);

  private:
    std::vector<std::pair<ObjectIDNode *, std::string *> *>
        &formals_; /*!< A vector containing pairs of pointer to ObjectIDNode and
                      String.*/
};

/*! \class MethodNode
 * \brief Class representing a Method.
 *
 * This class representing a Method contains all the information necessary to
 * represent it.
 */
class MethodNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the MethodNode class.
     *
     *\param location: The location in the VSOP file of the declaration of the
     *method. \param block: Node representing the block in the Method
     *expression. \param objectID: Node representing an Object-Identifier in the
     *Method expression. \param formals: Node representing the formals in the
     *Method expression. \param type: A String reprenting the type of the
     *method.
     */
    MethodNode(YYLTYPE &location, BlockNode &block, ObjectIDNode &objectID,
               DummyNode &formals, std::string &type);

    /*!
     * \brief Destructor
     *
     * Destructor of the MethodNode class.
     */
    ~MethodNode() override;

    /*!
     * \brief Visitor pattern of MethodNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

    /*!
     * \brief Getter of the variable objectID_.
     *
     * This function is the getter of the variable objectID_.
     *
     * \return objectID_: A Node representing an Object-Identifier in the Method
     * expression. (ObjectIDNode)
     */
    ObjectIDNode &objectID(void);

    /*!
     * \brief Getter of the variable formals_.
     *
     * This function is the getter of the variable formals_.
     *
     * \return formals_: A Node representing the formals in the Method
     * expression. (DummyNode)
     */
    DummyNode &formals(void);

    /*!
     * \brief Getter of the variable type_.
     *
     * This function is the getter of the variable type_.
     *
     * \return type_: A String reprenting the type of the method.
     */
    std::string &type(void);

    /*!
     * \brief Getter of the variable block_.
     *
     * This function is the getter of the variable block_.
     *
     * \return block_: A Node representing the block in the Method expression.
     * (BlockNode)
     */
    BlockNode &block(void);

  private:
    BlockNode
        &block_; /*!< A Node representing the block in the Method expression.*/
    ObjectIDNode &objectID_; /*!< A Node representing an Object-Identifier in
                                the Method expression.*/
    DummyNode &formals_;     /*!< A Node representing the formals in the Method
                                expression.*/
    std::string &type_;      /*!< A String reprenting the type of the method.*/
};

/*! \class ClassNode
 * \brief Class representing a Class.
 *
 * This class representing a Class contains all the information necessary to
 * represent it.
 */
class ClassNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the ClassNode class.
     *
     *\param location: The location in the VSOP file of the declaration of the
     *class \param className: A String representing the name of the class \param
     *superClassName: A String representing the name of the parent class \param
     *fieldNodes: A vector of pointer to Nodes representing the fields of the
     *class. \param methodeNodes: A vector of pointer to Nodes representing the
     *methods of the class.
     *
     */
    ClassNode(YYLTYPE &location, std::string &className,
              std::string &superClassName, std::vector<FieldNode *> &fieldNodes,
              std::vector<MethodNode *> &methodeNodes);

    /*!
     * \brief Destructor
     *
     * Destructor of the ClassNode class.
     */
    ~ClassNode() override;

    /*!
     * \brief Getter of the variable marked_.
     *
     * This function is the getter of the variable marked_.
     *
     * \return marked_: A boolean.
     */
    bool marked(void);

    /*!
     * \brief Setter of the variable marked_.
     *
     * This function is the setter of the variable marked_.
     *
     * \param marked: the boolean to set to marked_. (bool).
     */
    void setMarked(bool marked);

    /*!
     * \brief Getter of the variable className_.
     *
     * This function is the getter of the variable className_.
     *
     * \return className_: A string representing the name of the class.
     */
    std::string &className(void);

    /*!
     * \brief Getter of the variable superClassName_.
     *
     * This function is the getter of the variable superClassName_.
     *
     * \return superClassName_: A string representing the name of the super
     * class.
     */
    std::string &superClassName(void);

    /*!
     * \brief Getter of the variable fieldNodes_.
     *
     * This function is the getter of the variable fieldNodes_.
     *
     * \return fieldNodes_: A vector of pointer to Nodes representing the fields
     * of the class. (vector<FieldNode*>)
     */
    std::vector<FieldNode *> &fieldNodes(void);

    /*!
     * \brief Getter of the variable methodNodes_.
     *
     * This function is the getter of the variable methodNodes_.
     *
     * \return methodNodes_: A vector of pointer to Nodes representing the
     * methods of the class. (vector<MethodNode*>)
     */
    std::vector<MethodNode *> &methodNodes(void);

    /*!
     * \brief Visitor pattern of ClassNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

  private:
    bool marked_;            /*!< A boolean.*/
    std::string &className_; /*!<A string representing the name of the class.*/
    std::string &superClassName_; /*!< A string representing the name of the
                                     super class.*/
    std::vector<FieldNode *>
        &fieldNodes_; /*!< A vector of pointer to Nodes representing the fields
                         of the class..*/
    std::vector<MethodNode *>
        &methodNodes_; /*!< A vector of pointer to Nodes representing the
                          methods of the class.*/
};

/*! \class AstNode
 * \brief Class containing all the classes of a VSOP file.
 *
 * This class representing a list of classes contains all the information
 * necessary to represent it.
 */
class AstNode : public Node
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the ClassNode class.
     *
     *\param location: The location of the declaration of the first class
     *\param classes: Vector of pointer to Nodes representing the classes in a
     *VSOP file.
     */
    AstNode(YYLTYPE &location, std::vector<ClassNode *> &classes);

    /*!
     * \brief Destructor
     *
     * Destructor of the ClassNode class.
     */
    ~AstNode() override;

    /*!
     * \brief Getter of the variable classes_.
     *
     * This function is the getter of the variable classes_.
     *
     * \return classes_: A vector of pointer to Nodes representing the classes
     * in a VSOP file. (vector<ClassNode*>)
     */
    std::vector<ClassNode *> &classes(void);

    /*!
     * \brief Getter of the variable inheritanceTree_.
     *
     * This function is the getter of the variable inheritanceTree_.
     *
     * \return inheritanceTree_: The inheritance tree of the VSOP file.
     * (InheriTree)
     */
    InheriTree &inheritanceTree(void);

    /*!
     * \brief Getter of the variable variableTableTree_.
     *
     * This function is the getter of the variable variableTableTree_.
     *
     * \return variableTableTree_: The variable table tree tree of the VSOP
     * file. (VariableTableTree)
     */
    VariableTableTree &variableTableTree(void);

    /*!
     * \brief Getter of the variable functionTableTree_.
     *
     * This function is the getter of the variable functionTableTree_.
     *
     * \return functionTableTree_: The function table tree of the VSOP file.
     * (FunctionTableTree)
     */
    FunctionTableTree &functionTableTree(void);

    /*!
     * \brief Getter of the variable classMap_.
     *
     * This function is the getter of the variable classMap_.
     *
     *\return classMap_: The mapping of class. (unordered_map<std::string,
     *ClassNode*>)
     */
    std::unordered_map<std::string, ClassNode *> &classMap(void);

    /*!
     * \brief Visitor pattern of ClassNode
     *
     * Accept the Node.
     *
     * \param visitor : A Visitor object
     */
    void accept(Visitor &visitor) override;

  private:
    std::vector<ClassNode *>
        &classes_; /*!< A vector of pointer to Nodes representing the classes in
                      a VSOP file.*/
    InheriTree &inheritanceTree_; /*!< The inheritance tree of the VSOP file.*/
    VariableTableTree &
        variableTableTree_; /*!<The variable table tree tree of the VSOP file.*/
    FunctionTableTree
        &functionTableTree_; /*!< The function table tree of the VSOP file.*/
    std::unordered_map<std::string, ClassNode *>
        &classMap_;         /*!< The mapping of class.*/
    std::string *dumpName_; /*!< Pointer to the string used to add the Object
                               class to the variable table and function table.*/
    std::vector<MethodInfo *>
        *dumpMethodInfo_; /*!< Vector of pointer to the MethodInfo objects used
                             to add the Object class to the variable table and
                             function table.*/
};

#endif
