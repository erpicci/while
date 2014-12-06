/***********************************************************************
 *  Definitions.
 **********************************************************************/
%{ /* Prologue. */
/* Header file inclusion. */
#include <stdio.h>
#include <string.h>

#include "wrapper.h"

/* Bison functions to be exported to flex. */
extern "C"{
int yylex(void);
int yyerror(const char *s);
int yywrap();
void set_source_file(FILE *descriptor);
}

/* Abstract Syntax Tree. */
void *ast;
%}



/* Union representing each possible type. */
%union {
   int  integer;        /* Integer value. */
   char literal[32];    /* Identifier or textual information. */
   void *tree;          /* Reference to abstract syntax (sub) tree. */
}; 



/* Declaration of tokens and operator precedences and associativity. */
%token <integer> NUM
%token <literal> VAR

%token ASSIGNMENT SKIP
%token COMPOSITION
%token IF THEN
%nonassoc ELSE
%token END WHILE DO

%left  SUM DIF
%left  MUL DIV REM
%right POW

%token TRUE FALSE
%right NOT
%left  AND OR XOR NAND NOR NXOR
%left  EQ NEQ LT LEQ GEQ GT

%token PRINT

/* Type of each possible production. */
%type <tree> StatementList Statement AExp BExp



%%/*********************************************************************
 * Rules.
 **********************************************************************/

Program: StatementList  { ast = $1; }
       |                { ast = NULL; }

StatementList: Statement COMPOSITION   { $$ = $1; }
             | StatementList
               Statement COMPOSITION   { $$ = _concatenation($1, $2); }

Statement: VAR ASSIGNMENT AExp { $$ = _assignment(_variable($1), $3); }
         | SKIP                { $$ = _skip();         }
         | IF BExp
           THEN StatementList
           ELSE StatementList
           END                 { $$ = _if($2, $4, $6); }
         | WHILE BExp DO
            StatementList
           END                 { $$ = _while($2, $4);  } 
         | PRINT AExp          { $$ = _print($2);      }

AExp: NUM           { $$ = _constant($1);       }
    | VAR           { $$ = _variable($1);       }
    | AExp SUM AExp { $$ = _sum($1, $3);        }
    | AExp DIF AExp { $$ = _difference($1, $3); }
    | AExp MUL AExp { $$ = _product($1, $3);    }
    | AExp DIV AExp { $$ = _division($1, $3);   }
    | AExp REM AExp { $$ = _rem($1, $3);        }
    | AExp POW AExp { $$ = _pow($1, $3);        }
    | '(' AExp ')'  { $$ = $2;                  }

BExp : TRUE           { $$ = _boolean("true");  }
     | FALSE          { $$ = _boolean("false"); }
     | NOT BExp       { $$ = _not($2);          }
     | BExp AND BExp  { $$ = _and($1, $3);      }
     | BExp OR   BExp { $$ = _or($1, $3);       }
     | BExp XOR  BExp { $$ = _xor($1, $3);      }
     | BExp NAND BExp { $$ = _nand($1, $3);     }
     | BExp NOR  BExp { $$ = _nor($1, $3);      }
     | BExp NXOR BExp { $$ = _nxor($1, $3);     }
     | AExp LT   AExp { $$ = _lt($1, $3);       }
     | AExp LEQ  AExp { $$ = _leq($1, $3);      }
     | AExp EQ   AExp { $$ = _eq($1, $3);       }
     | AExp GEQ  AExp { $$ = _geq($1, $3);      }
     | AExp GT   AExp { $$ = _gt($1, $3);       }
     | AExp NEQ  AExp { $$ = _neq($1, $3);      }
     | '(' BExp ')'   { $$ = $2; }



%%/*********************************************************************
 * Auxiliary functions.
 **********************************************************************/

/* Error handling function. */
int yyerror(const char *s) {
  fprintf(stdout, "%s\n", s);
  return -1;
}

/* The source file is parsed and the Abstract Syntax Tree is built.*/
void *parse(const char *source_path){
  int parse_result;
  FILE *source_file;
  
  
  /* Source file is opened. */
  if(strcmp("-", source_path) == 0){
    printf("Reading program from standard input...\n");
    source_file = stdin;
  }
  else{
    source_file = fopen(source_path, "r");
    if(source_file == NULL){
      fprintf(stderr,
              "[Parser] Unable to open file \"%s\".\n", source_path);
      exit(-1);
    }
  }
  set_source_file(source_file);
  
  
  /* The source code is parsed. */
  ast  = NULL;
  parse_result = yyparse();
  if(parse_result == 1){
    fprintf(stderr, "[Parser] Syntax error.\n");
    ast = NULL;
  }
  else if(parse_result == 2){
    fprintf(stderr, "[Parser] Memory exhaustion.\n");
    ast = NULL;
  }
  
  return ast;
}

