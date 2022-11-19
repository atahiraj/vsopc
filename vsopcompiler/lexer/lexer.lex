/*!
 * \file lexer.lex
 * \brief Source code containing some useful functions for lexical analysis.
 * \author Tahiraj Arian
 * \author Leroy Antoine
 * \version 0.1
 */
%option noyywrap
%option nounput
%option noinput
%{
	#include <errno.h>
	#include <iostream>
	#include <string.h>
	#include <stack>
	#include <vector>
	#include <parser/parser.hpp>

	/***************************** Useful macros ******************************/
	/* Error print macros */
	#define ERROR(L,C)     curr_lin = (L); curr_col = (C);

	#define ERREX(L,C,M)    do                                                 \
							{                                                  \
								ERROR((L),(C)); error = M;                     \
								return -1;                                     \
							} while(0)

	#define ERREX_S(M)      ERREX(curr_lin, curr_col, (M))

	/* Static variables update */
	#define RESET_COL       curr_col = 1
	#define RESET_LINE      curr_lin = 1
	#define UPDATE_COL      curr_col += yyleng
	#define UPDATE_LINE     ++curr_lin

	/* Return tokens */
	#define RETURN(Cl, V, L, C, T)                                             \
							do {                                               \
								print_class = (Cl);                            \
								print_value = (V);                             \
								print_pos.line = (L);                          \
								print_pos.column = (C);                        \
								yylloc.first_line = curr_lin;                  \
								yylloc.first_column = curr_col;                \
								UPDATE_COL;                                    \
								yylloc.last_line = curr_lin;                   \
								yylloc.last_column = curr_col;                 \
								return (T);                                    \
							} while(0)

	#define RETURN_S(C, V, T)                                                  \
							RETURN((C), (V), curr_lin, curr_col, (T))

	#define RETURN_KEY(T)   RETURN_S(yytext, "", (T))

	/* Error messages */
	#define I_HEX           "Invalid hexadecimal integer"
	#define I_DEC           "Invalid decimal integer"
	#define I_COM           "Unclosed comments"
	#define I_S_S           "Invalid escape sequence"
	#define I_S_N           "Line Feed in string"
	#define I_S_0           "Null character in string"
	#define I_S_U           "Unfinished string"
	#define I_CAR           "Invalid character"

	using namespace std;

	/* Position structure */
	struct position
	{
		int line, column;
	};

	/* Static variables used */
	static int curr_lin = 1, curr_col = 1, nested_comment = 0;
	static position start_pos, print_pos;
	static stack<position> nest_stack;
	static string current_string, error, file_name, print_class, print_value;

%}


	/* DEFINITIONS */
	// Base definitions
LOWER_CASE                  [a-z]
UPPER_CASE                  [A-Z]
LETTER                      {LOWER_CASE}|{UPPER_CASE}
DIGIT                       [0-9]
HEX_DIGIT                   {DIGIT}|[a-fA-F]
NON_HEX                     [g-zG-Z]
TYPE_ID                     {UPPER_CASE}({LETTER}|{DIGIT}|_)*
OBJECT_ID                   {LOWER_CASE}({LETTER}|{DIGIT}|_)*
END_OF_LINE                 \n|\r|(\r\n)
WHITESPACE                  [ \t]
XHH                         \\x{HEX_DIGIT}{HEX_DIGIT}
MULTI                       \\{END_OF_LINE}{WHITESPACE}*

%x S_COMMENT M_COMMENT STRING

%%

	/* RULES */

	/* Trivial regexes */
{WHITESPACE}+               UPDATE_COL;
{END_OF_LINE}               RESET_COL; UPDATE_LINE;
\f                          RESET_LINE; RESET_COL;
"and"                       RETURN_KEY(AND);
"bool"                      RETURN_KEY(BOOL);
"class"                     RETURN_KEY(CLASS);
"do"                        RETURN_KEY(DO);
"else"                      RETURN_KEY(ELSE);
"extends"                   RETURN_KEY(EXTENDS);
"false"                     RETURN_KEY(FALSE_LIT);
"if"                        RETURN_KEY(IF);
"in"                        RETURN_KEY(IN_);
"int32"                     RETURN_KEY(INT32);
"isnull"                    RETURN_KEY(ISNULL);
"let"                       RETURN_KEY(LET);
"new"                       RETURN_KEY(NEW);
"not"                       RETURN_KEY(NOT);
"string"                    RETURN_KEY(STRING_TYPE);
"then"                      RETURN_KEY(THEN);
"true"                      RETURN_KEY(TRUE_LIT);
"unit"                      RETURN_KEY(UNIT);
"while"                     RETURN_KEY(WHILE);
{TYPE_ID}                   yylval.str = new string(yytext); RETURN_S("type-identifier", yytext, TYPEID);
{OBJECT_ID}                 yylval.str = new string(yytext); RETURN_S("object-identifier", yytext, OBJECTID);
"{"                         RETURN_S("lbrace", "", LBRACE);
"}"                         RETURN_S("rbrace", "", RBRACE);
"("                         RETURN_S("lpar", "", LPAREN);
")"                         RETURN_S("rpar", "", RPAREN);
":"                         RETURN_S("colon", "", COLON);
";"                         RETURN_S("semicolon", "", SEMICOLON);
","                         RETURN_S("comma", "", COMMA);
"+"                         RETURN_S("plus", "", PLUS);
"-"                         RETURN_S("minus", "", MINUS);
"*"                         RETURN_S("times", "", TIMES);
"/"                         RETURN_S("div", "", DIVIDE);
"^"                         RETURN_S("pow", "", POW);
"."                         RETURN_S("dot", "", DOT);
"="                         RETURN_S("equal", "", EQUAL);
"<"                         RETURN_S("lower", "", LOWER);
"<="                        RETURN_S("lower-equal", "", LOWERQ);
"<-"                        RETURN_S("assign", "", ASSIGN);

	/* Integers */
