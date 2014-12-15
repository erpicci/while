/** Abstract syntax tree.
 * Class handling an abstract syntax tree, built by the parser. Such a
 * tree can be traversed to perform an abstract interpretation.
 * 
 * @file AST.cpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "AST.hpp"


/** Constructor of a 0-ary statement abstract syntax node.
 * 0-ary statements are: skip (Skp).
 * @param[in]  type        Type of the statement
 */
AST::AST(StmType type)
{
  switch(type){
    case Skp:
      this->nodeID  = ++AST::lastID;
      this->type    = Stm;
      this->parent  = NULL;
      this->opcode.statement = type;
      break;
    default:
      cerr << "[AST]: Wrong statement type." << endl;
  }
}


/** Constructor of a unary statement abstract syntax node.
 * Unary statements are: print (Prn), input (In).
 * @param[in]  type        Type of the stament
 * @param[in]  first       Subtree representing the argument
 */
AST::AST(StmType type, AST *first)
{
  switch(type){
    case Prn:
    case In:
      this->nodeID  = ++AST::lastID;
      this->type    = Stm;
      this->parent  = NULL;
      this->sons.push_back(first);
      this->opcode.statement = type;
      first->parent = this;
      break;
    default:
      cerr << "[AST]: Wrong statement type." << endl;
  }
}


/** Constructor of a binary statement abstract syntax node.
 * Binary statements are: assignment (Asn), sequential composition
 * (Seq), while loop (Whl).
 * @param[in]  type        Type of the statement
 * @param[in]  first       Subtree representing the first argument
 * @param[in]  second      Subtree representing the second argument
 */
AST::AST(StmType type, AST *first, AST *second)
{
  switch(type){
    case Asn:
    case Seq:
    case Whl:
      this->nodeID  = ++AST::lastID;
      this->type    = Stm;
      this->parent  = NULL;
      this->sons.push_back(first);
      this->sons.push_back(second);
      this->opcode.statement = type;
      first->parent = this;
      second->parent= this;
      break;
    default:
      cerr << "[AST]: Wrong statement type." << endl;
  }
}


/** Constructor of a ternary statement abstract syntax node.
 * Ternary statements are: if-then-else branch (If).
 * @param[in]  type        Type of the statement
 * @param[in]  first       Subtree representing the first argument
 * @param[in]  second      Subtree representing the second argument
 * @param[in]  third       Subtree representing the third argument
 */
AST::AST(StmType type, AST *first, AST *second, AST *third)
{
  switch(type){
    case If:
      this->nodeID  = ++AST::lastID;
      this->type    = Stm;
      this->parent  = NULL;
      this->sons.push_back(first);
      this->sons.push_back(second);
      this->sons.push_back(third);
      this->opcode.statement = type;
      first->parent = this;
      second->parent= this;
      third->parent = this;
      break;
    default:
      cerr << "[AST]: Wrong statement type." << endl;
  }
}


/** Constructor of a numeric constant abstract syntax node.
 * Numeric constant expressions are: num (Num).
 * @param[in]  type        Type of the arithmetic expression
 * @param[in]  num         Constant, integer value
 */
AST::AST(AExpType type, int num)
{
  switch(type){
    case Num:
      this->nodeID  = ++AST::lastID;
      this->type    = AExp;
      this->parent  = NULL;
      this->value.num = num;
      this->opcode.arithmetic = type;
      break;
    default:
      cerr << "[AST]: Wrong arithmetic type." << endl;
  }
}


/** Constructor of a variable synatax node.
 * Varibales are: var (Var).
 * @param[in]  type        Type of the arithmetic expression
 * @param[in]  var         Name of the variable
 */
AST::AST(AExpType type, string var)
{
  switch(type){
    case Var:
      this->nodeID  = ++AST::lastID;
      this->type    = AExp;
      this->parent  = NULL;
      this->value.var = new string(var);
      this->opcode.arithmetic = type;
      break;
    default:
      cerr << "[AST]: Wrong arithmetic type." << endl;
  }
}


