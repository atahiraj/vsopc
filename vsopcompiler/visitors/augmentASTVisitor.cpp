/*!
 * \file augmentASTVisitor.cpp
 * \brief Source code containing the different classes allowing semantic
 * analysis through the visitor pattern. \author Tahiraj Arian \author Leroy
 * Antoine \version 0.1
 */

#include <iostream>
#include <typeinfo>
#include <visitors/augmentASTVisitor.hpp>

/*******************************************************************************
 *                           Class AugmentASTVisitor *
 *******************************************************************************/

AugmentASTVisitor::AugmentASTVisitor(const std::string &fileName)
    : fileName_(fileName)
{
}

void AugmentASTVisitor::visit(AstNode &astNode)
{
    // FIRST PASS - creating hierarchical tree, fetching methods and
    // creating tables
    InheritanceTreeVisitor inheritanceTreeVisitor =
        InheritanceTreeVisitor(this->fileName_);
    astNode.accept(inheritanceTreeVisitor);
    if (inheritanceTreeVisitor.flag())
    {
        this->flag_ = true;
        return;
    }

    // SECOND PASS - scope checking
    ScopeCheckerVisitor scopeCheckerVisitor =
        ScopeCheckerVisitor(this->fileName_);
    astNode.accept(scopeCheckerVisitor);
    if (scopeCheckerVisitor.flag())
    {
        this->flag_ = true;
        return;
    }

    // THIRD PASS - setting types
    TypeSetterVisitor typeSetterVisitor = TypeSetterVisitor(this->fileName_);
    astNode.accept(typeSetterVisitor);
    if (typeSetterVisitor.flag())
    {
        this->flag_ = true;
        return;
    }

    // FOURTH PASS - type checking
    TypeCheckerVisitor typeCheckerVisitor = TypeCheckerVisitor(this->fileName_);
    astNode.accept(typeCheckerVisitor);
    if (typeCheckerVisitor.flag())
        this->flag_ = true;
}

void AugmentASTVisitor::semError(const YYLTYPE &location,
                                 const std::string &message)
{
    std::cerr << this->fileName_ << ":" << location.first_line << ":"
              << location.first_column << ": semantic error: " << message
              << std::endl;
    this->flag_ = true;
}

bool AugmentASTVisitor::flag() { return this->flag_; }

// For convenience
void AugmentASTVisitor::visit(__attribute__((unused)) ClassNode &classNode) {}
void AugmentASTVisitor::visit(__attribute__((unused)) MethodNode &methodNode) {}
void AugmentASTVisitor::visit(__attribute__((unused)) FieldNode &fieldNode) {}
void AugmentASTVisitor::visit(__attribute__((unused)) FormalsNode &formalsNode)
{
}
void AugmentASTVisitor::visit(__attribute__((unused))
                              ObjectIDNode &objectIDNode)
{
}
void AugmentASTVisitor::visit(__attribute__((unused)) IfNode &ifNode) {}
void AugmentASTVisitor::visit(__attribute__((unused)) WhileNode &whileNode) {}
void AugmentASTVisitor::visit(__attribute__((unused)) LetNode &letNode) {}
void AugmentASTVisitor::visit(__attribute__((unused)) AssignNode &assignNode) {}
void AugmentASTVisitor::visit(__attribute__((unused))
                              BinaryOpNode &binaryOpNode)
{
}
void AugmentASTVisitor::visit(__attribute__((unused)) UnaryOpNode &unaryOpNode)
{
}
void AugmentASTVisitor::visit(__attribute__((unused)) CallNode &callNode) {}
void AugmentASTVisitor::visit(__attribute__((unused)) NewNode &newNode) {}
void AugmentASTVisitor::visit(__attribute__((unused)) LiteralNode &literalNode)
{
}
void AugmentASTVisitor::visit(__attribute__((unused)) BlockNode &blockNode) {}
void AugmentASTVisitor::visit(__attribute__((unused)) UnitNode &unitNode) {}

/*******************************************************************************
 *                    Class AugmentorAugmentASTVisitor *
 *******************************************************************************/
AugmentorVisitor::AugmentorAugmentASTVisitor(const std::string &fileName)
    : AugmentASTVisitor(fileName)
{
}

void AugmentorVisitor::visit(AstNode &astNode)
{
    // Fetching information
    this->inheritanceTree_ = &astNode.inheritanceTree();
    this->variableTableTree_ = &astNode.variableTableTree();
    this->functionTableTree_ = &astNode.functionTableTree();
    auto &classMap = astNode.classMap();

    for (auto x : this->inheritanceTree_->keys())
        if (*x != "Object")
            classMap[*x]->accept(*this);
}

