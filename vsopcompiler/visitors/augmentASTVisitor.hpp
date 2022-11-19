#ifndef AUGMENT_AST_VISITOR_H
#define AUGMENT_AST_VISITOR_H

/*!
 * \file augmentASTVisitor.hpp
 * \brief Header containing the different classes allowing semantic analysis
 * through the visitor pattern. \author Tahiraj Arian \author Leroy Antoine
 * \version 0.1
 */

#include <astTree/nodes.hpp>
#include <parser/parser.hpp>
#include <string>
#include <vector>
#include <visitors/visitor.hpp>

/*! \class AugmentASTVisitor
 * \brief Main class for semantic analysis.
 *
 * This class augments an AST by calling multiple other visitors that inherit
 * from this class.
 */
class AugmentASTVisitor : public Visitor
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the AugmentASTVisitor class.
     *
     * \param fileName : Name of the vsop file.
     */
    AugmentASTVisitor(const std::string &fileName);

    /*!
     * \brief Destructor
     *
     * Destructor of the AugmentASTVisitor class.
     */
    virtual ~AugmentASTVisitor(void) = default;

    /*!
     * \brief Visitor pattern of an AstNode
     *
     * Visit an AstNode and create the hierarchical tree, the different
     * tables and perform scope checking and type checking.
     *
     * \param astNode : An AstNode object
     */
    virtual void visit(AstNode &astNode) override;

    /*!
     * \brief Visitor pattern of an ClassNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param classNode : An ClassNode object (unused).
     */
    virtual void visit(__attribute__((unused)) ClassNode &classNode) override;
    /*!
     * \brief Visitor pattern of an MethodNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param methodNode : An MethodNode object (unused).
     */
    virtual void visit(__attribute__((unused)) MethodNode &methodNode) override;
    /*!
     * \brief Visitor pattern of an FieldNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param fieldNode : An FieldNode object (unused).
     */
    virtual void visit(__attribute__((unused)) FieldNode &fieldNode) override;
    /*!
     * \brief Visitor pattern of an FormalsNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param formalsNode : An FormalsNode object (unused).
     */
    virtual void visit(__attribute__((unused))
                       FormalsNode &formalsNode) override;
    /*!
     * \brief Visitor pattern of an ObjectIDNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param objectIDNode : An ObjectIDNode object (unused).
     */
    virtual void visit(__attribute__((unused))
                       ObjectIDNode &objectIDNode) override;
    /*!
     * \brief Visitor pattern of an IfNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param ifNode : An IfNode object (unused).
     */
    virtual void visit(__attribute__((unused)) IfNode &ifNode) override;
    /*!
     * \brief Visitor pattern of an WhileNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param whileNode : An WhileNode object (unused).
     */
    virtual void visit(__attribute__((unused)) WhileNode &whileNode) override;
    /*!
     * \brief Visitor pattern of an LetNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param letNode : An LetNode object (unused).
     */
    virtual void visit(__attribute__((unused)) LetNode &letNode) override;
    /*!
     * \brief Visitor pattern of an AssignNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param assignNode : An AssignNode object (unused).
     */
    virtual void visit(__attribute__((unused)) AssignNode &assignNode) override;
    /*!
     * \brief Visitor pattern of an BinaryOpNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param binaryOpNode : An BinaryOpNode object (unused).
     */
    virtual void visit(__attribute__((unused))
                       BinaryOpNode &binaryOpNode) override;
    /*!
     * \brief Visitor pattern of an UnaryOpNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param unaryOpNode : An UnaryOpNode object (unused).
     */
    virtual void visit(__attribute__((unused))
                       UnaryOpNode &unaryOpNode) override;
    /*!
     * \brief Visitor pattern of an CallNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param callNode : An CallNode object (unused).
     */
    virtual void visit(__attribute__((unused)) CallNode &callNode) override;
    /*!
     * \brief Visitor pattern of an NewNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param newNode : An NewNode object (unused).
     */
    virtual void visit(__attribute__((unused)) NewNode &newNode) override;
    /*!
     * \brief Visitor pattern of an LiteralNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param literalNode : An LiteralNode object (unused).
     */
    virtual void visit(__attribute__((unused))
                       LiteralNode &literalNode) override;
    /*!
     * \brief Visitor pattern of an BlockNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param blockNode : An BlockNode object (unused).
     */
    virtual void visit(__attribute__((unused)) BlockNode &blockNode) override;
    /*!
     * \brief Visitor pattern of an UnitNode
     *
     * This method does not do anything, it is implemented for convenience
     * so that all the child classes do not have to override it from
     * Visitor.
     *
     * \param unitNode : An UnitNode object (unused).
     */
    virtual void visit(__attribute__((unused)) UnitNode &unitNode) override;

    /*!
     * \brief Displays a semantic error found in the vsop file.
     *
     * This function allows semantic errors to be printed on the console.
     *
     * \param location : The location of the error in the vsop file.
     * \param message : The message containing the error to be displayed on
     * the console.
     */
    void semError(const YYLTYPE &location, const std::string &message);

    /*!
     * \brief Getter of the variable flag.
     *
     * This function is the getter of the variable flag.
     *
     * \return flag_: Variable allowing to know if an error has occurred.
     */
    bool flag(void);

  protected:
    bool flag_ =
        false; /*!< Variable allowing to know if an error has occurred. */
    const std::string &fileName_; /*!< The name of the inputfile. */
};