/** Constructor of an unary arithmetic expression abstract syntax node.
 * Unary arithmetic expressions are: identity (Id), opposite (Opp).
 * @param[in]  type        Type of the arithmetic expression
 * @param[in]  a           Operand
 */
AST::AST(AExpType type, AST *a)
{
  switch(type){
    case Id:
    case Opp:
      this->nodeID  = ++AST::lastID;
      this->type    = AExp;
      this->parent  = NULL;
      this->sons.push_back(a);
      this->opcode.arithmetic = type;
      a->parent     = this;
      break;
    default:
      cerr << "[AST]: Wrong arithmetic type." << endl;
  }
}


/** Constructor of a binary arithmetic expression abstract syntax node.
 * Binary arithmetic expressions are: sum (Sum), subtraction (Sub),
 * multiplication (Mul), integer division (Div), remainder of the
 * integer division (Rem), raise to the power (Pow).
 * @param[in]  type        Type of the arithmetic expression
 * @param[in]  a1          First operand
 * @param[in]  a2          Second operand
 */
AST::AST(AExpType type, AST *a1, AST *a2)
{
  switch(type){
    case Sum:
    case Sub:
    case Mul:
    case Div:
    case Rem:
    case Pow:
      this->nodeID  = ++AST::lastID;
      this->type    = AExp;
      this->parent  = NULL;
      this->sons.push_back(a1);
      this->sons.push_back(a2);
      this->opcode.arithmetic = type;
      a1->parent     = this;
      a2->parent     = this;
      break;
    default:
      cerr << "[AST]: Wrong arithmetic type." << endl;
  }
}


/** Constructor of a constant, boolean value.
 * Constant, boolean values are: boolean (Bool).
 * @param[in]  type        Type of the boolean value
 * @param[in]  boolean     Boolean value
 */
AST::AST(BExpType type, bool boolean)
{
  switch(type){
    case Bool:
      this->nodeID  = ++AST::lastID;
      this->type    = BExp;
      this->parent  = NULL;
      this->opcode.boolean = type;
      this->value.boolean  = boolean;
      break;
    default:
      cerr << "[AST]: Wrong boolear type." << endl;
  }
}


/** Constructor of a unary boolean expression abstract syntax node.
 * Unary boolean expressions are: logical negation (Not).
 * @param[in]  type        Type of the boolean expression
 * @param[in]  b           Operand
 */
AST::AST(BExpType type, AST *b)
{
  switch(type){
    case Not:
      this->nodeID  = ++AST::lastID;
      this->type    = BExp;
      this->parent  = NULL;
      this->sons.push_back(b);
      this->opcode.boolean = type;
      b->parent     = this;
      break;
    default:
      cerr << "[AST]: Wrong boolear type." << endl;
  }
}


/** Constructor of a binary boolean expression abstract syntax node.
 * Binary boolean expressions are: logical conjunction (And), logical
 * disjunction (Or), logical exclusive disjunction (Xor), negated
 * conjunction (Nand), negated disjunction (Nor), negated exclusive
 * disjunction (Xnor), 'less than' comparison (Lt), 'less than or
 * equal to' comparison, 'equal to' comparison, 'greater than or equal
 * to' comparison, 'greater than' comparison, 'not equal to' comparison.
 * @param[in]  type        Type of the boolean expression
 * @param[in]  b1          First operand
 * @param[in]  b2          Second operand
 */
AST::AST(BExpType type, AST *b1, AST *b2)
{
  switch(type){
    case And:
    case Or:
    case Xor:
    case Nand:
    case Nor:
    case Xnor:
    case Lt:
    case Leq:
    case Eq:
    case Geq:
    case Gt:
    case Neq:
      this->nodeID  = ++AST::lastID;
      this->type    = BExp;
      this->parent  = NULL;
      this->sons.push_back(b1);
      this->sons.push_back(b2);
      this->opcode.boolean = type;
      b1->parent    = this;
      b2->parent    = this;
      break;
    default:
      cerr << "[AST]: Wrong boolean type." << endl;
  }
}