void AugmentorVisitor::visit(ClassNode &classNode)
{
    this->currentClass_ = &classNode.className();
    this->functionTable_ =
        this->functionTableTree_->table(*this->currentClass_);
    this->variableTable_ =
        this->variableTableTree_->table(*this->currentClass_);
    this->field_ = true;

    // Going through fields first
    if (!classNode.fieldNodes().empty())
        for (auto x : classNode.fieldNodes())
            x->accept(*this);

    this->field_ = false;

    // Then through the methods
    if (!classNode.methodNodes().empty())
        for (auto x : classNode.methodNodes())
            x->accept(*this);
}

/*******************************************************************************
 *                   Class InheritanceTreeAugmentorVisitor *
 *******************************************************************************/
InheritanceTreeVisitor::InheritanceTreeAugmentorVisitor(
    const std::string &fileName)
    : AugmentorVisitor(fileName)
{
}

void InheritanceTreeVisitor::visit(AstNode &astNode)
{
    std::vector<ClassNode *> &classes = astNode.classes();
    this->inheritanceTree_ = &astNode.inheritanceTree();
    this->variableTableTree_ = &astNode.variableTableTree();
    this->functionTableTree_ = &astNode.functionTableTree();
    auto &classMap = astNode.classMap();

    /* STEP 1: BUILDING INHERITANCE TREE */
    bool allMarked = false;
    bool oneBeenMarked = false;

    // Adding other classes
    while (!allMarked)
    {
        oneBeenMarked = false;
        allMarked = true;

        for (auto x : classes)
        {
            // Class is not marked
            if (!x->marked())
            {
                // Class redefinition
                if (this->inheritanceTree_->contains(x->className()))
                {
                    this->semError(x->location(), "class redefinition: '" +
                                                      x->className() + "'");
                    x->setMarked(true);
                }

                // Super class is marked/in the inheritance tree
                if (this->inheritanceTree_->contains(x->superClassName()))
                {
                    this->inheritanceTree_->insert(x->className(),
                                                   x->superClassName());
                    classMap[x->className()] = x;
                    x->setMarked(true);
                    oneBeenMarked = true;
                }
            }

            allMarked = allMarked && x->marked();
        }

        // If no class has been marked -> semantic error
        if (!oneBeenMarked)
        {
            for (auto x : classes)
                if (!x->marked())
                    this->semError(x->location(), "class undefined: '" +
                                                      x->superClassName() +
                                                      "'");
            this->flag_ = true;
            break;
        }
    }

    // No Main
    std::string mainClass = std::string("Main");
    if (!this->inheritanceTree_->contains(mainClass))
        this->semError(classes[0]->location(), "class Main undefined");

    // Leaving if flag was raised
    if (this->flag_)
        return;

    /* STEP 2: FETCHING METHOD INFORMATION */
    for (auto x : this->inheritanceTree_->keys())
        if (*x != "Object")
            classMap[*x]->accept(*this);

    // Checking for main method
    std::string mainMethod = std::string("main");
    FunctionTable *mainFunctionTable =
        this->functionTableTree_->table(mainClass);

    // No main method
    if (!mainFunctionTable->contains(mainMethod))
        this->semError(classMap[mainClass]->location(),
                       "no method 'main' in class 'Main'");

    // main method is not int32
    else
    {
        MethodInfo &mainInfo = *mainFunctionTable->value(mainMethod);
        if (mainFunctionTable->value(mainMethod)->type() !=
            std::string("int32"))
        {
            std::string message =
                std::string("invalid type: method 'main': expected "
                            "type 'int32'\n\tbut found type '" +
                            mainInfo.type() + "'");
            this->semError(mainInfo.location(), message);
        }
        if (mainFunctionTable->value(mainMethod)->formals().size() > 0)
            this->semError(mainInfo.location(),
                           "Main.main() should have no arguments");
    }
}

void InheritanceTreeVisitor::visit(ClassNode &classNode)
{
    this->currentClass_ = &classNode.className();
    std::string &className = classNode.className();
    std::string &superClassName = classNode.superClassName();

    // Adding tables to the tree
    if (!this->variableTableTree_->contains(className))
    {
        this->variableTableTree_->insert(className, superClassName);
        this->functionTableTree_->insert(className, superClassName);
    }

    // Fetch the variable tree
    this->variableTable_ = this->variableTableTree_->table(className);
    this->functionTable_ = this->functionTableTree_->table(className);

    if (!classNode.methodNodes().empty())
        for (auto x : classNode.methodNodes())
            x->accept(*this);
}

