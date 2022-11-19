/*!
 * \file parser.y
 * \brief Bison source file for the syntaxic analysis.
 * \author Tahiraj Arian
 * \author Leroy Antoine
 * \version 0.1
 */

/********************************* PROLOGUE ***********************************/
%{
	#include <cstddef>
	#include <iostream>
	#include <parser/parser.hpp>
	#include <lexer/lexer.hpp>
	std::string file_name;

	void yyerror(const char *s);
	AstNode* root;
%}

%locations

/******************************* DECLARATIONS *********************************/

%union
{
	Node* node;
	BlockNode* block_node;
	ClassNode* class_node;
	DummyNode* formals_node;
	FieldNode* field_node;
	MethodNode* method_node;
	std::string* str;
	std::pair<std::vector<FieldNode*>*, std::vector<MethodNode*>*>* field_method_pair ;
	std::vector<Node*>* node_vect;
	std::vector<ClassNode*>* class_node_vect;
	std::pair<ObjectIDNode*, std::string*>* formal_pair;
	std::vector<std::pair<ObjectIDNode*, std::string*>*>* formal_pair_vect;
}
%code requires
{
class DummyNode;
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
#include <astTree/nodes.hpp>
AstNode* parse(char* filename);
}

/* Expecting exactly 51 non-contrary warnings */
%expect 51

/* Start symbol */
%start program

/* Operators */
%right ASSIGN
%left AND
%right NOT
%nonassoc LOWER LOWERQ EQUAL
%left PLUS MINUS 
%left TIMES DIVIDE 
%right ISNULL 
%precedence UNARY_MINUS
%right POW
%left DOT

/* Terminal symbols */
%token BOOL
%token CLASS
%token COLON
%token COMMA
%token DO
%token ELSE
%token EXTENDS
%token FALSE_LIT
%token IF
%token IN_
%token INT32
%token<str> INT_LIT
%token LET
%token LBRACE
%token LPAREN
%token NEW
%token<str> OBJECTID
%token RBRACE
%token RPAREN
%token SEMICOLON
%token STRING_TYPE
%token<str> STRING_LIT
%token THEN
%token TRUE_LIT
%token<str> TYPEID
%token UNIT
%token WHILE

/* Non terminal symbols */
%type<node_vect> args
%type<node_vect> args_m
%type<block_node> block
%type<class_node> class
%type<class_node_vect> classes
%type<field_method_pair> class_body
%type<field_method_pair> class_content
%type<node> expr
%type<node_vect> expr_m
%type<field_node> field
%type<formal_pair> formal
%type<formal_pair_vect> formal_m
%type<formals_node> formals
%type<method_node> method
%type<str> type

%%

/*********************************** RULES ************************************/

program:
	classes class
	{
		$1->push_back($2);
		root = new AstNode(* new YYLTYPE(@$), * $1);
	}
;

classes:
	classes class
	{
		$1->push_back($2);
		$$ = $1;
	}
|   %empty {$$ = new std::vector<ClassNode*>();}
;

class:
	CLASS TYPEID class_body
	{
		std::vector<FieldNode*>& field_nodes = * $3->first;
		std::vector<MethodNode*>& method_nodes = * $3->second;

		delete $3;
		
		$$ = new ClassNode(* new YYLTYPE(@$), * $2, * new std::string("Object"), field_nodes, method_nodes);
	}


|   CLASS TYPEID EXTENDS TYPEID class_body
	{
		std::vector<FieldNode*>& field_nodes = * $5->first;
		std::vector<MethodNode*>& method_nodes = * $5->second;

		delete $5;

		$$ = new ClassNode(* new YYLTYPE(@$), * $2, * $4, field_nodes, method_nodes);
	}
;

class_body:
	LBRACE class_content RBRACE {$$ = $2;}
;

class_content:
	class_content field
	{
		$1->first->push_back($2);
		$$ = $1;
	}