/*! \class AugmentorAugmentASTVisitor
 * \brief A class implementing comment methods for the augmentors.
 * \typedef AugmentorVisitor
 *
 * This class implements the common methods of most of the visitors used in the
 * augmentation of the AST.
 */
typedef class AugmentorAugmentASTVisitor : public AugmentASTVisitor
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the AugmentorAugmentASTVisitor class.
     *
     * \param fileName : Name of the vsop file.
     */
    AugmentorAugmentASTVisitor(const std::string &fileName);

    /*!
     * \brief Destructor
     *
     * Destructor of the AugmentorAugmentASTVisitor class.
     */
    virtual ~AugmentorAugmentASTVisitor(void) override = default;

    /*!
     * \brief Visitor pattern of an AstNode
     *
     * Visit an AstNode and fetch the different information.
     *
     * \param astNode : An AstNode object
     */
    virtual void visit(AstNode &astNode) override;

    /*!
     * \brief Visitor pattern of an ClassNode
     *
     * Visit an ClassNode and fetch the different information and then visit
     * the different fields and methods that the classes contain.
     *
     * \param classNode : An ClassNode object
     */
    virtual void visit(ClassNode &classNode) override;

  protected:
    bool field_ = true; /*!< Variable allowing to know if visiting the
                               various field is done */
    InheriTree *inheritanceTree_ = nullptr; /*!< Inheritance tree of the AST. */
    VariableTableTree *variableTableTree_ =
        nullptr; /*!< Variable table tree of the AST. */
    FunctionTableTree *functionTableTree_ =
        nullptr; /*!< Function table tree of the AST. */
    VariableTable *variableTable_ =
        nullptr; /*!< Variable table of the current class being visited. */
    FunctionTable *functionTable_ =
        nullptr; /*!< Function table of the current class being visited. */
    VariableTable *currentScope_ =
        nullptr; /*!< Variable table of the current scope the visitor is in.
                  */
    std::string *currentClass_ =
        nullptr; /*!< Name of the current class being visited. */

} AugmentorVisitor;

/*! \class InheritanceTreeAugmentorVisitor
 * \brief Class creating the inheritance tree and the function table tree.
 * \typedef InheritanceTreeVisitor
 *
 * This class visits the AST and creates the inheritance tree as well as the
 * tables of its function table tree.
 */