/** Destructor of an abstract syntax tree. */
AST::~AST()
{
  vector<AST*>::iterator it;
  
  // If node contains an identifier, it is deallocated.
  if(type == AExp && opcode.arithmetic == Var){
    delete value.var;
  }
  
  // Every sub-tree rooted in the current node is destroied.
  for(it = sons.begin(); it != sons.end(); ++it){
    if((*it)->parent == this){
      delete *it;
    }
  }
}


/** A textual representation of the node is provided.
 * @retval     string      String representing the node
 */
string AST::toString()
{
  char str[32];
  
  switch(type){
    case Stm: switch(opcode.statement){
      case Asn: return ":=";
      case Skp: return "skip";
      case Seq: return ";";
      case If:  return "if-then-else";
      case Whl: return "while";
      case Prn: return "print";
      case In:  return "input";
      default:  return "Unrecognized\\nstatement";
    }
    
    case AExp: switch(opcode.arithmetic){
      case Num:
        sprintf(str, "Num\\n%d", value.num);
        return str;
      case Var: return "Var\\n" + *(value.var);
      case Id:  return "AExp\\n+";
      case Opp: return "AExp\\n-";
      case Sum: return "AExp\\n+";
      case Sub: return "AExp\\n-";
      case Mul: return "AExp\\n*";
      case Div: return "AExp\\n/";
      case Rem: return "AExp\\n%";
      case Pow: return "AExp\\n^";
      default:  return "Unrecognized\\narithmetic expression";
    }
    
    case BExp: switch(opcode.boolean){
      case Bool:
        sprintf(str, "Bool\\n%s", value.boolean ? "true" : "false");
        return str;
      case And: return "BExp\\nand";
      case Or:  return "BExp\\nor";
      case Xor: return "BExp\\nxor";
      case Nand:return "BExp\\nnand";
      case Nor: return "BExp\\nnor";
      case Xnor:return "BExp\\nxnor";
      case Lt:  return "BExp\\n<";
      case Leq: return "BExp\\n<=";
      case Eq:  return "BExp\\n=";
      case Geq: return "BExp\\n>=";
      case Gt:  return "BExp\\n>";
      case Neq: return "BExp\\n<>";
      default:  return "Unrecognized\\nboolean expression";
    }
    
    default:
      return "Unrecognized node type.";
  }
}


/** Abstract syntax tree is exported to graphviz.
 * The abstract syntax tree rooted in the current node is esported
 * into a file which can later be compiled using graphviz.
 * @param[in]  filename      Path to the output file
 */
void AST::toGraphviz(const char *filename)
{
  ofstream output;
  vector<AST *> nodeStack;
  vector<AST *>::iterator rit;
  
  // Output file is open.
  output.open(filename);
  if(!output.is_open()){
    cerr << "[AST::toGraphviz] Error while opening file: "
         << filename << "." << endl;
    return;
  }
  
  // Graphviz header is written.
  output
  << "/** Automatically generated by While for Graphviz.\n"
  << " * Compile this file with `dot -Tpng -O " << filename << "`\n"
  << " * or any other option you like. See `man dot` for information\n"
  << " */"                          << endl
  << "strict digraph AST{"          << endl
  << "  /* Style. */"               << endl
  << "  splines = true;"            << endl
  << "  layout  = dot;"             << endl
  << "  bgcolor = \"#FFFFFF\";"     << endl
  << "  "                           << endl
  << "  node ["                     << endl
  << "    fontname  = \"Times\","   << endl
  << "    fontcolor = \"#333333\"," << endl
  << "    color     = \"#333333\"," << endl
  << "    style     = \"solid\""    << endl
  << "  ];"                         << endl
  << "  edge ["                     << endl
  << "    fontname  =\"Times\","    << endl
  << "    fontcolor =\"#222222\","  << endl
  << "    color     =\"#222222\","  << endl
  << "    arrowhead =\"open\""      << endl
  << "  ];"                         << endl
  << "  "                           << endl
  << "  /* Nodes and arcs. */"      << endl
  ;
  
  // Every node and arc are written trhough a in-depth visit.
  nodeStack.push_back(this);
  while(!nodeStack.empty()){
    AST *node = nodeStack.back();
    nodeStack.pop_back();
    vector<AST*> sons = node->sons;
    string label;
    
    // Current node is visited.
    label = "\"" + node->toString() + "\"";
    output << "  " << node->nodeID << "[label=" << label << "]" << endl;
    
    // Arcs exiting form the current node are written, and sons of the
    // current node are pushed into the stack to be visited.
    for(rit = sons.begin(); rit != sons.end(); ++rit){
      nodeStack.push_back(*rit);
      output << "  " << node->nodeID << "->" << (*rit)->nodeID << endl;
    }
  }
  
  // Output file is closed.
  output << "}" << endl;
  output.close();
}