void InheritanceTreeVisitor::visit(MethodNode &methodNode)
{
    std::string &methodType = methodNode.type();
    std::string &methodName = methodNode.objectID().name();

    // Creating info nodes
    this->formalTypes_ = new std::vector<std::string *>();

    // Fecthing information
    try
    {
        Node &node = dynamic_cast<Node &>(methodNode.formals());
        node.accept(*this);
    }
    catch (std::bad_cast &bc)
    {
    }

    // Checking for conflicting types
    if (this->functionTable_->value(methodName) &&
        this->functionTable_->value(methodName)->type() != methodType)
        this->semError(methodNode.location(),
                       "invalid type: method '" + methodName +
                           "': expected type '" +
                           this->functionTable_->value(methodName)->type() +
                           "'\n\tbut found type '" + methodType + "'");

    // Adding methods to table
    if (!this->functionTable_->value(methodName))
    {
        this->methodInfo_ =
            new MethodInfo(methodNode.location(), methodType, methodName,
                           *this->formalTypes_, *this->currentClass_);
        this->functionTable_->insert(methodName, *this->methodInfo_);
    }
    else if (this->functionTable_->contains(methodName))
    {
        YYLTYPE &loc = this->functionTable_->value(methodName)->location();
        std::string locString = std::string();
        locString += std::to_string(loc.first_line);
        locString += ":";
        locString += std::to_string(loc.first_column);

        this->semError(methodNode.location(),
                       "redefinition of method '" + methodName +
                           "', first defined at " + locString);

        for (auto x : *this->formalTypes_)
            delete x;
        delete this->formalTypes_;
    }
    else if (this->functionTable_->value(methodName)->type() != methodType)
    {
        this->semError(methodNode.location(),
                       "type error: method '" + methodName +
                           "': expected type '" +
                           this->functionTable_->value(methodName)->type() +
                           "'\n\tbut found type '" + methodType + "'");

        for (auto x : *this->formalTypes_)
            delete x;
        delete this->formalTypes_;
    }
    else if (this->functionTable_->value(methodName)->formals().size() !=
             formalTypes_->size())
    {
        this->semError(methodNode.location(),
                       "invalid override of method '" + methodName +
                           "': different number of parameters");

        for (auto x : *this->formalTypes_)
            delete x;
        delete this->formalTypes_;
    }
    else
    {
        std::vector<std::string *> formalTypes =
            this->functionTable_->value(methodName)->formals();
        int size = formalTypes.size();
        bool flag = false;

        for (int i = 0; i < size; ++i)
            if (*formalTypes[i] != *(*this->formalTypes_)[i])
                flag = true;

        if (flag)
        {
            this->semError(methodNode.location(),
                           "invalid override of method '" + methodName +
                               "': different parameter types");

            for (auto x : *this->formalTypes_)
                delete x;
            delete this->formalTypes_;
        }
        else
        {
            this->methodInfo_ =
                new MethodInfo(methodNode.location(), methodType, methodName,
                               *this->formalTypes_, *this->currentClass_);
            this->functionTable_->insert(methodName, *this->methodInfo_);
        }
    }
}

void InheritanceTreeVisitor::visit(FormalsNode &formalsNode)
{
    for (auto x : formalsNode.formals())
    {
        YYLTYPE &location = x->first->location();
        std::string &type = *x->second;

        this->formalTypes_->push_back(&type);

        if (type != "bool" && type != "int32" && type != "string" &&
            type != "unit" && !this->variableTableTree_->contains(type))
            this->semError(location, "unknown type identifier: '" + type + "'");
    }
}

/*******************************************************************************
 *                     Class ScopeCheckerAugmentorVisitor *
 *******************************************************************************/

ScopeCheckerVisitor::ScopeCheckerAugmentorVisitor(const std::string &fileName)
    : AugmentorVisitor(fileName)
{
}

void ScopeCheckerVisitor::visit(FieldNode &fieldNode)
{
    // Fetching some data
    YYLTYPE &location = fieldNode.location();
    std::string &name = fieldNode.objectID().name();
    std::string &type = fieldNode.type();

    // Checking assignment scopes
    try
    {
        Node &node = dynamic_cast<Node &>(fieldNode.assignExpr());
        int &scopeIndex = fieldNode.scopeIndex() = this->maxScopeIndex_++;
        this->currentScope_ =
            this->variableTableTree_->insert(scopeIndex, *this->currentClass_);
        node.accept(*this);
        this->currentScope_ = &this->currentScope_->parent();
        // Object needs an Object to be initialized
        if (type == *this->currentClass_)
            this->semError(location, "invalid initialization: using object "
                                     "instance to initialize instance");
    }
    catch (std::bad_cast &bc)
    {
    }

    // If the field's type is a typeID, check if the class exists
    if (type != "bool" && type != "int32" && type != "string" &&
        type != "unit" && !this->variableTableTree_->contains(type))
        this->semError(location, "unknown type identifier: '" + type + "'");

    // Invalid name
    if (name == "self")
        this->semError(location, "invalid field name: 'self");

    // Adding the field to the variable table
    if (this->variableTable_->value(name))
    {
        YYLTYPE &loc = this->variableTable_->value(name)->location();
        std::string locString = std::string();
        locString += std::to_string(loc.first_line);
        locString += ":";
        locString += std::to_string(loc.first_column);

        this->semError(location, "redefinition of field '" + name +
                                     "', first defined at " + locString);
    }
    else
    {
        VariableInfo &fieldInfo = *new VariableInfo(location, type);
        this->variableTable_->insert(name, fieldInfo);
    }
}

