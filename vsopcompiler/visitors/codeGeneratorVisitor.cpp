/*!
 * \file codeGeneratorVisitor.cpp
 * \brief Source code containing the different classes allowing code generation
 * through the visitor pattern and llvm. \author Tahiraj Arian \author Leroy
 * Antoine \version 0.1
 */

#include <visitors/objectll.h>

#include <astTree/nodes.hpp>
#include <cstddef>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <visitors/codeGeneratorVisitor.hpp>

CodeGeneratorVisitor::CodeGeneratorVisitor()
{
    this->labelNb_ = 0;
    this->ssaNb_ = 0;
    this->strNb_ = 0;
    this->code_ = std::string("");
    this->ss_ = std::stringstream();
    this->fMap_ = std::unordered_map<std::string, unsigned>();
    this->mMap_ = std::unordered_map<std::string, unsigned>();
    this->sMap_ = std::unordered_map<std::string, unsigned>();
    this->iTree_ = nullptr;
    this->fTree_ = nullptr;
    this->vTree_ = nullptr;
    this->cScope_ = nullptr;
}

void CodeGeneratorVisitor::visit(AstNode &astNode)
{
    // Adding object.ll
    this->code_ += std::string(reinterpret_cast<const char *>(object_ll));

    // Fetching trees and stuff
    this->iTree_ = &astNode.inheritanceTree();
    this->vTree_ = &astNode.variableTableTree();
    this->fTree_ = &astNode.functionTableTree();

    // Adding type aliases
    this->ss_ << "\n\n; Type aliases \n";
    this->ss_ << "%int32 = type i32\n";
    this->ss_ << "%bool = type i1\n";
    this->ss_ << "%unit = type i1\n";
    this->ss_ << "%string = type i8*\n\n";

    // Adding empty string
    this->ss_ << "@str" << ++this->strNb_ << " = constant [1 x i8] c\"\\00\"\n";
    this->sMap_[std::string("")] = 1;

    this->code_ += this->ss_.str();
    this->ss_.clear();
    this->ss_.str(std::string());

    /*
        Function/variable tree and inheritance tree are enough to generate code
        for classes data structures. Other nodes will however have to be visited
        for method bodies and class constructors.
        */
    // Looping on classes
    auto &keys = this->iTree_->keys();
    for (const auto &cNameptr : keys)
    {
        std::string className = *cNameptr;
        if (*cNameptr == "Object")
            continue;
        // Collecting fields
        auto &vTable = *this->vTree_->table(className);
        auto fieldNames = std::vector<std::string *>();
        auto fieldTypes = std::vector<std::string>();
        vTable.allKeys(fieldNames);
        for (const auto &fnameptr : fieldNames)
            fieldTypes.push_back(vTable.value(*fnameptr)->type());
        // Writing object type struct
        this->ss_ << "\n%struct." << className << " = type {\n";
        this->ss_ << "\t%struct." << className << "VTable*";
        this->fMap_[className + "_vtable"] = 0;
        if (!fieldTypes.empty())
        {
            this->ss_ << ",\n";
            for (auto it = fieldTypes.begin(); it != fieldTypes.end() - 1; ++it)
                this->ss_ << "\t" << this->convertType(*it) << ",\n";
            this->ss_ << "\t" << this->convertType(fieldTypes.back()) << "\n";

            size_t size = fieldTypes.size();
            for (size_t i = 0; i < size; i++)
                this->fMap_[className + "_" + *fieldNames[i]] = i + 1;
        }
        else
            this->ss_ << "\n";
        this->ss_ << "}\n\n";

        // Methods
        auto &fTable = *this->fTree_->table(className);
        auto vTableStruct = std::string("");
        auto vTableConst = std::string("");
        auto allMethodNames = std::vector<std::string *>();
        auto methodNames = std::vector<std::string>();
        auto objectNames = std::vector<std::string>();
        auto methodSet = std::unordered_set<std::string>();
        fTable.allKeys(allMethodNames); // There might be duplicates
        for (auto it = allMethodNames.begin(); it != allMethodNames.end(); ++it)
            if (methodSet.find(**it) == methodSet.end())
            {
                methodSet.insert(**it);
                methodNames.push_back(**it);
                objectNames.push_back(fTable.value(**it)->classKey());
            }

        // Building method body and co
        size_t size = methodNames.size();
        for (size_t i = 0; i < size; ++i)
        {
            MethodInfo &methodInfo = *fTable.value(methodNames[i]);
            std::string type = methodInfo.type();
            std::vector<std::string *> &formals = methodInfo.formals();
            type = this->convertType(type);
            vTableStruct += "\t" + type + " (";
            vTableConst += "\t" + type + " (";
            vTableStruct += this->convertType(objectNames[i]) + ",";
            vTableConst += this->convertType(objectNames[i]) + ",";

            for (const auto &formalptr : formals)
            {
                std::string formal = *formalptr;
                formal = this->convertType(formal) + ",";
                vTableStruct += formal;
                vTableConst += formal;
            }
            // Removing comma
            vTableStruct.pop_back();
            vTableConst.pop_back();
            vTableStruct += ")*,\n";
            vTableConst +=
                ")* @" + objectNames[i] + "_" + methodNames[i] + ",\n";

            this->mMap_[objectNames[i] + "_" + methodNames[i]] = i;
        }
        vTableStruct = vTableStruct.substr(0, vTableStruct.size() - 2) + "\n";
        vTableConst = vTableConst.substr(0, vTableConst.size() - 2) + "\n";

        // Vtable struct
        this->ss_ << "\n%struct." << className << "VTable = type {\n";
        this->ss_ << vTableStruct << "}\n\n";

        // Const Vtable
        this->ss_ << "@" << className << "_vtable = constant %struct."
                  << className << "VTable {\n";
        this->ss_ << vTableConst << "}\n\n";
    }

    /*
        At this point, the Object structures and their corresponding Vtables are
        defined
        */
    for (const auto &classptr : astNode.classes())
        classptr->accept(*this);

    // Adding entry point
    this->ss_ << "define %int32 @main() {\n";
    this->ss_ << "\t%1 = call %struct.Main* @Main__new()\n";
    this->ss_ << "\t%2 = call %int32 @Main_main(%struct.Main* %1)\n";
    this->ss_ << "\tret %int32 %2\n";
    this->ss_ << "}\n\n";

    this->code_ += this->ss_.str();
    this->ss_.clear();
    this->ss_.str(std::string());
}