typedef class InheritanceTreeAugmentorVisitor : public AugmentorVisitor
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the AugmentorAugmentASTVisitor class.
     *
     * \param fileName : Name of the vsop file.
     */
    InheritanceTreeAugmentorVisitor(const std::string &fileName);

    /*!
     * \brief Destructor
     *
     * Destructor of the AugmentorAugmentASTVisitor class.
     */
    ~InheritanceTreeAugmentorVisitor(void) override = default;

    /*!
     * \brief Visitor pattern of an AstNode.
     *
     * Visit an AstNode and build the inheritance tree.
     *
     * \param astNode : An AstNode object.
     */
    void visit(AstNode &astNode) override;

    /*!
     * \brief Visitor pattern of an ClassNode.
     *
     * Visit an ClassNode in order to access its methods.
     *
     * \param classNode : An ClassNode object
     */
    void visit(ClassNode &classNode) override;

    /*!
     * \brief Visitor pattern of an MethodNode.
     *
     * Visit an MethodNode and creates the method's information.
     *
     * \param methodNode : An MethodNode object.
     */
    void visit(MethodNode &methodNode) override;
    /*!
     * \brief Visitor pattern of an FormalsNode.
     *
     * Visits a node containing the formals of a method.
     *
     * \param formalsNode : An FormalsNode object.
     */
    void visit(FormalsNode &formalsNode) override;

  private:
    MethodInfo *methodInfo_; /*!< Pointer to a MethodInfo object, for
                                    convenience only. */
    std::string
        *currentClass_; /*!< The name of the current class being visited. */
    std::vector<std::string *>
        *formalTypes_; /*!< Vector containing the types of the formals. */

} InheritanceTreeVisitor;

/*! \class ScopeCheckerAugmentorVisitor
 * \brief Class allowing mainly scope checking.
 * \typedef ScopeCheckerVisitor
 *
 * This class visits the whole syntax tree and checks whether the variables
 * have a correct scoping. It also checks whether the typeinfo are present in
 * the input vsop file.
 */
typedef class ScopeCheckerAugmentorVisitor : public AugmentorVisitor
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the ScopeCheckerAugmentorVisitor class.
     *
     * \param fileName : Name of the vsop file.
     */
    ScopeCheckerAugmentorVisitor(const std::string &fileName);

    /*!
     * \brief Destructor
     *
     * Destructor of the ScopeCheckerAugmentorVisitor class.
     */
    ~ScopeCheckerAugmentorVisitor(void) override = default;

    /*!
     * \brief Visitor pattern of an MethodNode
     *
     * Visits a MethodNode to check the scoping of its variables.
     *
     * \param methodNode : An MethodNode object
     */
    void visit(MethodNode &methodNode) override;

    /*!
     * \brief Visitor pattern of an FieldNode
     *
     * Visits a FieldNode to check the scoping of its variables.
     *
     * \param fieldNode : An FieldNode object
     */
    void visit(FieldNode &fieldNode) override;

    /*!
     * \brief Visitor pattern of an FormalsNode
     *
     * Visits a FormalsNode to add them to the variable table.
     *
     * \param formalsNode : An FormalsNode object
     */
    void visit(FormalsNode &formalsNode) override;

    /*!
     * \brief Visitor pattern of an ObjectIDNode
     *
     * Visits a ObjectIDNode to check whether it's present in the current
     * scope.
     *
     * \param objectIDNode : An ObjectIDNode object
     */
    void visit(ObjectIDNode &objectIDNode) override;

    /*!
     * \brief Visitor pattern of an IfNode
     *
     * Visits a IfNode.
     *
     * \param ifNode : An IfNode object
     */
    void visit(IfNode &ifNode) override;

    /*!
     * \brief Visitor pattern of an WhileNode
     *
     * Visits a WhileNode.
     *
     * \param whileNode : An WhileNode object
     */
    void visit(WhileNode &whileNode) override;

    /*!
     * \brief Visitor pattern of an LetNode
     *
     * Visits a LetNode.
     *
     * \param letNode : An LetNode object
     */
    void visit(LetNode &letNode) override;

    /*!
     * \brief Visitor pattern of an AssignNode
     *
     * Visits a AssignNode.
     *
     * \param assignNode : An AssignNode object
     */
    void visit(AssignNode &assignNode) override;

    /*!
     * \brief Visitor pattern of an BinaryOpNode
     *
     * Visits a BinaryOpNode.
     *
     * \param binaryOpNode : An BinaryOpNode object
     */
    void visit(BinaryOpNode &binaryOpNode) override;

    /*!
     * \brief Visitor pattern of an UnaryOpNode
     *
     * Visits a UnaryOpNode.
     *
     * \param unaryOpNode : An UnaryOpNode object
     */
    void visit(UnaryOpNode &unaryOpNode) override;

    /*!
     * \brief Visitor pattern of an CallNode
     *
     * Visits a CallNode.
     *
     * \param callNode : An CallNode object
     */
    void visit(CallNode &callNode) override;

    /*!
     * \brief Visitor pattern of an NewNode
     *
     * Visits a NewNode.
     *
     * \param newNode : An NewNode object
     */
    void visit(NewNode &newNode) override;

    /*!
     * \brief Visitor pattern of an BlockNode
     *
     * Visits a BlockNode.
     *
     * \param blockNode : An BlockNode object
     */
    void visit(BlockNode &blockNode) override;
    using AugmentorVisitor::visit;

  private:
    int maxScopeIndex_ = 0; /*!< index of the max scope */
} ScopeCheckerVisitor;