void ScopeCheckerVisitor::visit(MethodNode &methodNode)
{
    // New scope
    int &scopeIndex = methodNode.scopeIndex() = this->maxScopeIndex_++;
    this->currentScope_ =
        this->variableTableTree_->insert(scopeIndex, *this->currentClass_);

    // Adding self
    std::string &selfName = *new std::string("self");
    VariableInfo &selfInfo =
        *new VariableInfo(methodNode.location(), *this->currentClass_);
    this->currentScope_->insert(selfName, selfInfo);

    // Fetching parameters if any
    try
    {
        Node &node = dynamic_cast<Node &>(methodNode.formals());
        node.accept(*this);
    }
    catch (std::bad_cast &bc)
    {
    }

    // Jumping the block
    methodNode.block().accept(*this);

    // Leaving scope and deleting stuff
    this->currentScope_ = &this->currentScope_->parent();
}

void ScopeCheckerVisitor::visit(FormalsNode &formalsNode)
{
    for (auto x : formalsNode.formals())
    {
        YYLTYPE &location = formalsNode.location();
        std::string &name = x->first->name();
        std::string &type = *x->second;

        VariableInfo &paramInfo = *new VariableInfo(location, type);

        if (!this->currentScope_->contains(name))
            this->currentScope_->insert(name, paramInfo);
        else
            this->semError(formalsNode.location(),
                           "parameter redefinition :'" + name + "'");
    }
}

void ScopeCheckerVisitor::visit(ObjectIDNode &objectIDNode)
{
    YYLTYPE &location = objectIDNode.location();
    std::string &name = objectIDNode.name();

    if (this->field_ && name == "self")
        this->semError(location, "invalid use of 'self' during initialization");
    else if (this->field_ && this->variableTable_->value(name))
        this->semError(location, "use of unbound variable '" + name + "'");
    else if (!this->currentScope_->value(name))
        this->semError(location, "unknown object identifier: '" + name + "'");
}

void ScopeCheckerVisitor::visit(LetNode &letNode)
{
    YYLTYPE &location = letNode.location();
    std::string &name = letNode.objectID().name();
    std::string &type = letNode.type();

    try
    {
        Node &node = dynamic_cast<Node &>(letNode.assignExpr());
        node.accept(*this);
    }
    catch (std::bad_cast &bc)
    {
    }

    // If the field's type is a typeID, check if the class exists
    if (type != "bool" && type != "int32" && type != "string" &&
        type != "unit" && !this->variableTableTree_->contains(type))
        this->semError(location, "unknown type identifier: '" + type + "'");

    // Checking name
    if (name == "self")
        this->semError(location, "invalid use of 'self'");

    // Entering a new scope
    int &scopeIndex = letNode.scopeIndex() = this->maxScopeIndex_++;
    this->currentScope_ =
        this->variableTableTree_->insert(scopeIndex, *this->currentScope_);

    // Adding the field to the variable table
    VariableInfo &variableInfo = *new VariableInfo(location, type);
    this->currentScope_->insert(name, variableInfo);

    letNode.inExpr().accept(*this);

    // Leaving scope and freeing
    this->currentScope_ = &this->currentScope_->parent();
}

void ScopeCheckerVisitor::visit(CallNode &callNode)
{
    callNode.expr().accept(*this);

    if (!callNode.args().empty())
        for (auto x : callNode.args())
            x->accept(*this);
}

void ScopeCheckerVisitor::visit(NewNode &newNode)
{
    YYLTYPE &location = newNode.location();
    std::string &type = newNode.typeID();

    // Invalid object ID
    if (!this->inheritanceTree_->contains(type))
        this->semError(location, "unknown type identifier: " + type);
    else if (type == *this->currentClass_ && this->field_)
        this->semError(location, "invalid initialization: using object "
                                 "instance to initialize instance");
}

/* Obvious stuff */