void CodeGeneratorVisitor::visit(ClassNode &classNode)
{
    // New and init functions must be built here
    this->cClass_ = classNode.className();
    this->cScope_ = this->vTree_->table(this->cClass_);
    const auto &classType = this->convertType(this->cClass_);
    const auto &superClassName = classNode.superClassName();
    const auto &superClassType = this->convertType(superClassName);

    // init
    this->ssaNb_ = 1;
    this->ss_ << "define " << classType << " @" << this->cClass_ << "__init("
              << classType << ") {\n";
    this->bitcastGen(++this->ssaNb_, classType, 0, superClassType);
    this->callGen(++this->ssaNb_, superClassType,
                  std::string("@" + superClassName + "__init"),
                  std::vector<std::string>{superClassType + " " +
                                           this->registerToLlvm(2)});

    // Visiting fields
    for (const auto &fieldNodeptr : classNode.fieldNodes())
        fieldNodeptr->accept(*this);

    // Ret
    this->retGen(classType, 0);
    this->ss_ << "}\n\n";

    // New
    this->ssaNb_ = 0;
    this->ss_ << "define " << classType << " @" << this->cClass_
              << "__new() {\n";
    this->ss_ << "\t%" << ++this->ssaNb_ << " = getelementptr "
              << classType.substr(0, classType.size() - 1) << ", " << classType
              << " null, i32 1\n";

    this->ssaNb_++;
    this->ss_ << "\t" << this->registerToLlvm(this->ssaNb_) << " = ptrtoint "
              << classType << this->registerToLlvm(this->ssaNb_ - 1)
              << " to i64\n"; // Hardcoded cause only 1 use
    this->ssaNb_++;
    this->callGen(this->ssaNb_, std::string("i8*"), std::string("@malloc"),
                  std::vector<std::string>{
                      "i64 " + this->registerToLlvm(this->ssaNb_ - 1)});
    this->ssaNb_++;
    this->bitcastGen(this->ssaNb_, std::string("i8*"), this->ssaNb_ - 1,
                     classType);

    // Calling init
    this->ssaNb_++;
    this->callGen(
        this->ssaNb_, classType, "@" + this->cClass_ + "__init",
        std::vector<std::string>(
            {classType + " " + this->registerToLlvm(this->ssaNb_ - 1)}));

    // Setting Vtable
    this->ssaNb_++;
    this->getEleGen(this->ssaNb_, classType,
                    this->registerToLlvm(this->ssaNb_ - 1),
                    this->fMap_[this->cClass_ + "_vtable"]);
    this->storeGen("%struct." + this->cClass_ + "VTable*",
                   "@" + this->cClass_ + "_vtable",
                   this->registerToLlvm(this->ssaNb_));
    this->retGen(classType, this->ssaNb_ - 1);
    this->ss_ << "}\n\n";

    // Going through methdods
    for (const auto &methodNodeptr : classNode.methodNodes())
        methodNodeptr->accept(*this);
}