/** Concrete excecution is performed starting from the bottom state.
 * @retval     AbstractState State containing the result of the
 *                         (concrete) compupation
 */
AbstractState<int> AST::execute()
{
  return execute(AbstractState<int>());
}


/** Concrete excecution is performed starting from the given state.
 * @retval     AbstractState State containing the result of the
 *                         (concrete) compupation
 */
AbstractState<int> AST::execute(AbstractState<int> state)
{
  int input;
  
  // If node is not a statement, just return the curren state.
  if(type != Stm){ return state; }
  
  // Correct action is taken depending on the statement type.
  switch(opcode.statement){
    case Asn:
      state.store(*(sons[0]->value.var), sons[1]->A(state));
      return state;
    
    case Skp:
      return state;
    
    case Seq:
      return sons[1]->execute(sons[0]->execute(state));
    
    case If:
      return sons[0]->B(state)
           ? sons[1]->execute(state)
           : sons[2]->execute(state);
    
    case Whl:
      while(sons[0]->B(state)){
        state = sons[1]->execute(state);
      }
      return state;
    
    case Prn:
      cout << (sons[0]->A(state)) << endl;
      return state;
    
    case In:
      cout << "> " << *(sons[0]->value.var) << " := ";
      cin >> input;
      state.store(*(sons[0]->value.var), input);
      return state;
    
    default:
      cerr << "[AST::execute]: Unrecognized statement opcode value: "
           << opcode.statement << "." << endl;
      return AbstractState<int>();
  }
}


/** An arithmetic expression is evaluated in the given state.
 * Evaluation is performed on the concrete values.
 * @param[in]  state       Concrete state where expression is
 *                         evaluated
 * @retval     int         Evaluated arithmetic expression
 */
int AST::A(AbstractState<int> state)
{
  int i, pow;
  
  // If node is not an arithmetic expression, just return 0.
  if(type != AExp){ return 0; }
  
  // Correct action is taked depending on the type of operation.
  switch(opcode.arithmetic){
    case Num: return value.num;
    case Var: return state.load(*(value.var));
    case Id:  return sons[0]->A(state);
    case Opp: return -(sons[0]->A(state));
    case Sum: return sons[0]->A(state) + sons[1]->A(state);
    case Sub: return sons[0]->A(state) - sons[1]->A(state);
    case Mul: return sons[0]->A(state) * sons[1]->A(state);
    case Div: return sons[0]->A(state) / sons[1]->A(state);
    case Rem: return sons[0]->A(state) % sons[1]->A(state);
    case Pow:
      pow = 1;
      for(i = 0; i < sons[1]->A(state); ++i){
        pow *= sons[0]->A(state);
      }
      return pow;
    default:
      cerr << "[AST::A]: Unrecognized arithmetic opcode value: "
           << opcode.statement << "." << endl;
      return 0;
  }
}


/** Boolean expression is evaluated in the given state.
 * Evaluation is perfomed on the concrete values.
 * @param[in]  state       Initial state
 * @retval     bool        True if and only if the boolean expression
 *                         evaluates to true
 */