/*! \class TypeSetterAugmentorVisitor
 * \brief This class sets the expression type of the different expression nodes.
 * \typedef TypeSetterVisitor
 *
 * This class sets the expression type of the different expression nodes using
 * the VSOP typing rules.
 */
typedef class TypeSetterAugmentorVisitor : public AugmentorVisitor
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the TypeSetterAugmentorVisitor class.
     *
     * \param fileName : Name of the vsop file.
     */
    TypeSetterAugmentorVisitor(const std::string &fileName);

    /*!
     * \brief Destructor
     *
     * Destructor of the TypeSetterAugmentorVisitor class.
     */
    ~TypeSetterAugmentorVisitor(void) override = default;

    /*!
     * \brief Visitor pattern of an MethodNode
     *
     * Visits a MethodNode.
     *
     * \param methodNode : An MethodNode object
     */
    void visit(MethodNode &methodNode) override;

    /*!
     * \brief Visitor pattern of an FieldNode
     *
     * Visits a FieldNode.
     *
     * \param fieldNode : An FieldNode object
     */
    void visit(FieldNode &fieldNode) override;

    /*!
     * \brief Visitor pattern of an ObjectIDNode
     *
     * Visits a ObjectIDNode and sets its expression type.
     *
     * \param objectIDNode : An ObjectIDNode object
     */
    void visit(ObjectIDNode &objectIDNode) override;

    /*!
     * \brief Visitor pattern of an IfNode
     *
     * Visits a IfNode and sets its expression type.
     *
     * \param ifNode : An IfNode object
     */
    void visit(IfNode &ifNode) override;

    /*!
     * \brief Visitor pattern of an WhileNode
     *
     * Visits a WhileNode and sets its expression type (to unit).
     *
     * \param whileNode : An WhileNode object
     */
    void visit(WhileNode &whileNode) override;

    /*!
     * \brief Visitor pattern of an LetNode
     *
     * Visits a letNode and sets its expression type.
     *
     * \param letNode : An LetNode object
     */
    void visit(LetNode &letNode) override;

    /*!
     * \brief Visitor pattern of an AssignNode
     *
     * Visits a AssignNode and sets its expression type.
     *
     * \param assignNode : An AssignNode object
     */
    void visit(AssignNode &assignNode) override;

    /*!
     * \brief Visitor pattern of an BinaryOpNode
     *
     * Visits a BinaryOpNode and sets its expression type.
     *
     * \param binaryOpNode : An BinaryOpNode object
     */
    void visit(BinaryOpNode &binaryOpNode) override;

    /*!
     * \brief Visitor pattern of an UnaryOpNode
     *
     * Visits a UnaryOpNode and sets its expression type.
     *
     * \param unaryOpNode : An UnaryOpNode object
     */
    void visit(UnaryOpNode &unaryOpNode) override;

    /*!
     * \brief Visitor pattern of an CallNode
     *
     * Visits a CallNode and sets its expression type. Also checks whether
     * caller's class contains the called method.
     *
     * \param callNode : An CallNode object
     */
    void visit(CallNode &callNode) override;

    /*!
     * \brief Visitor pattern of an NewNode
     *
     * Visits a NewNode and sets its expression type.
     *
     * \param newNode : An NewNode object
     */
    void visit(NewNode &newNode) override;

    /*!
     * \brief Visitor pattern of an LiteralNode
     *
     * Visits a LiteralNode and sets its expression type.
     *
     * \param literalNode : An LiteralNode object
     */
    void visit(LiteralNode &literalNode) override;

    /*!
     * \brief Visitor pattern of an BlockNode
     *
     * Visits a BlockNode and sets its expression type.
     *
     * \param blockNode : An BlockNode object
     */
    void visit(BlockNode &blockNode) override;

    /*!
     * \brief Visitor pattern of an UnitNode
     *
     * Visits a UnitNode and sets its expression type (to unit).
     *
     * \param unitNode : An UnitNode object
     */
    void visit(UnitNode &unitNode) override;
    using AugmentorVisitor::visit;

  private:
} TypeSetterVisitor;