void CodeGeneratorVisitor::visit(FieldNode &fieldNode)
{
    // Class constructor body is build here
    const auto &objectName = fieldNode.objectID().name();
    const auto &objectLlvmType = this->convertType(fieldNode.type());
    const auto &classType = this->convertType(this->cClass_);
    try
    {
        // Visit expr node
        Node &node = dynamic_cast<Node &>(fieldNode.assignExpr());
        this->cScope_ = this->vTree_->table(fieldNode.scopeIndex());
        node.accept(*this);
        this->cScope_ = &this->cScope_->parent();

        const auto &assignLlvmType = this->convertType(*node.exprType());

        getEleGen(++this->ssaNb_, classType, this->registerToLlvm(0),
                  this->fMap_[this->cClass_ + "_" + objectName]);

        if ((objectLlvmType != assignLlvmType)) // We have to bitcast
        {
            this->ssaNb_++;
            this->bitcastGen(this->ssaNb_, assignLlvmType, this->ssaNb_ - 2,
                             objectLlvmType);
            this->storeGen(objectLlvmType, this->registerToLlvm(this->ssaNb_),
                           this->registerToLlvm(this->ssaNb_ - 1));
        }
        else
            this->storeGen(objectLlvmType,
                           this->registerToLlvm(this->ssaNb_ - 1),
                           this->registerToLlvm(this->ssaNb_));
    }
    catch (std::bad_cast &bc) // Default this->init
    {
        getEleGen(++this->ssaNb_, classType, this->registerToLlvm(0),
                  this->fMap_[this->cClass_ + "_" + objectName]);

        const unsigned ssa = this->ssaNb_;
        this->init(objectLlvmType);
        storeGen(objectLlvmType, this->registerToLlvm(this->ssaNb_),
                 this->registerToLlvm(ssa));
    }
}

void CodeGeneratorVisitor::visit(MethodNode &methodNode)
{
    this->cScope_ = this->vTree_->table(methodNode.scopeIndex());

    const auto &methodName = methodNode.objectID().name();
    const auto &methodType = this->convertType(methodNode.type());

    // Fetching formals - we won't visit the node itself
    auto formals = std::vector<std::pair<ObjectIDNode *, std::string *> *>();
    try
    {
        DummyNode &dummyNode = methodNode.formals();
        FormalsNode &formalsNode = dynamic_cast<FormalsNode &>(dummyNode);
        formals = formalsNode.formals();
    }
    catch (std::bad_cast &bc)
    {
    }

    this->ss_ << "define " << methodType << " @" << this->cClass_ << "_"
              << methodName << "(%struct." << this->cClass_ << "*";

    // Adding parameters
    for (const auto &formalptr : formals)
    {
        const auto &ftype = this->convertType(*formalptr->second);
        this->ss_ << ", " << ftype;
    }
    this->ss_ << ") {\n";

    // Adding parameters on the stack - clang style
    std::vector<std::string *> allKeys;
    this->cScope_->allKeys(allKeys);
    for (const auto &key : allKeys)
        this->cScope_->value(*key)->ssaptr() = 0;

    size_t formalsSize = formals.size();
    this->ssaNb_ = formalsSize + 1;

    // Allocating self
    const auto &classType = this->convertType(this->cClass_);
    this->allocaGen(++this->ssaNb_, classType);
    this->storeGen(classType, this->registerToLlvm(0),
                   this->registerToLlvm(this->ssaNb_));
    this->cScope_->value(std::string("self"))->ssaptr() = this->ssaNb_;
    // Allocating the arguments
    for (size_t i = 0; i < formalsSize; ++i)
    {
        const auto &formalptr = formals[i];
        const auto &fieldName = formalptr->first->name();
        auto ftype = this->convertType(*formalptr->second);

        this->allocaGen(++this->ssaNb_, ftype);
        this->storeGen(ftype, this->registerToLlvm(i + 1),
                       this->registerToLlvm(this->ssaNb_));

        this->cScope_->value(fieldName)->ssaptr() = this->ssaNb_;
    }

    // Visiting the block node
    methodNode.block().accept(*this);

    // Ret
    this->retGen(methodType, this->ssaNb_);
    this->ss_ << "}\n\n";

    this->cScope_ = &this->cScope_->parent();
}

void CodeGeneratorVisitor::visit(__attribute__((unused))
                                 FormalsNode &formalsNode)
{
    /*
        This node should have been removed long ago
        */
}

void CodeGeneratorVisitor::visit(ObjectIDNode &objectIDNode)
{
    const auto &name = objectIDNode.name();
    const auto &classType = this->convertType(this->cClass_);
    const auto &objectType =
        this->convertType(this->cScope_->value(name)->type());
    unsigned &ssa = this->cScope_->value(name)->ssaptr();

    // Is a ptr to objectID not already on the stack
    if (ssa == 0)
    {
        getEleGen(++this->ssaNb_, classType, this->registerToLlvm(0),
                  this->fMap_[this->cClass_ + "_" + name]);
        ssa = this->ssaNb_;
    }

    loadGen(++this->ssaNb_, objectType, this->registerToLlvm(ssa));
}