bool AST::B(AbstractState<int> state)
{
  // If node is not a boolean expression, just return false.
  if(type != BExp){ return false; }
  
  // Correct action is taked depending on the type of expression.
  switch(this->opcode.boolean)
  {
    case Bool: return value.boolean;
    case Not:  return !(sons[0]->B(state));
    
    case Lt:   return sons[0]->A(state) <  sons[1]->A(state);
    case Leq:  return sons[0]->A(state) <= sons[1]->A(state);
    case Eq:   return sons[0]->A(state) == sons[1]->A(state);
    case Geq:  return sons[0]->A(state) >= sons[1]->A(state);
    case Gt:   return sons[0]->A(state) >  sons[1]->A(state);
    case Neq:  return sons[0]->A(state) != sons[1]->A(state);
    
    case And:  return sons[0]->B(state) && sons[1]->B(state);
    case Or:   return sons[0]->B(state) || sons[1]->B(state);
    case Xor:
      return (!(sons[0]->B(state)) && sons[1]->B(state))
          || (sons[0]->B(state) && !(sons[1]->B(state)));
    case Nand: return !(sons[0]->B(state) && sons[1]->B(state));
    case Nor:  return !(sons[0]->B(state) || sons[1]->B(state));
    case Xnor:
      return !((!(sons[0]->B(state)) && sons[1]->B(state))
          || (sons[0]->B(state) && !(sons[1]->B(state))));
    default:
      cerr << "[AST::B]: Unrecognized boolean opcode value: "
           << opcode.statement << "." << endl;
      return false;
  }
}


unsigned int AST::lastID = 0;


/** Boolean expression is negated.
 * Boolean expression associated to the current node is reversed and
 * returned into a new sub-tree.
 * For instance, if current node contains a 'less than' comparison
 * between arithmetic expressions a1 and a2, a new sub-tree is created,
 * whose root is a node representing a 'greater than or equal to'
 * comparison between a1 and a2.
 * @retval     AST         Negated boolean expression
 */
AST AST::neg()
{
  BExpType notOpcode;
  AST falseBExp = AST(Bool, false);
  
  // If node is not a boolean expression, just return a constant false
  // node.
  if(type != BExp){ return falseBExp; }
  
  // New opcode is detected.
  switch(opcode.boolean){
    case Bool: notOpcode = Bool; break;
    case Not:  notOpcode = Not;  break;
    case Lt:   notOpcode = Geq;  break;
    case Leq:  notOpcode = Gt;   break;
    case Eq:   notOpcode = Neq;  break;
    case Geq:  notOpcode = Lt;   break;
    case Gt:   notOpcode = Leq;  break;
    case Neq:  notOpcode = Eq;   break;
    case And:  notOpcode = Nand; break;
    case Or:   notOpcode = Nor;  break;
    case Xor:  notOpcode = Xnor; break;
    case Nand: notOpcode = And;  break;
    case Nor:  notOpcode = Or;   break;
    case Xnor: notOpcode = Xor;  break;
    default:
      cerr << "[AST::neg]: Unrecognized boolean opcode value: "
           << opcode.arithmetic << "." << endl;
      return falseBExp;
  }
  
  
  // A new sub-tree is created.
  switch(notOpcode){
    case Bool:
      return AST(Bool, !value.boolean);
    
    case Not:
      return sons[0]->neg();
    
    case Lt:   case Leq:  case Eq:   case Geq:  case Gt:   case Neq:
    case And:  case Or:   case Xor:  case Nand: case Nor:  case Xnor:
    {
      AST negation = AST(notOpcode, sons[0], sons[1]);
      sons[0]->parent = this;  sons[1]->parent = this;
      return negation;
    }
    
    default:
      cerr << "[AST::neg]: Unrecognized boolean opcode value: "
           << opcode.arithmetic << "." << endl;
      return falseBExp;
  }
}
