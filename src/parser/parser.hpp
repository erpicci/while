/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     VAR = 259,
     ASN = 260,
     SKIP = 261,
     SEQ = 262,
     IF = 263,
     THEN = 264,
     WHILE = 265,
     DO = 266,
     ELSE = 267,
     MINUS = 268,
     PLUS = 269,
     PERC = 270,
     SLASH = 271,
     STAR = 272,
     CAP = 273,
     TRUE = 274,
     FALSE = 275,
     NOT = 276,
     XNOR = 277,
     NOR = 278,
     NAND = 279,
     XOR = 280,
     OR = 281,
     AND = 282,
     RIMP = 283,
     IMP = 284,
     GT = 285,
     GEQ = 286,
     LEQ = 287,
     LT = 288,
     NEQ = 289,
     EQ = 290,
     PRINT = 291,
     INPUT = 292,
     LPAR = 293,
     RPAR = 294
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 22 "parser/grammar.y"

   int  integer;        // Integer value.
   char literal[32];    // Identifier or textual information.
   AST *tree;           // Reference to abstract syntax (sub) tree.



/* Line 2068 of yacc.c  */
#line 97 "parser/parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