void CodeGeneratorVisitor::visit(IfNode &ifNode)
{
    std::vector<Node *> &exprs = ifNode.exprs();

    // Conditionnal expression
    exprs[0]->accept(*this);

    // Creating labels
    this->labelNb_++;
    const auto &labelNb = std::to_string(this->labelNb_);
    const auto &trueLabel = std::string("if_true_") + labelNb;
    const auto &trueDummyLabel = std::string("if_true_dummy_") + labelNb;
    const auto &falseLabel = std::string("if_false_") + labelNb;
    const auto &falseDummyLabel = std::string("if_false_dummy_") + labelNb;
    const auto &endLabel = std::string("if_end_") + labelNb;
    const auto &ifType = *ifNode.exprType();
    const auto &ifLlvmType = this->convertType(ifType);
    const auto &thenLlvmType = this->convertType(*exprs[1]->exprType());

    // True label
    branchGen(this->ssaNb_, trueLabel, falseLabel);
    this->ss_ << trueLabel << ":\n";
    exprs[1]->accept(*this);
    if (this->iTree_->contains(ifType) && ifLlvmType != thenLlvmType)
    {
        this->ssaNb_++;
        this->bitcastGen(this->ssaNb_, thenLlvmType, this->ssaNb_ - 1,
                         ifLlvmType);
    }
    const unsigned truessa = this->ssaNb_;
    this->branchGen(trueDummyLabel);
    this->ss_ << trueDummyLabel << ":\n";
    this->branchGen(endLabel);

    // False label
    this->ss_ << falseLabel << ":\n";
    if (exprs.size() == 3)
    {
        exprs[2]->accept(*this);
        const auto &fLlType = this->convertType(*exprs[2]->exprType());
        if (this->iTree_->contains(ifType) && ifLlvmType != fLlType)
        {
            this->ssaNb_++;
            this->bitcastGen(this->ssaNb_, fLlType, this->ssaNb_ - 1,
                             ifLlvmType);
        }
    }
    const unsigned falsessa = this->ssaNb_;
    this->branchGen(falseDummyLabel);
    this->ss_ << falseDummyLabel << ":\n";
    this->branchGen(endLabel);

    // End label
    this->ss_ << endLabel << ":\n";
    if (ifType == "unit")
        this->init(ifLlvmType);
    else
        this->phiGen(++this->ssaNb_, ifLlvmType, truessa, trueDummyLabel,
                     falsessa, falseDummyLabel);
}

void CodeGeneratorVisitor::visit(WhileNode &whileNode)
{
    // Creating labels
    this->labelNb_++;
    const auto &labelNb = std::to_string(this->labelNb_);
    const auto &condLabel = std::string("while_cond_") + labelNb;
    const auto &bodyLabel = std::string("while_body_") + labelNb;
    const auto &endLabel = std::string("while_end_") + labelNb;

    this->branchGen(condLabel);

    // Conditionnal label
    this->ss_ << condLabel << ":\n";
    whileNode.condExpr().accept(*this);
    this->branchGen(this->ssaNb_, bodyLabel, endLabel);

    // Body label
    this->ss_ << bodyLabel << ":\n";
    whileNode.bodyExpr().accept(*this);
    this->branchGen(condLabel);

    // End label
    this->ss_ << endLabel << ":\n";
    this->init(std::string("%unit"));
}

void CodeGeneratorVisitor::visit(LetNode &letNode)
{
    // Going through assign expression first
    const auto &letLlvmType = this->convertType(letNode.type());
    const auto &objectName = letNode.objectID().name();
    try
    {
        DummyNode &dummyNode = letNode.assignExpr();
        Node &node = dynamic_cast<Node &>(dummyNode);
        node.accept(*this);

        const auto &assignLlvmType = this->convertType(*node.exprType());
        if (this->iTree_->contains(letNode.type()) &&
            assignLlvmType != letLlvmType)
        { // We have to bitcast
            this->ssaNb_++;
            this->bitcastGen(this->ssaNb_, assignLlvmType, this->ssaNb_ - 1,
                             letLlvmType);
        }
    }
    catch (std::bad_cast &bc)
    {
        this->init(letLlvmType);
    }

    unsigned bfr = 0;
    if (this->cScope_->value(objectName))
        bfr = this->cScope_->value(objectName)->ssaptr();

    // Entering scope
    this->cScope_ = this->vTree_->table(letNode.scopeIndex());

    // Allocating new variable on the stack
    this->cScope_->value(objectName)->ssaptr() = ++this->ssaNb_;
    this->allocaGen(this->ssaNb_, letLlvmType);
    this->storeGen(letLlvmType, this->registerToLlvm(this->ssaNb_ - 1),
                   this->registerToLlvm(this->ssaNb_));

    letNode.inExpr().accept(*this);

    // Leaving scope
    this->cScope_ = &this->cScope_->parent();

    if (this->cScope_->value(objectName))
        this->cScope_->value(objectName)->ssaptr() = bfr;
}

