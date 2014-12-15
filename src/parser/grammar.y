/***********************************************************************
 *  Definitions.
 **********************************************************************/
%{ // Prologue.
#include <stdio.h>
#include <string.h>

#include "../AST.hpp"

// Bison functions to be exported to flex.
int yylex(void);
int yyerror(const char *s);
int yywrap();
void set_source_file(FILE *descriptor);

// Abstract Syntax Tree.
AST *ast;
%}


/* Union representing each possible type. */
%union {
   int  integer;        // Integer value.
   char literal[32];    // Identifier or textual information.
   AST *tree;           // Reference to abstract syntax (sub) tree.
}; 



/* Declaration of tokens and operator precedences and associativity. */
%token <integer> NUM
%token <literal> VAR

%token ASN SKIP SEQ IF THEN WHILE DO
%nonassoc ELSE

%left  PLUS MINUS
%left  STAR SLASH PERC
%right CAP

%token TRUE FALSE
%right NOT
%left  AND OR XOR NAND NOR XNOR
%left  IMP RIMP
%left  EQ NEQ LT LEQ GEQ GT

%token PRINT INPUT
%token LPAR RPAR

/* Type of each possible production. */
%type <tree> Prog Stms Stm AExp BExp



%%/*********************************************************************
 * Rules.
 **********************************************************************/

Prog: Stms              { ast = $1; }
    |                   { ast = NULL; }

Stms: Stm SEQ           { $$ = $1; }
    | Stms Stm SEQ      { $$ = new AST(AST::Seq, $1, $2); }


Stm: VAR ASN AExp  { $$ = new AST(AST::Asn, new AST(AST::Var, $1), $3); }
   | SKIP               { $$ = new AST(AST::Skp); }
   | IF BExp
     THEN Stm
     ELSE Stm           { $$ = new AST(AST::If, $2, $4, $6); }
   | WHILE BExp DO Stm  { $$ = new AST(AST::Whl, $2, $4); } 
   | PRINT AExp         { $$ = new AST(AST::Prn, $2); }
   | INPUT VAR          { $$ = new AST(AST::In, new AST(AST::Var, $2)); }
   | LPAR Stms RPAR     { $$ = $2; }

AExp: NUM               { $$ = new AST(AST::Num, $1); }
    | VAR               { $$ = new AST(AST::Var, $1); }
    | PLUS AExp         { $$ = new AST(AST::Id, $2); }
    | MINUS AExp        { $$ = new AST(AST::Opp, $2); }
    | AExp PLUS AExp    { $$ = new AST(AST::Sum, $1, $3); }
    | AExp MINUS AExp   { $$ = new AST(AST::Sub, $1, $3); }
    | AExp STAR AExp    { $$ = new AST(AST::Mul, $1, $3); }
    | AExp SLASH AExp   { $$ = new AST(AST::Div, $1, $3); }
    | AExp PERC AExp    { $$ = new AST(AST::Rem, $1, $3); }
    | AExp CAP AExp     { $$ = new AST(AST::Pow, $1, $3); }
    | LPAR AExp RPAR    { $$ = $2; }

BExp: TRUE              { $$ = new AST(AST::Bool, true); }
    | FALSE             { $$ = new AST(AST::Bool, false); }
    | NOT BExp          { $$ = new AST(AST::Not, $2); }
    | BExp AND BExp     { $$ = new AST(AST::And, $1, $3); }
    | BExp OR   BExp    { $$ = new AST(AST::Or, $1, $3); }
    | BExp XOR  BExp    { $$ = new AST(AST::Xor, $1, $3); }
    | BExp NAND BExp    { $$ = new AST(AST::Nand, $1, $3); }
    | BExp NOR  BExp    { $$ = new AST(AST::Nor, $1, $3); }
    | BExp XNOR BExp    { $$ = new AST(AST::Xnor, $1, $3); }
    | BExp IMP  BExp    { $$ = new AST(AST::Or, new AST(AST::Not, $1), $3); }
    | BExp RIMP BExp    { $$ = new AST(AST::Or, new AST(AST::Not, $3), $1); }
    | AExp LT   AExp    { $$ = new AST(AST::Lt, $1, $3); }
    | AExp LEQ  AExp    { $$ = new AST(AST::Leq, $1, $3); }
    | AExp EQ   AExp    { $$ = new AST(AST::Eq, $1, $3); }
    | AExp GEQ  AExp    { $$ = new AST(AST::Geq, $1, $3); }
    | AExp GT   AExp    { $$ = new AST(AST::Gt, $1, $3); }
    | AExp NEQ  AExp    { $$ = new AST(AST::Neq, $1, $3); }
    | LPAR BExp RPAR    { $$ = $2; }



%%/*********************************************************************
 * Auxiliary functions.
 **********************************************************************/

/* Error handling function. */
int yyerror(const char *s) {
  cout << s << endl;
  return -1;
}

/* The source file is parsed and the Abstract Syntax Tree is built.*/
void *parse(const char *source_path){
  int parse_result;
  FILE *source_file;
  
  
  /* Source file is opened. */
  if(strcmp("-", source_path) == 0){
    cout << "Reading from standard input. Type Ctrl+D to terminate..."
         << endl;
    source_file = stdin;
  }
  else{
    source_file = fopen(source_path, "r");
    if(source_file == NULL){
      cerr << "[Parser]: Unable to open file \"" << source_path << "\"."
           << endl;
      exit(-1);
    }
  }
  set_source_file(source_file);
  
  
  /* The source code is parsed. */
  ast  = NULL;
  parse_result = yyparse();
  if(parse_result == 1){
    cerr << "[Parser]: Syntax error." << endl;
    ast = NULL;
  }
  else if(parse_result == 2){
    cerr << "[Parser]: Memory exhaustion." << endl;
    ast = NULL;
  }
  
  return ast;
}