void ScopeCheckerVisitor::visit(IfNode &ifNode)
{
    for (auto x : ifNode.exprs())
        x->accept(*this);
}

void ScopeCheckerVisitor::visit(WhileNode &whileNode)
{
    whileNode.condExpr().accept(*this);
    whileNode.bodyExpr().accept(*this);
}

void ScopeCheckerVisitor::visit(BinaryOpNode &binaryOpNode)
{
    binaryOpNode.leftExpr().accept(*this);
    binaryOpNode.rightExpr().accept(*this);
}

void ScopeCheckerVisitor::visit(UnaryOpNode &unaryOpNode)
{
    unaryOpNode.expr().accept(*this);
}

void ScopeCheckerVisitor::visit(BlockNode &blockNode)
{
    int &scopeIndex = blockNode.scopeIndex() = this->maxScopeIndex_++;
    this->currentScope_ =
        this->variableTableTree_->insert(scopeIndex, *this->currentScope_);

    for (auto x : blockNode.exprs())
        x->accept(*this);

    this->currentScope_ = &this->currentScope_->parent();
}

void ScopeCheckerVisitor::visit(AssignNode &assignNode)
{
    if (assignNode.objectID().name() == "self")
        this->semError(assignNode.location(), "one cannot assign to self");

    assignNode.assignExpr().accept(*this);
    assignNode.objectID().accept(*this);
}

/*******************************************************************************
 *                        Class TypeSetterAugmentorVisitor *
 *******************************************************************************/

TypeSetterVisitor::TypeSetterAugmentorVisitor(const std::string &fileName)
    : AugmentorVisitor(fileName)
{
}

void TypeSetterVisitor::visit(MethodNode &methodNode)
{
    // New scope
    this->currentScope_ =
        this->variableTableTree_->table(methodNode.scopeIndex());

    // Jumping to the block
    methodNode.block().accept(*this);

    // Leaving scope
    this->currentScope_ = &this->currentScope_->parent();
}

void TypeSetterVisitor::visit(FieldNode &fieldNode)
{
    try
    {
        Node &node = dynamic_cast<Node &>(fieldNode.assignExpr());

        this->currentScope_ =
            this->variableTableTree_->table(fieldNode.scopeIndex());

        node.accept(*this);

        this->currentScope_ = &this->currentScope_->parent();
    }
    catch (std::bad_cast &bc)
    {
    }
}

void TypeSetterVisitor::visit(ObjectIDNode &objectIDNode)
{
    std::string &type = this->currentScope_->value(objectIDNode.name())->type();
    objectIDNode.setExprType(*new std::string(type));
}

void TypeSetterVisitor::visit(IfNode &ifNode)
{
    std::vector<Node *> &exprs = ifNode.exprs();
    for (auto x : exprs)
        x->accept(*this);

    if (exprs.size() == 3)
    {
        std::string &type1 = *exprs[1]->exprType();
        std::string &type2 = *exprs[2]->exprType();

        if (type1 == type2)
            ifNode.setExprType(*new std::string(type1));

        // Class objects
        else if (this->inheritanceTree_->contains(type1) &&
                 this->inheritanceTree_->contains(type2))
            ifNode.setExprType(*new std::string(
                *this->inheritanceTree_->commonAncestor(type1, type2)));
    }

    // If types do not agree -> unit
    if (!ifNode.exprType())
        ifNode.setExprType(*new std::string("unit"));
}

void TypeSetterVisitor::visit(WhileNode &whileNode)
{
    whileNode.condExpr().accept(*this);
    whileNode.bodyExpr().accept(*this);
    whileNode.setExprType(*new std::string("unit"));
}

void TypeSetterVisitor::visit(LetNode &letNode)
{
    try
    {
        Node &node = dynamic_cast<Node &>(letNode.assignExpr());
        node.accept(*this);
    }
    catch (std::bad_cast &bc)
    {
    }

    // Entering a new scope
    this->currentScope_ = this->variableTableTree_->table(letNode.scopeIndex());

    // Body expr
    letNode.inExpr().accept(*this);

    // Leaving scope and freeing
    this->currentScope_ = &this->currentScope_->parent();

    letNode.setExprType(*new std::string(*letNode.inExpr().exprType()));
}

void TypeSetterVisitor::visit(AssignNode &assignNode)
{
    assignNode.assignExpr().accept(*this);
    assignNode.setExprType(
        *new std::string(*assignNode.assignExpr().exprType()));
}