/*! \class TypeCheckerAugmentorVisitor
 * \brief This class performs the type checking of the expression nodes.
 * \typedef TypeCheckerVisitor
 *
 * This class performs the type checking of the expression nodes according to
 * the VSOP typing rules.
 */
typedef class TypeCheckerAugmentorVisitor : public AugmentorVisitor
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the TypeCheckerAugmentorVisitor class.
     *
     * \param fileName : Name of the vsop file.
     */
    TypeCheckerAugmentorVisitor(const std::string &fileName);

    /*!
     * \brief Destructor
     *
     * Destructor of the TypeCheckerAugmentorVisitor class.
     */
    ~TypeCheckerAugmentorVisitor(void) override = default;

    /*!
     * \brief Visitor pattern of an MethodNode
     *
     * Visits a MethodNode.
     *
     * \param methodNode : An MethodNode object
     */
    void visit(MethodNode &methodNode) override;

    /*!
     * \brief Visitor pattern of an FieldNode
     *
     * Visits a FieldNode.
     *
     * \param fieldNode : An FieldNode object
     */
    void visit(FieldNode &fieldNode) override;

    /*!
     * \brief Visitor pattern of an IfNode
     *
     * Visits a IfNode.
     *
     * \param ifNode : An IfNode object
     */
    void visit(IfNode &ifNode) override;

    /*!
     * \brief Visitor pattern of an WhileNode
     *
     * Visits a WhileNode.
     *
     * \param whileNode : An WhileNode object
     */
    void visit(WhileNode &whileNode) override;

    /*!
     * \brief Visitor pattern of an LetNode
     *
     * Visits a LetNode and checks whether the node's types are valid.
     *
     * \param letNode : An LetNode object
     */
    void visit(LetNode &letNode) override;

    /*!
     * \brief Visitor pattern of an AssignNode
     *
     * Visits a AssignNode.
     *
     * \param assignNode : An AssignNode object
     */
    void visit(AssignNode &assignNode) override;

    /*!
     * \brief Visitor pattern of an BinaryOpNode
     *
     * Visits a BinaryOpNode and checks whether the operand types are valid.
     *
     * \param binaryOpNode : An BinaryOpNode object
     */
    void visit(BinaryOpNode &binaryOpNode) override;

    /*!
     * \brief Visitor pattern of an UnaryOpNode
     *
     * Visits a UnaryOpNode and checks whether the operand's type is valid.
     *
     * \param unaryOpNode : An UnaryOpNode object
     */
    void visit(UnaryOpNode &unaryOpNode) override;

    /*!
     * \brief Visitor pattern of an CallNode
     *
     * Visits a CallNode checks and checks whether the arguments' types are
     * the same as the formals'.
     *
     * \param callNode : An CallNode object
     */
    void visit(CallNode &callNode) override;

    /*!
     * \brief Visitor pattern of an BlockNode
     *
     * Visits a BlockNode.
     *
     * \param blockNode : An BlockNode object
     */
    void visit(BlockNode &blockNode) override;
    using AugmentorVisitor::visit;

  private:
    /*!
     * \brief Method to verify the type of two VSOP variables.
     *
     * This function checks whether the left and right variable types are
     * of the same type, that is whether the types are the same or if the
     * right typeid inherits from the left typeid.
     *
     * \param left : The type of the left variable.
     * \param right : The type of the right variable.
     *
     * \return True if left and right typeids are the same or if the if
     * the right typeid inherits from the left typeid.
     */
    bool typeChecker(std::string &left, std::string &right);

} TypeCheckerVisitor;

#endif