|   class_content method
	{
		$1->second->push_back($2);
		$$ = $1;
	}
|   %empty
	{
		$$ = new std::pair<std::vector<FieldNode*>*, std::vector<MethodNode*>*> (new std::vector<FieldNode*>(), new std::vector<MethodNode*>());
	}
;

field:
	OBJECTID COLON type SEMICOLON
	{
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE(@1), * $1);
		$$ = new FieldNode(* new YYLTYPE(@$), objectID, * new DummyNode(), * $3);
	}
|   OBJECTID COLON type ASSIGN expr SEMICOLON
	{
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE(@1), * $1);
		$$ = new FieldNode(* new YYLTYPE(@$), objectID, * $5, * $3);
	}
;

method:
	OBJECTID LPAREN formals RPAREN COLON type block
	{
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE(@1), * $1);
		$$ = new MethodNode(* new YYLTYPE(@$), * $7, objectID, * $3, * $6);
	}
;

type:
	TYPEID {$$ = $1;}
|   INT32 {$$ = new std::string("int32");}
|   BOOL {$$ = new std::string("bool");}
|   STRING_TYPE {$$ = new std::string("string");}
|   UNIT {$$ = new std::string("unit");}
;

formals:
	formal_m formal
	{
		$1->push_back($2);
		$$ = new FormalsNode(* new YYLTYPE(@$), * $1);
	}
|   %empty {$$ = new DummyNode();}
;

formal_m:
	formal_m formal COMMA
	{
		$1->push_back($2);
		$$ = $1;
	}
|   %empty
	{
		$$ = new std::vector<std::pair<ObjectIDNode*, std::string*>*>();
	}
;

formal:
	OBJECTID COLON type
	{
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE(@1), * $1);
		$$ = new std::pair<ObjectIDNode*, std::string*>(&objectID, $3);
	}
;

block:
	LBRACE expr_m expr RBRACE
	{
		$2->push_back($3);
		$$ = new BlockNode(* new YYLTYPE(@$), * $2);
	}
;

expr_m:
	expr_m expr SEMICOLON  
	{
		$1->push_back($2);
		$$ = $1;
	}
|   %empty {$$ = new std::vector<Node*>();}
;

expr:
	IF expr THEN expr
	{
		std::vector<Node*>& exprs = * new std::vector<Node*>();
		exprs.push_back($2);
		exprs.push_back($4);
		$$ = new IfNode(* new YYLTYPE(@$), exprs);
	}
|   IF expr THEN expr ELSE expr
	{
		std::vector<Node*>& exprs = * new std::vector<Node*>();
		exprs.push_back($2);
		exprs.push_back($4);
		exprs.push_back($6);
		$$ = new IfNode(* new YYLTYPE(@$), exprs);
	}
|   WHILE expr DO expr
	{
		$$ = new WhileNode(* new YYLTYPE(@$), * $2, * $4);
	}
|   LET OBJECTID COLON type IN_ expr
	{
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE(@2), * $2);
		$$ = new LetNode(* new YYLTYPE(@$), objectID, * new DummyNode(), * $6, * $4);
	}
|   LET OBJECTID COLON type ASSIGN expr IN_ expr
	{
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE(@2), * $2);
		$$ = new LetNode(* new YYLTYPE(@$), objectID, * $6, * $8, * $4);
	}
|   OBJECTID ASSIGN expr
	{
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE(@1), * $1);
		$$ = new AssignNode(* new YYLTYPE(@$), objectID, * $3);
	}
|   NOT expr {$$ = new UnaryOpNode(* new YYLTYPE(@$), UnaryOpNode::unaryType::NOT, * $2);}
|   MINUS expr %prec UNARY_MINUS {$$ = new UnaryOpNode(* new YYLTYPE(@$), UnaryOpNode::unaryType::MINUS, * $2);}
|   ISNULL expr {$$ = new UnaryOpNode(* new YYLTYPE(@$), UnaryOpNode::unaryType::ISNULL, * $2);}