void TypeSetterVisitor::visit(BinaryOpNode &binaryOpNode)
{
    binaryOpNode.rightExpr().accept(*this);
    binaryOpNode.leftExpr().accept(*this);

    switch (binaryOpNode.binaryType())
    {
    case BinaryOpNode::binaryType::AND:
        binaryOpNode.setExprType(*new std::string("bool"));
        break;
    case BinaryOpNode::binaryType::EQUAL:
        binaryOpNode.setExprType(*new std::string("bool"));
        break;
    case BinaryOpNode::binaryType::LOWER:
        binaryOpNode.setExprType(*new std::string("bool"));
        break;
    case BinaryOpNode::binaryType::LOWERQ:
        binaryOpNode.setExprType(*new std::string("bool"));
        break;
    case BinaryOpNode::binaryType::PLUS:
        binaryOpNode.setExprType(*new std::string("int32"));
        break;
    case BinaryOpNode::binaryType::MINUS:
        binaryOpNode.setExprType(*new std::string("int32"));
        break;
    case BinaryOpNode::binaryType::TIMES:
        binaryOpNode.setExprType(*new std::string("int32"));
        break;
    case BinaryOpNode::binaryType::DIVIDE:
        binaryOpNode.setExprType(*new std::string("int32"));
        break;
    case BinaryOpNode::binaryType::POW:
        binaryOpNode.setExprType(*new std::string("int32"));
        break;
    }
}

void TypeSetterVisitor::visit(UnaryOpNode &unaryOpNode)
{
    unaryOpNode.expr().accept(*this);

    switch (unaryOpNode.unaryType())
    {
    case UnaryOpNode::unaryType::NOT:
        unaryOpNode.setExprType(*new std::string("bool"));
        break;
    case UnaryOpNode::unaryType::MINUS:
        unaryOpNode.setExprType(*new std::string("int32"));
        break;
    case UnaryOpNode::unaryType::ISNULL:
        unaryOpNode.setExprType(*new std::string("bool"));
        break;
    }
}

void TypeSetterVisitor::visit(CallNode &callNode)
{
    callNode.expr().accept(*this);

    YYLTYPE &location = callNode.location();
    std::string &type = *callNode.expr().exprType();
    std::string &name = callNode.objectID().name();

    // using self. during initialization
    if ((*callNode.expr().exprType() == *this->currentClass_) && this->field_)
    {
        this->semError(location, "invalid use of object method during "
                                 "object initialization");
        callNode.setExprType(
            *new std::string(this->functionTable_->value(name)->type()));
    }

    // Calling method on literal
    if (!this->functionTableTree_->contains(type))
        this->semError(location, "type '" + type +
                                     "' does not have a method '" + name + "'");
    else
    {
        // Checking method scope
        FunctionTable &funTable = *this->functionTableTree_->table(type);
        if (!funTable.value(name))
            this->semError(location, "type identifier " + type +
                                         "' does not have a method '" + name +
                                         "'");
        else
            callNode.setExprType(
                *new std::string(funTable.value(name)->type()));
    }

    if (!callNode.args().empty())
        for (auto x : callNode.args())
            x->accept(*this);

    // Just to avoid segmentation fault
    if (!callNode.exprType())
        callNode.setExprType(*new std::string("unit"));
}

void TypeSetterVisitor::visit(NewNode &newNode)
{
    newNode.setExprType(*new std::string(newNode.typeID()));
}

void TypeSetterVisitor::visit(LiteralNode &literalNode)
{
    switch (literalNode.literalType())
    {
    case LiteralNode::literalType::INTEGER:
        literalNode.setExprType(*new std::string("int32"));
        break;
    case LiteralNode::literalType::STRING:
        literalNode.setExprType(*new std::string("string"));
        break;
    case LiteralNode::literalType::BOOL:
        literalNode.setExprType(*new std::string("bool"));
        break;
    }
}

void TypeSetterVisitor::visit(BlockNode &blockNode)
{
    this->currentScope_ =
        this->variableTableTree_->table(blockNode.scopeIndex());

    for (auto x : blockNode.exprs())
        x->accept(*this);

    this->currentScope_ = &this->currentScope_->parent();

    // Fetching expr type of last element
    std::string &exprType = *blockNode.exprs().back()->exprType();
    blockNode.setExprType(*new std::string(exprType));
}

void TypeSetterVisitor::visit(UnitNode &unitNode)
{
    unitNode.setExprType(*new std::string("unit"));
}

/*******************************************************************************
 *                       Class TypeCheckerAugmentorVisitor *
 *******************************************************************************/

TypeCheckerVisitor::TypeCheckerAugmentorVisitor(const std::string &fileName)
    : AugmentorVisitor(fileName)
{
}

