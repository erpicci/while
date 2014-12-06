 /**********************************************************************
 * Definitions. 
 **********************************************************************/
%{
/* Header file inclusion. */
#include <string.h>
#include "parser.hh"

extern "C"{
int yyerror(const char *);
int yylex(void);
void set_source_file(FILE *descriptor);
}
%}

/* Unput-like function will not be used. */
%option nounput

%%
 /**********************************************************************
 * Rules. 
 **********************************************************************/
  
  /* Arithmetic operators. */
"+"      return SUM;
"-"      return DIF;
"*"      return MUL;
"/"      return DIV;
"%"      return REM;
"^"      return POW;
  
  /* Boolean operators and comparison operators. */
"true"   return TRUE;
"false"  return FALSE;
"not"    return NOT;
"and"    return AND;
"or"     return OR;
"xor"    return XOR;
"nand"   return NAND;
"nor"    return NOR;
"nxor"   return NXOR;
"="      return EQ;
"<>"     return NEQ;
"<"      return LT;
"<="     return LEQ;
">="     return GEQ;
">"      return GT;
  
  /* Statement operators. */
":="     return ASSIGNMENT;
";"      return COMPOSITION;
"skip"   return SKIP;
"if"     return IF;
"then"   return THEN;
"else"   return ELSE;
"end"    return END;
"while"  return WHILE;
"do"     return DO;
  
  /* Other operators and symbols. */
[()]     return *yytext;
"print"  return PRINT;
  
  /* Spaces and comments are ignored */
[ \t\n]+   ;
"//".*$    ;
  
  /* Numbers (integers only). */
[-]?[1-9][0-9]*|0 {
                    yylval.integer = atoi(yytext);
                    return NUM;
                  }
  
  /* Identifiers. */
[a-z][a-zA-Z0-9]* {
                    strcpy(yylval.literal, yytext);
                    return VAR;
                  }
  
  
  /* Anything else is an error. */
.  { 
     yyerror("[ERROR] Unrecognized input."); 
   }



%%
 /**********************************************************************
  * Auxiliary functions.
  *********************************************************************/

/* Predicate related to the number of file to parse at once. */
int yywrap(void)
{
  return 1;
}

/* Function which tells the scanner the source channel. */
void set_source_file(FILE *descriptor)
{
  yyin = descriptor;
}