void CodeGeneratorVisitor::visit(AssignNode &assignNode)
{
    // Visiting assigner and bitcasting if need be
    const auto &objectName = assignNode.objectID().name();
    const auto &assignType = *assignNode.assignExpr().exprType();
    const auto &objectType = this->cScope_->value(objectName)->type();

    assignNode.assignExpr().accept(*this);

    if (this->vTree_->contains(assignType) && assignType != objectType)
    {
        this->ssaNb_++;
        this->bitcastGen(this->ssaNb_, this->convertType(assignType),
                         this->ssaNb_ - 1, this->convertType(objectType));
    }
    const unsigned ssaAssign = this->ssaNb_;

    // Visiting assignee
    assignNode.objectID().accept(*this);
    const unsigned ssaObject = this->cScope_->value(objectName)->ssaptr();

    this->storeGen(this->convertType(objectType),
                   this->registerToLlvm(ssaAssign),
                   this->registerToLlvm(ssaObject));

    this->loadGen(++this->ssaNb_, this->convertType(objectType),
                  this->registerToLlvm(ssaObject));
}

void CodeGeneratorVisitor::visit(BinaryOpNode &binaryOpNode)
{
    // Special case due to shortcircuiting
    if (binaryOpNode.binaryType() == BinaryOpNode::binaryType::AND)
    {
        const auto &label = std::to_string(++this->labelNb_);
        const auto &startLabel = "and_start_" + label;
        const auto &noShortLabel = "and_no_short_circuit_" + label;
        const auto &endLabel = "and_end_" + label;

        // Visiting first node
        binaryOpNode.leftExpr().accept(*this);
        const unsigned ssaLeft = this->ssaNb_;

        this->branchGen(startLabel);
        // Start label, here for phi only
        this->ss_ << startLabel << ":\n";
        this->branchGen(this->ssaNb_, noShortLabel, endLabel);

        // No shortcircuit
        this->ss_ << noShortLabel << ":\n";
        binaryOpNode.rightExpr().accept(*this);
        const unsigned ssaRight = this->ssaNb_;
        this->binaryGen(++this->ssaNb_, "and", std::string("%bool"), ssaLeft,
                        ssaRight);
        this->branchGen(endLabel);

        // End label
        this->ss_ << endLabel << ":\n";
        this->ssaNb_++;
        this->phiGen(this->ssaNb_, std::string("%bool"), ssaLeft, startLabel,
                     this->ssaNb_ - 1, noShortLabel);
        return;
    }

    // Visiting expr nodes first
    binaryOpNode.leftExpr().accept(*this);
    const unsigned ssaLeft = this->ssaNb_;
    binaryOpNode.rightExpr().accept(*this);
    const unsigned ssaRight = this->ssaNb_;
    const unsigned ssa = ++this->ssaNb_;

    switch (binaryOpNode.binaryType())
    {
    case BinaryOpNode::binaryType::LOWER: // right > left
        this->binaryGen(ssa, "icmp slt", std::string("%int32"), ssaLeft,
                        ssaRight);
        break;
    case BinaryOpNode::binaryType::LOWERQ:
        this->binaryGen(ssa, "icmp sle", std::string("%int32"), ssaLeft,
                        ssaRight);
        break;
    case BinaryOpNode::binaryType::PLUS:
        this->binaryGen(ssa, "add", std::string("%int32"), ssaLeft, ssaRight);
        break;
    case BinaryOpNode::binaryType::MINUS:
        this->binaryGen(ssa, "sub", std::string("%int32"), ssaLeft, ssaRight);
        break;
    case BinaryOpNode::binaryType::TIMES:
        this->binaryGen(ssa, "mul", std::string("%int32"), ssaLeft, ssaRight);
        break;
    case BinaryOpNode::binaryType::DIVIDE:
        this->binaryGen(ssa, "sdiv", std::string("%int32"), ssaLeft, ssaRight);
        break;
    case BinaryOpNode::binaryType::EQUAL:
    {
        const auto &leftLlvmtype =
            this->convertType(*binaryOpNode.leftExpr().exprType());
        const auto &rightLlvmtype =
            this->convertType(*binaryOpNode.rightExpr().exprType());
        if (leftLlvmtype != rightLlvmtype) // We have to bitcast
        {
            this->bitcastGen(ssa, leftLlvmtype, ssaLeft, rightLlvmtype);
            this->binaryGen(++this->ssaNb_, "icmp eq", rightLlvmtype, ssa,
                            ssaRight);
        }
        else
            this->binaryGen(ssa, "icmp eq", rightLlvmtype, ssaLeft, ssaRight);
        break;
    }
    case BinaryOpNode::binaryType::POW:
    {
        const auto &label = std::to_string(++this->labelNb_);
        const auto &invalLabel = "pow_inval_" + label;
        const auto &initLabel = "pow_init_" + label;
        const auto &condLabel = "pow_cond_" + label;
        const auto &bodyLabel = "pow_body_" + label;
        const auto &endLabel = "pow_end_" + label;
        const auto &type = std::string("%int32");

        this->ss_ << "\t%" << this->ssaNb_ << " = icmp slt %int32 %" << ssaRight
                  << ", 0\n";
        this->branchGen(this->ssaNb_, invalLabel, initLabel);

        // Inval label
        this->ss_ << invalLabel << ":\n";
        this->init(type);
        const unsigned ssaInit = this->ssaNb_;
        this->branchGen(endLabel);

        // Init label
        this->ss_ << initLabel << ":\n";
        this->allocaGen(++this->ssaNb_, type);
        const auto &allocaLeft = this->registerToLlvm(this->ssaNb_);
        this->allocaGen(++this->ssaNb_, type);
        const auto &allocaRight = this->registerToLlvm(this->ssaNb_);
        this->storeGen(type, std::string("1"), allocaLeft);
        this->storeGen(type, std::string("1"), allocaRight);
        this->branchGen(condLabel);

        // Cond label
        this->ss_ << condLabel << ":\n";
        this->loadGen(++this->ssaNb_, type, allocaRight);
        this->ssaNb_++;
        this->binaryGen(this->ssaNb_, "icmp sle", "%int32", this->ssaNb_ - 1,
                        ssaRight);
        this->loadGen(++this->ssaNb_, type, allocaLeft);
        const unsigned ssaCond = this->ssaNb_;

        this->branchGen(this->ssaNb_ - 1, bodyLabel, endLabel);

        // Body label
        this->ss_ << bodyLabel << ":\n";
        this->loadGen(++this->ssaNb_, type, allocaLeft);
        this->ssaNb_++;
        this->binaryGen(this->ssaNb_, "mul", "%int32", this->ssaNb_ - 1,
                        ssaLeft);
        this->storeGen(type, this->registerToLlvm(this->ssaNb_), allocaLeft);

        this->loadGen(++this->ssaNb_, type, allocaRight);
        this->ssaNb_++;
        this->ss_ << "\t%" << this->ssaNb_ << " = add %int32 1, %"
                  << this->ssaNb_ - 1 << "\n";
        this->storeGen(type, this->registerToLlvm(this->ssaNb_), allocaRight);
        this->branchGen(condLabel);

        // End label
        this->ss_ << endLabel << ":\n";
        this->phiGen(++this->ssaNb_, type, ssaInit, invalLabel, ssaCond,
                     condLabel);
        break;
    }
    default:
        return;
    }
}