void TypeCheckerVisitor::visit(FieldNode &fieldNode)
{
    try
    {
        Node &node = dynamic_cast<Node &>(fieldNode.assignExpr());

        std::string &type1 = fieldNode.type();
        std::string &type2 = *node.exprType();
        std::string &name = fieldNode.objectID().name();

        if (!typeChecker(type1, type2))
            this->semError(fieldNode.location(),
                           "type error: expected type '" + type1 +
                               "'\n\tbut found type '" + type2 +
                               "' for field '" + name + "'");

        node.accept(*this);
    }
    catch (std::bad_cast &bc)
    {
    }
}

void TypeCheckerVisitor::visit(MethodNode &methodNode)
{
    YYLTYPE &location = methodNode.location();
    std::string &type1 = methodNode.type();
    std::string &type2 = *methodNode.block().exprType();

    if (!typeChecker(type1, type2))
        this->semError(location, "type error: expected type '" + type1 +
                                     "'\n\tbut found type '" + type2 + "'");

    methodNode.block().accept(*this);
}

void TypeCheckerVisitor::visit(IfNode &ifNode)
{
    std::vector<Node *> &exprs = ifNode.exprs();
    YYLTYPE &location = ifNode.location();

    if (*exprs[0]->exprType() != "bool")
        this->semError(exprs[0]->location(),
                       "type error: condition expression should be of "
                       "type 'bool'\n\tbut found type '" +
                           *exprs[0]->exprType() + "'");

    if (exprs.size() > 2)
    {
        std::string &type1 = *exprs[1]->exprType();
        std::string &type2 = *exprs[2]->exprType();

        if (type1 != type2 && type1 != "unit" && type2 != "unit" &&
            *ifNode.exprType() == "unit")
            this->semError(location, "type error: types do not agree: '" +
                                         type1 + "' and '" + type2 + "'");
    }

    for (auto x : exprs)
        x->accept(*this);
}

void TypeCheckerVisitor::visit(WhileNode &whileNode)
{
    YYLTYPE &location = whileNode.condExpr().location();
    std::string &condType = *whileNode.condExpr().exprType();

    if (condType != "bool")
        this->semError(location,
                       "type error: condition expression should be of "
                       "type 'bool'\n\tbut found type '" +
                           condType + "'");

    whileNode.condExpr().accept(*this);
    whileNode.bodyExpr().accept(*this);
}

void TypeCheckerVisitor::visit(LetNode &letNode)
{
    try
    {
        Node &node = dynamic_cast<Node &>(letNode.assignExpr());

        YYLTYPE &location = letNode.location();
        std::string &type1 = letNode.type();
        std::string &type2 = *node.exprType();
        if (!typeChecker(type1, type2))
            this->semError(location, "type error: expected type '" + type1 +
                                         "'\n\tbut found type '" + type2 + "'");

        node.accept(*this);
    }
    catch (std::bad_cast &bc)
    {
    }

    letNode.inExpr().accept(*this);
}

void TypeCheckerVisitor::visit(AssignNode &assignNode)
{
    assignNode.assignExpr().accept(*this);
}

