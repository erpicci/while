/** While Language Abstract (and Concrete) Interpreter.
 * 
 * The While language is a very simple C-like imperative language where
 * the possible operations are assignments, compositions, if and while
 * control structures and both arithmetic and boolean operations. This
 * tools offers a basic static analyzer for such a language.
 * 
 * @file main.cpp
 * @mainpage
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @version 1.0
 * @date 14/03/2014
 */

/* Header file inclusion. */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

#include "AST.h"
#include "AbstractState.h"
#include "domains/ConcreteDomain.h"
#include "domains/SignDomain.h"
#include "wrapper.h"



/* Global variable definition. */
string source_path;     /**< Path of the source file, if any. */
bool export_ast;        /**< True if a dot file representing the
                             Abstract Syntax Tree shall be created. */
string ast_path;        /**< Path to the output ast dot file. */



/** The source code is parsed.
 * Source code is parsed, and the corresponding Abstract Syntax Tree is
 * built and returned. If the specified file does not exists, source
 * code is read from the standard input. In case of error, NULL is
 * returned.
 * @param[in]  file_path     Path to the file containing the source code
 * @return     Abstract Syntax Tree of the program
 */
AST *parse(const char *file_path);



/** Program options are read from the command line.
 * @param[in]  argc          ARGument Counter
 * @param[in]  argv          ARGument Vector
 */
void parse_options(int argc, char *argv[])
{
  int i;
  
  // Global variables are initialized with their standard values.
  source_path = "-";
  export_ast  = false;
  ast_path    = "./ast.dot";
  
  for(i = 1; i < argc; i++){
    // AST export is requested.
    if((strcmp("--ast", argv[i]) == 0 || strcmp("-a", argv[i]) == 0)
       && (i+1 < argc)){
      export_ast = true;
      ast_path   = argv[++i];
    }
    
    // Helper.
    else if(strcmp("--help", argv[i]) == 0 || strcmp("-h", argv[i]) == 0){
      cout << "While Interpreter\n"
           << "----------------------------------\n"
           << "Usage: while [options] [file]\n\n"
           << "List of options:\n"
           << "  -a, --ast FILE        Abstract Syntax Tree of the program is exported in dot format to FILE\n"
           << "  -h, --help            Print this help and exit\n"
           << "\n"
           << "File:\n"
           << "  filename              Path to the program file (typically .wl)\n"
           << "  -                     Program is read from standard input\n"
           << "  (nothing)             Program is read from standard input\n"
            ;
      exit(0);
    }
    
    // Last argument, if any, is the source code file.
    else if(i == argc - 1){
      source_path = argv[i];
    }
  }
}



/** While interpreter.
 * Core of the While language abstract (and concrete) interpreter. When
 * invoking the program, the path to the file containing the source code
 * of the while program to be analized can be given as an input
 * parameter. If such parameter is not given, the program will read the
 * source code from the standard input.
 * @param[in]  argc          ARGument Counter
 * @param[in]  argv          ARGument Vector
 * @return     0 in case of success, a negative value in case of failure
 */
int main(int argc, char *argv[])
{
  AST *P;
  char **var_v;
  unsigned int var_c;
  
  
  // Checks on input.
  parse_options(argc, argv);
  
  
  // Input file is parsed, and infos about the variables are read.
  P = parse(source_path.c_str());
  var_v = NULL;  variables(&var_v, &var_c);
  if(P == NULL){
    fprintf(stderr, "[While] Nothing to be done.\n");
    return 0;
  }
  
  
  // An abstract state is created.
  
  
  // Abstract Syntax Tree is exported, if asked.
  if(export_ast){
    P->export_graphviz(ast_path.c_str());
  }
  
  
  // Concrete interpretation.
  cout << "Concrete interpretation:\n";
  AbstractState<ConcreteDomain::abstract_type> *S;
  S = new AbstractState<ConcreteDomain::abstract_type>(var_c);
  for(unsigned int i = 0; i < var_c; i++) S->insert(var_v[i]);
  P->interpret<ConcreteDomain>(S);
  
  // Sign Domain interpretation.
  cout << "Sign interpretation:\n";
  AbstractState<SignDomain::abstract_type> *Sign;
  Sign = new AbstractState<SignDomain::abstract_type>(var_c);
  for(unsigned int i = 0; i < var_c; i++) Sign->insert(var_v[i]);
  P->interpret<SignDomain>(Sign);
  
  
  // Memory free.
  delete P;
  
  
  return 0;
}