void CodeGeneratorVisitor::visit(UnaryOpNode &unaryOpNode)
{
    // Visiting the expr first so that we have its ssa
    unaryOpNode.expr().accept(*this);
    const unsigned ssa = this->ssaNb_;

    switch (unaryOpNode.unaryType())
    {
    case UnaryOpNode::unaryType::NOT:
        // Using xor to implement a not
        this->ss_ << "\t%" << ++this->ssaNb_ << " = xor %bool %" << ssa
                  << ", true\n";
        break;
    case UnaryOpNode::unaryType::MINUS:
        // 0 - expr
        this->ss_ << "\t%" << ++this->ssaNb_ << " = sub %int32 0, %" << ssa
                  << "\n";
        break;
    case UnaryOpNode::unaryType::ISNULL:
    {
        const auto &type = this->convertType(*unaryOpNode.expr().exprType());
        // Comparging to null
        this->ss_ << "\t%" << ++this->ssaNb_ << " = icmp eq " << type << " %"
                  << ssa << ", null\n";
        break;
    }
    }
}

void CodeGeneratorVisitor::visit(CallNode &callNode)
{
    // Visiting caller node
    callNode.expr().accept(*this);
    unsigned ssaCaller = this->ssaNb_;

    // Fetching a lot of info from everywhere
    const auto &methodName = callNode.objectID().name();
    const auto &callerClassName = *callNode.expr().exprType();
    const auto &callerClassType = this->convertType(callerClassName);
    auto &methodInfo = *this->fTree_->table(callerClassName)->value(methodName);
    const auto &actualClassName = methodInfo.classKey();
    const auto &actualClassType = this->convertType(actualClassName);
    const auto &retType = this->convertType(methodInfo.type());
    const auto &vTableType = "%struct." + callerClassName + "VTable*";

    // Searching pointer to the table
    this->ssaNb_++;
    this->getEleGen(this->ssaNb_, callerClassType,
                    this->registerToLlvm(ssaCaller), 0);
    this->ssaNb_++;
    this->loadGen(this->ssaNb_, vTableType,
                  this->registerToLlvm(this->ssaNb_ - 1));

    // Get ptr to method
    this->ssaNb_++;
    this->getEleGen(this->ssaNb_, vTableType,
                    this->registerToLlvm(this->ssaNb_ - 1),
                    this->mMap_[actualClassName + "_" + methodName]);
    const unsigned ssaMethod = this->ssaNb_;

    // Bitcasting if need be
    if (callerClassType != actualClassType)
    {
        this->bitcastGen(++this->ssaNb_, callerClassType, ssaCaller,
                         actualClassType);
        ssaCaller = this->ssaNb_;
    }

    // Building method type and argument vector
    std::string methodType = retType + " (" + actualClassType + ", ";
    std::vector<std::string> args(
        {actualClassType + " " + this->registerToLlvm(ssaCaller)});

    size_t size = callNode.args().size();
    for (size_t i = 0; i < size; ++i)
    {
        const auto &formalType = this->convertType(*methodInfo.formals()[i]);
        const auto &argType =
            this->convertType(*callNode.args()[i]->exprType());

        callNode.args()[i]->accept(*this);

        if (argType != formalType) // Bitcast
        {
            this->ssaNb_++;
            this->bitcastGen(this->ssaNb_, argType, this->ssaNb_ - 1,
                             formalType);
        }

        args.push_back(formalType + " " + this->registerToLlvm(this->ssaNb_));
        methodType += formalType + ", ";
    }
    methodType = methodType.substr(0, methodType.size() - 2) + ")*";

    // Loading method
    this->ssaNb_++;
    this->loadGen(this->ssaNb_, methodType, this->registerToLlvm(ssaMethod));

    // Making the call
    this->ssaNb_++;
    this->callGen(this->ssaNb_, retType, this->registerToLlvm(this->ssaNb_ - 1),
                  args);
}