void TypeCheckerVisitor::visit(BinaryOpNode &binaryOpNode)
{
    YYLTYPE &location = binaryOpNode.location();
    YYLTYPE &location1 = binaryOpNode.leftExpr().location();
    YYLTYPE &location2 = binaryOpNode.rightExpr().location();
    std::string &type1 = *binaryOpNode.leftExpr().exprType();
    std::string &type2 = *binaryOpNode.rightExpr().exprType();

    switch (binaryOpNode.binaryType())
    {
    case BinaryOpNode::binaryType::AND:
        if (type1 != "bool")
            this->semError(location1, "type error: 'and' operands type should "
                                      "be 'bool'\n\tbut found '" +
                                          type1 + "'");
        if (type2 != "bool")
            this->semError(location2, "type error: 'and' operands type should "
                                      "be 'bool'\n\tbut found '" +
                                          type2 + "'");
        break;
    case BinaryOpNode::binaryType::EQUAL:
        if (!typeChecker(type1, type2) && !typeChecker(type2, type1))
            this->semError(location, "type error: '=' operands types should "
                                     "match\n\tbut found '" +
                                         type1 + "' and '" + type2 + "'");
        break;
    case BinaryOpNode::binaryType::LOWER:
        if (type1 != "int32")
            this->semError(location1, "type error: '<' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type1 + "'");
        if (type2 != "int32")
            this->semError(location2, "type error: '<' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type2 + "'");
        break;
    case BinaryOpNode::binaryType::LOWERQ:
        if (type1 != "int32")
            this->semError(location1, "type error: '<=' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type1 + "'");
        if (type2 != "int32")
            this->semError(location2, "type error: '<=' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type2 + "'");
        break;
    case BinaryOpNode::binaryType::PLUS:
        if (type1 != "int32")
            this->semError(location1, "type error: '+' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type1 + "'");
        if (type2 != "int32")
            this->semError(location2, "type error: '+' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type2 + "'");
        break;
    case BinaryOpNode::binaryType::MINUS:
        if (type1 != "int32")
            this->semError(location1, "type error: '-' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type1 + "'");
        if (type2 != "int32")
            this->semError(location2, "type error: '-' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type2 + "'");
        break;
    case BinaryOpNode::binaryType::TIMES:
        if (type1 != "int32")
            this->semError(location1, "type error: '*' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type1 + "'");
        if (type2 != "int32")
            this->semError(location2, "type error: '*' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type2 + "'");
        break;
    case BinaryOpNode::binaryType::DIVIDE:
        if (type1 != "int32")
            this->semError(location1, "type error: '/' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type1 + "'");
        if (type2 != "int32")
            this->semError(location2, "type error: '/' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type2 + "'");
        break;
    case BinaryOpNode::binaryType::POW:
        if (type1 != "int32")
            this->semError(location1, "type error: '^' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type1 + "'");
        if (type2 != "int32")
            this->semError(location2, "type error: '^' operands type should "
                                      "be 'int32'\n\tbut found '" +
                                          type2 + "'");
        break;
    }

    binaryOpNode.leftExpr().accept(*this);
    binaryOpNode.rightExpr().accept(*this);
}

void TypeCheckerVisitor::visit(UnaryOpNode &unaryOpNode)
{
    YYLTYPE &location = unaryOpNode.location();
    std::string &type = *unaryOpNode.expr().exprType();

    switch (unaryOpNode.unaryType())
    {
    case UnaryOpNode::unaryType::NOT:
        if (type != "bool")
            this->semError(location, "type error: 'not' operand type should "
                                     "be 'bool'\n\tbut found '" +
                                         type + "'");
        break;
    case UnaryOpNode::unaryType::MINUS:
        if (type != "int32")
            this->semError(location, "type error: '-' operand type should be "
                                     "'int32'\n\tbut found '" +
                                         type + "'");
        break;
    case UnaryOpNode::unaryType::ISNULL:
        if (!this->inheritanceTree_->contains(type))
            this->semError(location,
                           "type error: 'isnull' operand type should be a "
                           "type identifier\n\tbut found '" +
                               type + "'");
        break;
    }

    unaryOpNode.expr().accept(*this);
}

void TypeCheckerVisitor::visit(CallNode &callNode)
{
    if (!callNode.args().empty())
    {
        YYLTYPE &location = callNode.location();
        std::string &type = *callNode.expr().exprType();
        std::string &methodName = callNode.objectID().name();
        std::vector<std::string *> argsTypes = std::vector<std::string *>();
        std::vector<std::string *> parametersTypes;

        // Fetching parameter types
        FunctionTable &funTable = *this->functionTableTree_->table(type);
        parametersTypes = funTable.value(methodName)->formals();

        // Fetching argument types
        for (auto x : callNode.args())
            argsTypes.push_back(x->exprType());

        // Invalid number of arguments
        if (argsTypes.size() != parametersTypes.size())
        {
            std::string message =
                std::string("invalid number of arguments: expected ");
            message += parametersTypes.size();
            message += "\n\tbut found ";
            message += argsTypes.size();
            this->semError(location, message);
        }
        else
        {
            bool flag = false;
            int size = argsTypes.size();

            // types do not correspond
            for (int i = 0; i < size; ++i)
                if (!typeChecker(*parametersTypes[i], *argsTypes[i]))
                {
                    flag = true;
                    break;
                }

            if (flag)
            {
                std::string message =
                    std::string("type error: method '" + methodName +
                                "' call arguments' types do not match "
                                "parameters' types: expected");
                for (auto x : parametersTypes)
                {
                    message += "'" + *x + "'";
                    if (x != parametersTypes.back())
                        message += ", ";
                }
                message += " but found\n\t";

                for (auto x : argsTypes)
                {
                    message += "'" + *x + "'";
                    if (x != argsTypes.back())
                        message += ", ";
                }

                this->semError(location, message);
            }
        }
    }

    callNode.expr().accept(*this);

    if (!callNode.args().empty())
        for (auto x : callNode.args())
            x->accept(*this);
}

void TypeCheckerVisitor::visit(BlockNode &blockNode)
{
    for (auto x : blockNode.exprs())
        x->accept(*this);
}

bool TypeCheckerVisitor::typeChecker(std::string &left, std::string &right)
{
    if (!this->inheritanceTree_->contains(left) ||
        !this->inheritanceTree_->contains(right))
        return (left == right);

    return *this->inheritanceTree_->commonAncestor((left), (right)) == (left);
}
