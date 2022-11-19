/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_VSOPCOMPILER_PARSER_PARSER_HPP_INCLUDED
# define YY_YY_VSOPCOMPILER_PARSER_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 41 "vsopcompiler/parser/parser.y"

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

#line 73 "vsopcompiler/parser/parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ASSIGN = 258,                  /* ASSIGN  */
    AND = 259,                     /* AND  */
    NOT = 260,                     /* NOT  */
    LOWER = 261,                   /* LOWER  */
    LOWERQ = 262,                  /* LOWERQ  */
    EQUAL = 263,                   /* EQUAL  */
    PLUS = 264,                    /* PLUS  */
    MINUS = 265,                   /* MINUS  */
    TIMES = 266,                   /* TIMES  */
    DIVIDE = 267,                  /* DIVIDE  */
    ISNULL = 268,                  /* ISNULL  */
    UNARY_MINUS = 269,             /* UNARY_MINUS  */
    POW = 270,                     /* POW  */
    DOT = 271,                     /* DOT  */
    BOOL = 272,                    /* BOOL  */
    CLASS = 273,                   /* CLASS  */
    COLON = 274,                   /* COLON  */
    COMMA = 275,                   /* COMMA  */
    DO = 276,                      /* DO  */
    ELSE = 277,                    /* ELSE  */
    EXTENDS = 278,                 /* EXTENDS  */
    FALSE_LIT = 279,               /* FALSE_LIT  */
    IF = 280,                      /* IF  */
    IN_ = 281,                     /* IN_  */
    INT32 = 282,                   /* INT32  */
    INT_LIT = 283,                 /* INT_LIT  */
    LET = 284,                     /* LET  */
    LBRACE = 285,                  /* LBRACE  */
    LPAREN = 286,                  /* LPAREN  */
    NEW = 287,                     /* NEW  */
    OBJECTID = 288,                /* OBJECTID  */
    RBRACE = 289,                  /* RBRACE  */
    RPAREN = 290,                  /* RPAREN  */
    SEMICOLON = 291,               /* SEMICOLON  */
    STRING_TYPE = 292,             /* STRING_TYPE  */
    STRING_LIT = 293,              /* STRING_LIT  */
    THEN = 294,                    /* THEN  */
    TRUE_LIT = 295,                /* TRUE_LIT  */
    TYPEID = 296,                  /* TYPEID  */
    UNIT = 297,                    /* UNIT  */
    WHILE = 298                    /* WHILE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "vsopcompiler/parser/parser.y"

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

#line 148 "vsopcompiler/parser/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_VSOPCOMPILER_PARSER_PARSER_HPP_INCLUDED  */
