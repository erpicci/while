 ///////////////////////////////////////////////////////////////////////
 // Definitions.
%{
#include <string.h>

#include "../AST.hpp"
#include "../parser/parser.hpp"

int yyerror(const char *);
int yylex(void);
void set_source_file(FILE *descriptor);
%}

/* Unput-like function will not be used. */
%option nounput

%%
 ///////////////////////////////////////////////////////////////////////
 // Rules. 

  /* Statement operators. */
":="               return ASN;
"skip"             return SKIP;
";"                return SEQ;
"if"               return IF;
"then"             return THEN;
"else"             return ELSE;
"while"            return WHILE;
"do"               return DO;
"print"            return PRINT;
"input"            return INPUT;


  /* Arithmetic operators. */
"+"                return PLUS;
"-"                return MINUS;
"*"                return STAR;
"/"                return SLASH;
"%"                return PERC;
("^"|"**")         return CAP;


  /* Boolean operators and comparison operators. */
("true"|"tt")      return TRUE;
("false"|"ff")     return FALSE;
("not"|"!")        return NOT;

("and"|"&&")       return AND;
("or"|"||")        return OR;
("xor"|"$$")       return XOR;
("nand"|"!&")      return NAND;
("nor"|"!|")       return NOR;
("xnor"|"!$")      return XNOR;
"->"               return IMP;
"<-"               return RIMP;
"<->"              return XNOR;

"<"                return LT;
"<="               return LEQ;
("="|"==")         return EQ;
">="               return GEQ;
">"                return GT;
("<>"|"!=")        return NEQ;


  /* Other operators and symbols. */
"("                return LPAR;
")"                return RPAR;


  /* Constant, integer values. */
[-]?[1-9][0-9]*|0  { yylval.integer = atoi(yytext); return NUM; }


  /* Identifiers. */
[a-z][a-zA-Z0-9]*  { strcpy(yylval.literal, yytext); return VAR; }


  /* Spaces and comments are ignored */
[ \t\n]+           ;
"//".*$            ;


  /* Anything else is a lessical error. */
.                  { yyerror("[Lexer]: Unrecognized input."); }



%%
 ///////////////////////////////////////////////////////////////////////
 // Auxiliary functions.

// Predicate related to the number of file to parse at once.
int yywrap(void)
{
  return 1;
}

// Function which tells the scanner the source channel.
void set_source_file(FILE *descriptor)
{
  yyin = descriptor;
}