void CodeGeneratorVisitor::visit(NewNode &newNode)
{
    const auto &llvmType = this->convertType(newNode.typeID());
    const auto &methodName = "@" + newNode.typeID() + "__new";
    this->callGen(++this->ssaNb_, llvmType, methodName,
                  std::vector<std::string>());
}

void CodeGeneratorVisitor::visit(LiteralNode &literalNode)
{
    switch (literalNode.literalType())
    {
    case LiteralNode::literalType::INTEGER:
    {
        // Allocating, storing, loading
        this->ss_ << "\t%" << ++this->ssaNb_ << " = add %int32 0, "
                  << literalNode.value() << "\n";
        break;
    }
    case LiteralNode::literalType::BOOL:
    {
        this->ss_ << "\t%" << ++this->ssaNb_ << " = add %bool 0, "
                  << literalNode.value() << "\n";
        break;
    }
    case LiteralNode::literalType::STRING:
    {
        // String must be declared constant, we poop it wherever we are
        std::string value =
            literalNode.value().substr(1, literalNode.value().size() - 2);
        unsigned size = value.size();
        unsigned llSize = value.size() + 1; // To be printed in the llvm file

        // There might be escaped characters withing the string
        for (size_t i = 1; i < size; ++i)
            if (value[i - 1] == '\\' && value[i] == 'x')
            {
                value.erase(i, 1);
                size--;
                i--;
                llSize -= 3;
            }

        // Is the string already defined ? (strings are immutable in
        // vsop)
        if (this->sMap_.find(value) != this->sMap_.end())
            this->getStrGen(++this->ssaNb_, llSize, this->sMap_[value]);
        else
        {
            std::stringstream ss;
            ss << "@str" << ++this->strNb_ << " = constant [" << llSize
               << " x i8] c\"" << value << "\\00\"\n";
            this->code_ += ss.str();
            this->getStrGen(++this->ssaNb_, llSize, this->strNb_);
            this->sMap_[value] = this->strNb_;
        }
        break;
    }
    }
}

void CodeGeneratorVisitor::visit(BlockNode &blockNode)
{
    this->cScope_ = this->vTree_->table(blockNode.scopeIndex());

    for (const auto &nodeptr : blockNode.exprs())
        nodeptr->accept(*this);

    this->cScope_ = &this->cScope_->parent();
}

void CodeGeneratorVisitor::visit(__attribute__((unused)) UnitNode &unitNode)
{
    this->init(std::string("%unit"));
}

std::string &CodeGeneratorVisitor::code() { return this->code_; }

std::string CodeGeneratorVisitor::convertType(std::string type)
{
    if (this->iTree_->contains(type))
        type = "struct." + type + "*";
    type = "%" + type;
    return type;
}