0x{HEX_DIGIT}+              {
								yylval.str = new string(to_string(strtol(yytext, NULL, 16)));
								RETURN_S("integer-literal",
									to_string(strtol(yytext, NULL, 16)),
									INT_LIT);
							}
0x{HEX_DIGIT}*{NON_HEX}*    ERREX_S(I_HEX);
{DIGIT}+                    {
								yylval.str = new string(to_string(strtol(yytext, NULL, 10)));
								RETURN_S("integer-literal",
									to_string(strtol(yytext, NULL, 10)),
									INT_LIT);
							}
{DIGIT}*{LETTER}*           ERREX_S(I_DEC);

	/* Single line comments */
"//"                        {
								start_pos.line = curr_lin;
								start_pos.column = curr_col;
								UPDATE_COL;
								BEGIN(S_COMMENT);
							}
<S_COMMENT>{END_OF_LINE}    UPDATE_LINE; RESET_COL; BEGIN(INITIAL);
<S_COMMENT>.                UPDATE_COL;
<S_COMMENT><<EOF>>          UPDATE_COL; return 0;

	/* Multi line comments */
<INITIAL,M_COMMENT>"(*"     {
								++nested_comment;
								position pos;
								pos.line = curr_lin; pos.column = curr_col;
								nest_stack.push(pos);
								UPDATE_COL;
								BEGIN(M_COMMENT);
							}
<M_COMMENT>{END_OF_LINE}    {RESET_COL; UPDATE_LINE;}
<M_COMMENT>"*)"             {
								nest_stack.pop();
								UPDATE_COL;
								if(--nested_comment == 0)
									BEGIN(INITIAL);
							}
<M_COMMENT>.                 UPDATE_COL;
<M_COMMENT><<EOF>>          {
								position last = nest_stack.top();
								curr_lin = last.line;
								curr_col = last.column;
								ERREX_S(I_COM);
							}

	/* Strings */
\"                          {
								start_pos.column = curr_col;
								start_pos.line = curr_lin;
								UPDATE_COL;
								current_string = yytext;
								BEGIN(STRING);
							}
<STRING>{XHH}               {
								UPDATE_COL;
								string hex = yytext+2;
								int xhh = stoi(hex, NULL, 16);
								if(xhh >= 32 && xhh <= 126)
									current_string += (char) xhh;
								else
									current_string += yytext;
							}
<STRING>\"                  {
								current_string += yytext;
								yylval.str = new string(current_string);
								BEGIN(INITIAL);
								print_class = ("string-literal");
								print_value = (current_string);
								print_pos.line = start_pos.line;
								print_pos.column = start_pos.column;
								yylloc.first_line = start_pos.line;
								yylloc.first_column = start_pos.column;
								UPDATE_COL;
								yylloc.last_line = curr_lin;
								yylloc.last_column = curr_col;
								return STRING_LIT;
							}
<STRING>(\r\n){WHITESPACE}* RESET_COL; UPDATE_COL; curr_col -= 4; UPDATE_LINE;
<STRING>{MULTI}             RESET_COL; UPDATE_COL; curr_col -= 2; UPDATE_LINE;
<STRING>\\\\                UPDATE_COL; current_string += "\\x5c";
<STRING>\\b                 UPDATE_COL; current_string += "\\x08";
<STRING>\\t                 UPDATE_COL; current_string += "\\x09";
<STRING>\\n                 UPDATE_COL; current_string += "\\x0a";
<STRING>\\r                 UPDATE_COL; current_string += "\\x0d";
<STRING>\\\"                UPDATE_COL; current_string += "\\x22";
<STRING>\\([^\\btnr\"]|" ") ERREX_S(I_S_S);
<STRING>\n                  ERREX_S(I_S_N);
<STRING>\0                  ERREX_S(I_S_0);
<STRING>.                   UPDATE_COL; current_string += yytext;
<STRING><<EOF>>             ERREX(start_pos.line, start_pos.column, I_S_U);

	/* End of file */
<INITIAL><<EOF>>            return 0;

	/* Invalid character */
.                           ERREX_S(I_CAR);

%%

/* USER CODE */

/* -----------------------------------------------------------------------------
 * Called to set yyin to the input file
 *
 * PARAMETERS
 * filname: name of the input file (char*)
 *
 * RETURN
 * /
 * ---------------------------------------------------------------------------*/
void yylex_init(char* filename)
{
	/* Opening the file */
	yyin = fopen(filename, "r");
	if (yyin == NULL)
	{
		cerr << "Error opening file: ";
		perror(NULL);
		exit(-1);
	}
	file_name = filename;
	return;
}

 /* -----------------------------------------------------------------------------
 * Prints lexical analyzer output
 *
 * PARAMETERS
 * /
 *
 * RETURN
 * -1 if an error occured and 0 otherwise (int)
 * ---------------------------------------------------------------------------*/

int yylex_dump()
{
	int ret;
	/* Executing the lexer */
	while( (ret = yylex() ) > 0)
	{
		/* Printing token */
		cout << print_pos.line << "," << print_pos.column << "," << print_class;
		if (print_value == "")
			cout << "\n";
		else
			cout << "," << print_value << "\n";
	}
	fclose(yyin);

	if(ret == -1)
	{
		cerr << file_name << ":" << curr_lin << ":" << curr_col << ": lexical error"  << ": " << error << endl;
	}

	return ret;
}
