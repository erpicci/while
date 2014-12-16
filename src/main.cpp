/** While Language Abstract Interpreter.
 * The While language is a very simple C-like imperative language where
 * the possible operations are assignments, compositions, if-then-else
 * branches, while loops and arithmetic and boolean expressions. This
 * tool offers a basic static analyzer for such a language.
 * 
 * @file main.cpp
 * @mainpage
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "domains.hpp"
#include "AbstractState.hpp"
#include "AST.hpp"

using namespace std;


// Global variables.
string source_path = "-";         ///< Path of the source file, if any
bool export_ast    = false;       ///< True if a dot file representing the
                                  ///<  Abstract Syntax Tree shall be created
string ast_path    = "ast.dot";   ///< Path to the output ast dot file



/** Source code is parsed.
 * @param[in]  file_path     Path to the source file
 * @retval     AST *         Abstract syntax tree of the program
 */
AST *parse(const char *file_path);



/** Program options are read from the command line.
 * @param[in]  argc          ARGument Counter
 * @param[in]  argv          ARGument Vector
 */
void init(int argc, char *argv[]);



/** While interpreter.
 * Core of the While language abstract interpreter. When invoking the
 * program, the path to the file containing the source code of the while
 * program to be analized can be given as an input parameter.
 * If such parameter is not given, the program will read the source code
 * from the standard input.
 * @param[in]  argc          ARGument Counter
 * @param[in]  argv          ARGument Vector
 * @retval     int           EXIT_SUCCESS in case of success,
 *                           EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[])
{
  AST *P;
  
  // Parse options.
  init(argc, argv);
  
  // Abstract Syntax Tree is created.
  P = parse(source_path.c_str());
  if(NULL == P){
    cerr << "[While]: Nothing to be done." << endl;
    return EXIT_SUCCESS;
  }
  
  // Abstract Syntax Tree is exported, if asked.
  if(export_ast){
    P->toGraphviz(ast_path.c_str());
  }
  
  // Concrete execution.
  //AbstractState<int> concreteState = P->execute();
  //cout << "Concrete domain:   ";
  //concreteState.dump();
  
  // Abstract executions.
  AbstractState<Sign> signS = P->interpret<Sign>();
  cout << "Sign domain:       ";
  signS.dump();
  
  AbstractState<Interval> intervalS = P->interpret<Interval>();
  cout << "Interval domain:   ";
  intervalS.dump();
  
  AbstractState<SInterval> sintervalS = P->interpret<SInterval>();
  cout << "S-Interval domain: ";
  sintervalS.dump();

  AbstractState< Modulo<2> > modulo2S = P->interpret< Modulo<2> >();
  cout << "Modulo 2 domain:   ";
  modulo2S.dump();
  
  AbstractState< Modulo<3> > modulo3S = P->interpret< Modulo<3> >();
  cout << "Modulo 3 domain:   ";
  modulo3S.dump();
  
  delete P;
  
  return EXIT_SUCCESS;
}



/** Program options are read from the command line.
 * @param[in]  argc          ARGument Counter
 * @param[in]  argv          ARGument Vector
 */
void init(int argc, char *argv[])
{
  int i;
  
  for(i = 1; i < argc; i++){
    // AST export is requested.
    if((strcmp("--ast", argv[i]) == 0 || strcmp("-a", argv[i]) == 0)
       && (i+1 < argc)){
      export_ast = true;
      ast_path   = argv[++i];
    }
    
    // Helper.
    else if(strcmp("--help", argv[i]) == 0 || strcmp("-h", argv[i]) == 0){
      cout
      << "While Interpreter\n"
      << "----------------------------------\n"
      << "Usage: while [options] [file]\n\n"
      << "List of options:\n"
      << "  -a, --ast FILE   AST is exported in dot format to FILE\n"
      << "  -h, --help       Print this help and exit\n"
      << endl
      << "File:\n"
      << "  filename         Path to the program file (typically .wl)\n"
      << "  -                Program is read from standard input\n"
      << "  (nothing)        Program is read from standard input\n"
      ;
      exit(0);
    }
    
    // Last argument, if any, is the source code file.
    else if(i == argc - 1){
      source_path = argv[i];
    }
  }
}