std::string CodeGeneratorVisitor::registerToLlvm(const unsigned &ssa)
{
    return "%" + std::to_string(ssa);
}

void CodeGeneratorVisitor::allocaGen(const unsigned &ssaDest,
                                     const std::string &type)
{
    this->ss_ << "\t%" << ssaDest << " = alloca " << type << "\n";
}

void CodeGeneratorVisitor::loadGen(const unsigned &ssaDest,
                                   const std::string &type,
                                   const std::string &src)
{
    this->ss_ << "\t%" << ssaDest << " = load " << type << ", " << type << "* "
              << src << "\n";
}

void CodeGeneratorVisitor::storeGen(const std::string &type,
                                    const std::string &src,
                                    const std::string &dest)
{
    this->ss_ << "\tstore " << type << " " << src << ", " << type << "* "
              << dest << "\n";
}

void CodeGeneratorVisitor::binaryGen(const unsigned &ssaDest,
                                     const char *const &op,
                                     const std::string &type,
                                     const unsigned &ssaLeft,
                                     const unsigned &ssaRight)
{
    this->ss_ << "\t%" << ssaDest << " = " << op << " " << type << " %"
              << ssaLeft << ", %" << ssaRight << "\n";
}

void CodeGeneratorVisitor::bitcastGen(const unsigned &ssaDest,
                                      const std::string &fromType,
                                      const unsigned &ssa,
                                      const std::string &toType)
{
    this->ss_ << "\t%" << ssaDest << " = bitcast " << fromType << " %" << ssa
              << " to " << toType << "\n";
}

void CodeGeneratorVisitor::callGen(const unsigned &ssaDest,
                                   const std::string &retType,
                                   const std::string &methodName,
                                   const std::vector<std::string> &args)
{
    std::stringstream ss;
    ss << "\t%" << ssaDest << " = call " << retType << " " << methodName << "(";
    for (auto const &arg : args)
        ss << arg << ", ";
    if (!args.empty())
        this->ss_ << ss.str().substr(0, ss.str().size() - 2) + ")\n";
    else
        this->ss_ << ss.str() + ")\n";
}

void CodeGeneratorVisitor::getEleGen(const unsigned &ssaDest,
                                     const std::string &type,
                                     const std::string &ptr,
                                     const unsigned &idx)
{
    this->ss_ << "\t%" << ssaDest << " = getelementptr "
              << type.substr(0, type.size() - 1) << ", " << type << " " << ptr
              << ", i32 0, i32 " << idx << "\n";
}

void CodeGeneratorVisitor::branchGen(const unsigned &ssaCond,
                                     const std::string &label1,
                                     const std::string &label2)
{
    this->ss_ << "\tbr %bool %" << ssaCond << ", label %" << label1 << ", "
              << "label %" << label2 << "\n";
}

void CodeGeneratorVisitor::branchGen(const std::string &label)
{
    this->ss_ << "\tbr label %" << label << "\n";
}

void CodeGeneratorVisitor::phiGen(const unsigned &ssa, const std::string &type,
                                  const unsigned &ssa1,
                                  const std::string &label1,
                                  const unsigned &ssa2,
                                  const std::string &label2)
{
    this->ss_ << "\t" << this->registerToLlvm(ssa) << " = phi " << type << " ["
              << this->registerToLlvm(ssa1) << ", %" << label1 << "], ["
              << this->registerToLlvm(ssa2) << ", %" << label2 << "]\n";
}

void CodeGeneratorVisitor::retGen(const std::string &type, const unsigned &ssa)
{
    this->ss_ << "\tret " << type << " " << this->registerToLlvm(ssa) << " \n";
}
void CodeGeneratorVisitor::getStrGen(const unsigned &ssa, const unsigned &size,
                                     const unsigned &idx)
{
    std::stringstream ss;
    ss << "[" << size << " x i8]*";
    std::string type = ss.str();
    ss.clear();
    ss.str("");
    ss << "@str" << idx;
    std::string ptr = ss.str();

    this->getEleGen(ssa, type, ptr, 0);
}

void CodeGeneratorVisitor::init(const std::string &type)
{
    if (type == "%string")
        this->getStrGen(++this->ssaNb_, 1, 1);
    else if (type == "%int32" || type == "%unit" || type == "%bool")
        this->ss_ << "\t%" << ++this->ssaNb_ << " = add " << type << " 0, 0\n";
    else // null
    {
        this->allocaGen(++this->ssaNb_, type);
        this->storeGen(type, std::string("null"),
                       this->registerToLlvm(this->ssaNb_));
        this->ssaNb_++;
        this->loadGen(this->ssaNb_, type,
                      this->registerToLlvm(this->ssaNb_ - 1));
    }
}