|   expr AND expr {$$ = new BinaryOpNode(* new YYLTYPE(@$), BinaryOpNode::binaryType::AND, * $1, * $3);}
|   expr EQUAL expr {$$ = new BinaryOpNode(* new YYLTYPE(@$), BinaryOpNode::binaryType::EQUAL, * $1, * $3);}
|   expr LOWER expr {$$ = new BinaryOpNode(* new YYLTYPE(@$), BinaryOpNode::binaryType::LOWER, * $1, * $3);}
|   expr LOWERQ expr {$$ = new BinaryOpNode(* new YYLTYPE(@$), BinaryOpNode::binaryType::LOWERQ, * $1, * $3);}
|   expr PLUS expr {$$ = new BinaryOpNode(* new YYLTYPE(@$), BinaryOpNode::binaryType::PLUS, * $1, * $3);}
|   expr MINUS expr {$$ = new BinaryOpNode(* new YYLTYPE(@$), BinaryOpNode::binaryType::MINUS, * $1, * $3);}
|   expr TIMES expr {$$ = new BinaryOpNode(* new YYLTYPE(@$), BinaryOpNode::binaryType::TIMES, * $1, * $3);}
|   expr DIVIDE expr {$$ = new BinaryOpNode(* new YYLTYPE(@$), BinaryOpNode::binaryType::DIVIDE, * $1, * $3);}
|   expr POW expr {$$ = new BinaryOpNode(* new YYLTYPE(@$), BinaryOpNode::binaryType::POW, * $1, * $3);}
|   OBJECTID LPAREN args RPAREN
	{
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE(@1), * $1);
		ObjectIDNode& selfObj = * new ObjectIDNode(* new YYLTYPE(@$), * new std::string("self"));

		
		$$ = new CallNode(* new YYLTYPE(@$), selfObj, objectID, * $3);
	}
|   expr DOT OBJECTID LPAREN args RPAREN
	{
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE(@3), * $3);

		$$ = new CallNode(* new YYLTYPE(@$), * $1, objectID, * $5);
	}
|   NEW TYPEID
	{
		$$ = new NewNode(* new YYLTYPE(@$), * $2);
	}
|   OBJECTID
	{
		$$ = new ObjectIDNode(* new YYLTYPE(@$), * $1);
	}
|   INT_LIT
	{
		$$ = new LiteralNode(* new YYLTYPE(@$), LiteralNode::literalType::INTEGER, * $1);
	}
|   STRING_LIT
	{
		$$ = new LiteralNode(* new YYLTYPE(@$), LiteralNode::literalType::STRING, * $1);
	}
|   FALSE_LIT
	{;
		$$ = new LiteralNode(* new YYLTYPE(@$), LiteralNode::literalType::BOOL,
								* new std::string("false"));
	}
|   TRUE_LIT
	{
		$$ = new LiteralNode(* new YYLTYPE(@$), LiteralNode::literalType::BOOL,
								* new std::string("true"));
	}
|   LPAREN expr RPAREN
	{
		$$ = $2;
	}
|   LPAREN RPAREN
	{
		$$ = new UnitNode(* new YYLTYPE(@$));
	}
|   block {$$ = $1;}
;

args:
	args_m expr
	{
		$1->push_back($2);
		$$ = $1;
	}
|   %empty {$$ = new std::vector<Node*>();}
;

args_m:
	args_m expr COMMA
	{
		$1->push_back($2);
		$$ = $1;
	}
|   %empty {$$ = new std::vector<Node*>();}
;

%%

/********************************* EPILOGUE ***********************************/

void yyerror(const char *s)
{
	std::cerr << file_name << ":" << yylloc.first_line << ":" << yylloc.first_column << ": " << s << std::endl;
}

AstNode * parse(char* filename)
{
	int ret = 0;
	file_name = std::string(filename);
	ret = yyparse();

	
	if(ret == 0)
		return root;
	else
		return nullptr;
}