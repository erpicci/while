/** Template for a ternary abstract syntax tree.
 * 
 * Class template to handle ternary trees, to be used for the
 * abstract interpreter for the While language.
 * 
 * @file AST.h
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @version 0.9
 * @date 09/03/2014
 */


#ifndef _AST_H_
#define _AST_H_

/* Header file inclusion. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "AbstractState.h"


/* Namespaces. */
using namespace std;



/** Template used to represent a ternary tree.
 * Trees are ternary beacuse the maximum number of non terminals in a
 * production of the While language is three, hence the maximum number
 * of sons a tree can have is limited to three. Having such a (low)
 * upper bound makes reasonable the idea to allocate, for each node, an
 * array of three elements on the stack, in order to simplify the memory
 * management and avoid dynamic memory operation.
 * The type of the tree is parametric, and it represent the abstract
 * domain.
 */
class AST
{
public:
  /** Type of node. */
  typedef enum{
    ASN,       /**< Assignment statement. */
    SKP,       /**< Skip statement. */
    CAT,       /**< Concatenation statement. */
    IF,        /**< If-then-else statement. */
    WHL,       /**< While statement. */
    NUM,       /**< Numeric constant. */
    VAR,       /**< Variable. */
    AOP,       /**< Arithmetic binary operation. */
    BOOL,      /**< Boolean constant. */
    NOT,       /**< Boolean negation. */
    BOP,       /**< Boolean binary operation. */
    CMP,       /**< Arithmetic binary comparison. */
    PRN        /**< Print statement. */
  } node_type;
  
  /** Type of an arithmetic binary operator. */
  typedef enum{
    SUM,       /**< Arithmetic sum. */
    DIF,       /**< Arithmetic difference. */
    MUL,       /**< Arithmetic product. */
    DIV,       /**< Integer division. */
    REM,       /**< Rest of the integer divisio. */
    POW        /**< Integer power. */
  } a_opcode;
  
  /** Type of a boolean binary operator. */
  typedef enum{
    AND,       /**< Boolean 'and' operator. */
    OR,        /**< Boolean 'or' operator. */
    XOR,       /**< Boolean 'exclusive or' operator. */
    NAND,      /**< Boolean 'not and' operator. */
    NOR,       /**< Boolean 'nor or' operator. */
    NXOR       /**< Boolean 'not exclusive or' operator. */
  } b_opcode;
  
  /** Type of a binary comparison operator. */
  typedef enum{
    LT,        /**< 'Less than' binary comparison operator. */
    LEQ,       /**< 'Less or equal' binary comparison operator. */
    EQ,        /**< 'Equal to' binary comparison operator. */
    GEQ,       /**< 'Greater or equal' binary comparison operator. */
    GT,        /**< 'Greater than' binary comparison operator. */
    NEQ        /**< 'Not equal' binary comparison operator. */
  } c_opcode;
  
  
  
  /** Constructor.
   * A node is created storing informations about its type. This
   * constructor can be used for the 'skip' instruction.
   * @param[in]  type        Type of the node
   * @return     A new node
   */
  AST(node_type type)
  {
    this->type = type;
    this->sons = 0;
  }
  
  
  /** Constructor.
   * A node is created storing informations about its type and a
   * literal. This constructor can be used for variable names and
   * boolean constants
   * @param[in]  type        Type of the node
   * @param[in]  literal     Textual information associated to the node
   * @return     A new node
   */
  AST(node_type type, const char literal[])
  {
    this->type = type;
    strcpy(this->literal, literal);
    this->sons = 0;
  }
  
  
  /** Constructor.
   * A node is created storing informations about its type value. This
   * constructor can be used for numeric constants.
   * @param[in]  type        Type of the node
   * @param[in]  value       Value associated to the node
   * @return     A new node
   */
  AST(node_type type, int value)
  {
    this->type = type;
    this->value = value;
    this->sons = 0;
  }
  
  
  /** Constructor.
   * A node representing an unary operator is created storing
   * informations about its type and its operand. This constructor can
   * be used for unary constructs: 'not' and 'print'.
   * @param[in]  type        Type of the node
   * @param[in]  operand     Operand for this unary operator
   * @return     A new node
   */
  AST(node_type type, AST *operand)
  {
    this->type = type;
    this->subtrees[0] = operand;
    this->sons = 1;
  }
  
  
  /** Constructor.
   * A node representing a binary operator is created storing
   * informations about its type, operands and operator. This
   * constructor can be used for arithmetic binary operations: sum,
   * difference, product, division, rest of division, power.
   * @param[in]  type        Type of the node
   * @param[in]  op          Opcode representing a binary operator
   * @param[in]  first_op    First operand for this binary operator
   * @param[in]  second_op   Second operand for this binary operator
   * @return     A new node
   */
  AST(node_type type, a_opcode op, AST *first_op, AST *second_op)
  {
    this->type = type;
    this->a_op = op;
    this->subtrees[0] = first_op;
    this->subtrees[1] = second_op;
    this->sons = 2;
  }
  
  
  /** Constructor.
   * A node representing a binary operator is created storing
   * informations about its type, operands and operator. This
   * constructor can be used for boolean binary operations: and, or,
   * exclusive or, not and, not or, not exclusive or.
   * @param[in]  type        Type of the node
   * @param[in]  op          Opcode representing a binary operator
   * @param[in]  first_op    First operand for this binary operator
   * @param[in]  second_op   Second operand for this binary operator
   * @return     A new node
   */
  AST(node_type type, b_opcode op, AST *first_op, AST *second_op)
  {
    this->type = type;
    this->b_op = op;
    this->subtrees[0] = first_op;
    this->subtrees[1] = second_op;
    this->sons = 2;
  }
  
  
  /** Constructor.
   * A node representing a binary operator is created storing
   * informations about its type, operands and operator. This
   * constructor can be used for binary comparisons: less than, less or
   * equal, equal, greater or equal, greater than, not equal.
   * @param[in]  type        Type of the node
   * @param[in]  op          Opcode representing a binary operator
   * @param[in]  first_op    First operand for this binary operator
   * @param[in]  second_op   Second operand for this binary operator
   * @return     A new node
   */
  AST(node_type type, c_opcode op, AST *first_op, AST *second_op)
  {
    this->type = type;
    this->c_op = op;
    this->subtrees[0] = first_op;
    this->subtrees[1] = second_op;
    this->sons = 2;
  }
  
  
  /** Constructor.
   * A node representing a binary operator is created storing
   * informations about its type and operands. This constructor can be
   * used for binary constructs: concatenation and while.
   * @param[in]  type        Type of the node
   * @param[in]  first_op    First operand for this binary operator
   * @param[in]  second_op   Second operand for this binary operator
   * @return     A new node
   */
  AST(node_type type, AST *first_op, AST *second_op)
  {
    this->type = type;
    this->subtrees[0] = first_op;
    this->subtrees[1] = second_op;
    this->sons = 2;
  }
  
  
  /** Constructor.
   * A node representing a ternary operator is created storing
   * informations about its type and operands. This constructor can be
   * used for the ternary construct if-then-else.
   * @param[in]  type        Type of the node
   * @param[in]  first_op    First operand for this ternary operator
   * @param[in]  second_op   Second operand for this ternary operator
   * @param[in]  third_op    Third operand for this ternary operator
   * @return     A new node
   */
  AST(node_type type, AST *first_op, AST *second_op, AST *third_op)
  {
    this->type = type;
    this->subtrees[0] = first_op;
    this->subtrees[1] = second_op;
    this->subtrees[2] = third_op;
    this->sons = 3;
  }
  
  
  
  /** Number of nodes in the subtree is returned.
   * The number of nodes in the subtree rooted in the current node is
   * returned, including the root node itself.
   * @return     Number of nodes in the subtree
   */
  unsigned int nodes(void)
  {
    unsigned int nodes, i;
    
    nodes = 1;
    for(i = 0; i < this->sons; i++){
      nodes += this->subtrees[i]->nodes();
    }
    
    return nodes;
  }
  
  
  
  /** Number of edges is the subtree is returned.
   * The number of edges in the subtree rooted in the current node is
   * returned.
   * @return     Number of edges in the subtree
   */
  inline unsigned int edges(void)
  {
    return this->nodes() - 1;
  }
  
  
  
  /** The abstract tree is interepreted.
   * The subtree rooted in the current node is interpreted, according to
   * a given abstract state and a given abstract domain.
   * @param[in, out] S Abstract state in which operate
   * @return         Modified abstract state
   */
  template <class T>
  AbstractState<typename T::abstract_type> *
  interpret(AbstractState<typename T::abstract_type> *S)
  {
    switch(this->type){
      case ASN:
        T::Assignment(this->subtrees[0]->literal,
                      this->subtrees[1]->arithmetic_op<T>(S),
                      S);
        return S;
      
      case SKP:
        T::Skip();
        return S;
      
      case CAT:
        T::Cat(this->subtrees[0], this->subtrees[1], S);
        return S;
      
      case IF:
        T::If(this->subtrees[0]->boolean_op<T>(S),
              this->subtrees[1],
              this->subtrees[2],
              S);
        return S;
      
      case WHL:
        T::While(this->subtrees[0],
                 this->subtrees[1],
                 S);
        return S;
      
      case PRN:
        T::Print(this->subtrees[0]->arithmetic_op<T>(S));
        return S;
      
      default:
        fprintf(stderr,
          "[AST::interpret] Something really bad happened.\n");
        return S;
    }
  }
  
  
  
  /** The Arithmetic Expression is interepreted.
   * The subtree corresponding to an arithmetic expression rooted in the
   * current node is interpreted, according to a given abstract state
   * and a given abstract domain. This typically correspond to some kind
   * of evaluation.
   * @param[in, out] S Abstract state in which operate
   * @return         Abstract arithmetic evaluation
   */
  template <class T>
  typename T::abstract_type
  arithmetic_op(AbstractState<typename T::abstract_type> *S)
  {
    switch(this->type){
      case NUM:
        return T::NumericValue(this->value);
      
      case VAR:
        return T::VariableValue(this->literal, S);
       
      case AOP: switch(this->a_op){
        case SUM:
          return T::Sum(this->subtrees[0]->arithmetic_op<T>(S),
                        this->subtrees[1]->arithmetic_op<T>(S));
        
        case DIF:
          return T::Dif(this->subtrees[0]->arithmetic_op<T>(S),
                        this->subtrees[1]->arithmetic_op<T>(S));
        
        case MUL:
          return T::Prod(this->subtrees[0]->arithmetic_op<T>(S),
                         this->subtrees[1]->arithmetic_op<T>(S));
        
        case DIV:
          return T::Div(this->subtrees[0]->arithmetic_op<T>(S),
                        this->subtrees[1]->arithmetic_op<T>(S));
        
        case REM:
          return T::Rem(this->subtrees[0]->arithmetic_op<T>(S),
                        this->subtrees[1]->arithmetic_op<T>(S));
        
        case POW:
          return T::Pow(this->subtrees[0]->arithmetic_op<T>(S),
                        this->subtrees[1]->arithmetic_op<T>(S));
        
        default:
          fprintf(stderr,
            "[AST::arithmetic_op] Unrecognized arithmetic operation.\n");
      }
      break;
      
      default:
        fprintf(stderr,
          "[AST::arithmetic_op] Unrecognized arithmetic item\n.");
    }
    return (typename T::abstract_type) 0;
  }
  
  
  
  /** The Boolean Expression is interepreted.
   * The subtree corresponding to a boolean expression rooted in the
   * current node is interpreted, according to a given abstract state
   * and a given abstract domain. This typically correspond to some kind
   * of evaluation.
   * @param[in, out] S Abstract state in which operate
   * @return         Abstract boolean evaluation
   */
  template <class T>
  typename T::abstract_bool
  boolean_op(AbstractState<typename T::abstract_type> *S)
  {
    switch(this->type){
      case BOOL:
        return T::Bool(this->literal);
      
      case NOT:
        return T::Not(this->subtrees[0]->boolean_op<T>(S));
      
      case BOP: switch(this->b_op){
        case AND:
          return T::And(this->subtrees[0]->boolean_op<T>(S),
                        this->subtrees[1]->boolean_op<T>(S));
        
        case OR:
          return T::Or(this->subtrees[0]->boolean_op<T>(S),
                       this->subtrees[1]->boolean_op<T>(S));
        
        case XOR:
          return T::Xor(this->subtrees[0]->boolean_op<T>(S),
                        this->subtrees[1]->boolean_op<T>(S));
        
        case NAND:
          return T::Nand(this->subtrees[0]->boolean_op<T>(S),
                         this->subtrees[1]->boolean_op<T>(S));
        
        case NOR:
          return T::Nor(this->subtrees[0]->boolean_op<T>(S),
                        this->subtrees[1]->boolean_op<T>(S));
        
        case NXOR:
          return T::Nxor(this->subtrees[0]->boolean_op<T>(S),
                         this->subtrees[1]->boolean_op<T>(S));
        
        default:
          fprintf(stderr,
            "[AST::boolean_op] Unrecognized boolean operation.\n");
      }
      break;
      
      case CMP: switch(this->c_op){
        case LT:
          return T::Lt(this->subtrees[0]->arithmetic_op<T>(S),
                       this->subtrees[1]->arithmetic_op<T>(S));
        
        case LEQ:
          return T::Leq(this->subtrees[0]->arithmetic_op<T>(S),
                        this->subtrees[1]->arithmetic_op<T>(S));
        
        case EQ:
          return T::Eq(this->subtrees[0]->arithmetic_op<T>(S),
                       this->subtrees[1]->arithmetic_op<T>(S));
        
        case GEQ:
          return T::Geq(this->subtrees[0]->arithmetic_op<T>(S),
                        this->subtrees[1]->arithmetic_op<T>(S));
        
        case GT:
          return T::Gt(this->subtrees[0]->arithmetic_op<T>(S),
                       this->subtrees[1]->arithmetic_op<T>(S));
        
        case NEQ:
          return T::Neq(this->subtrees[0]->arithmetic_op<T>(S),
                        this->subtrees[1]->arithmetic_op<T>(S));
        
        default:
          fprintf(stderr,
            "[AST::boolean_op] Unrecognized comparison.\n");
      }
      break;
      
      default:
        fprintf(stderr,
          "[AST::boolean_op] Unrecognized boolean item.\n");
    }
    
    return (typename T::abstract_bool) true;
  }
  
  
  
  /** The subtree is exported into a graphviz file.
   * The subtree rooted in the current node is exported to a file at
   * given location, which can later be processed with the graphviz tool
   * in order to produce a visual representation of the tree.
   * An user defined function is used to translate the abstract value of
   * every node into a string to be displayed inside the node.
   * @param[in]  filename    Name of the output file
   */
  void export_graphviz(const char* filename)
  {
    char str[32];
    unsigned int i;
    unsigned int node_ID, edge_ID;
    unsigned int nodes, edges;
    ofstream output;
    struct graph_node *node_list;
    struct graph_edge *edge_list;
    
    
    // Otput file is open.
    output.open(filename, ios::out);
    if(!output.is_open()){
      fprintf(stderr, "[AST::export_graphviz]: Unable to open file.\n");
      return;
    }
    
    
    // Graphviz header is prepared.
    output 
    << "/** Automatically generated by the static analyzer for graphviz.\n"
    <<  " * Compile this file with `dot -Tpng -O " << filename << "`.\n"
    <<  " * or any other options you like. See `man dot` for informations.\n"
    <<  " */\n"
    << "strict digraph AST{\n"
    << "  splines = true;\n"
    << "  layout  = dot;\n"
    << "  bgcolor = \"#FFFFFF\";\n"
    << "  \n"
    << "  node [fontname=\"Times\", fontcolor=\"#333333\","
    << " color=\"#333333\",\n        style=\"solid\"];\n"
    << "  edge [fontname=\"Times\", fontcolor=\"#222222\","
    << " color=\"#222222\",\n        arrowhead=\"open\"];\n"
    << "  \n"
    ;
    
    // Tree is scanned and the lists of nodes are created.
    nodes = this->nodes();
    node_list = (struct graph_node *) malloc(nodes * sizeof(struct graph_node));
    node_ID = 0;
    
    edges = this->edges();
    edge_list = (struct graph_edge *) malloc(edges * sizeof(struct graph_edge));
    edge_ID = 0;
    
    this->to_list(node_list, edge_list, &node_ID, &edge_ID);
    
    // The output is written to the graphviz file.
    output << "  /* Nodes. */\n";
    for(i = 0; i < nodes; i++){
      ((AST *) node_list[i].node)->to_string(str);
      output << "  " << i << "[label=\"" << str << "\"];\n";
    }
    
    output << "\n";
    
    output << "  /* Edges. */\n";
    for(i = 0; i < edges; i++){
      output << "  " << edge_list[i].tail->ID << " -> "
             << edge_list[i].head->ID << ";\n";
    }
    
    output << "}\n";
    
    // Output file is safely closed and memory is freed.
    output.close();
    free(node_list);
    free(edge_list);
  }
  
  
  
private:
  node_type type;       /**< Type of the node. */
  int value;            /**< Abstract value associated to the node. */
  char literal[32];     /**< Literal associated to the node. */
  a_opcode a_op;        /**< Arithmetic operator associated to the node. */
  b_opcode b_op;        /**< Boolean operator associated to the node. */
  c_opcode c_op;        /**< Comparison operator associated to the node. */
  unsigned int sons;    /**< Number of sons of the node. */
  AST *subtrees[3];     /**< Array containing every son of the node. */
  
  
  /* Structures used by the built-in graphviz converter. */
  /** Structure of a node. */
  struct graph_node{
    void *node;                /**< Pointer to the node. */
    unsigned int ID;           /**< ID of the node. */
  };
  
  /** Structure of an edge. */
  struct graph_edge{
    struct graph_node *head;   /**< Pointer to the head. */
    struct graph_node *tail;   /**< Pointer to the tail. */
  };
  
  
  
  /** The subtree is scanned and converted into lists of nodes and edges.
   * The subtree rooted in the current node is explored (trough a
   * depth-first visit). Such a visit builds two arrays, one containing
   * the couples (pointer-to-node; numeric-ID) representing the nodes,
   * the other containing the couples (pointer-to-head; pointer-to-tail)
   * representing the edges.
   * @param[in, out] node_list List of nodes visited so far
   * @param[in, out] edge_list List of edges visited so far
   * @param[in, out] node_ID   Next ID to be assigned to a node
   * @param[in, out] edge_ID   Next ID to be assigned to an edge
   * @return     ID of the last visited node
   */
  unsigned int to_list(
    struct graph_node node_list[], struct graph_edge edge_list[],
    unsigned int *node_ID, unsigned int *edge_ID
  )
  {
    unsigned int ID, son, i;
    struct graph_node node;
    struct graph_edge edge;
    
    ID = *node_ID;
    node.node = this;
    node.ID   = ID;
    node_list[ID] = node;
    *node_ID = ID + 1;
    
    for(i = 0; i < this->sons; i++){
      son = this->subtrees[i]->to_list(node_list, edge_list, node_ID, edge_ID);
      edge.head = &node_list[son];
      edge.tail = &node_list[ID];
      edge_list[*edge_ID] = edge;
      *edge_ID = *edge_ID + 1;
    }
    
    return ID;
  }
  
  
  
  /** The current node is "translated" to a string.
   * The content of the current node is print into a previously 
   * allocated buffer. The content of the string depends on the type of
   * the node.
   * @param[out] buffer      Buffer where the string will be written
   */
  void to_string(char *buffer)
  {
    switch(this->type){
      case ASN:  sprintf(buffer, ":=");                      break;
      case SKP:  sprintf(buffer, "skip");                    break;
      case CAT:  sprintf(buffer, ";");                       break;
      case IF:   sprintf(buffer, "if-then-else");            break;
      case WHL:  sprintf(buffer, "while");                   break;
      case NUM:  sprintf(buffer, "Num\\n%d", this->value);   break;
      case VAR:  sprintf(buffer, "Var\\n%s", this->literal); break;
      case AOP:  switch(this->a_op){
                   case SUM: sprintf(buffer, "AOp\\n+");  break;
                   case DIF: sprintf(buffer, "AOp\\n-");  break;
                   case MUL: sprintf(buffer, "AOp\\n*");  break;
                   case DIV: sprintf(buffer, "AOp\\n/");  break;
                   case REM: sprintf(buffer, "AOp\\n%%"); break;
                   case POW: sprintf(buffer, "AOp\\n^");  break;
                   default:  sprintf(buffer, "Unknown\\nAOp"); break;
                 } break;
      case BOOL: sprintf(buffer, "%s", this->literal);       break;
      case NOT:  sprintf(buffer, "not");                     break;
      case BOP:  switch(this->b_op){
                   case AND:  sprintf(buffer, "BOp\\nand");  break;
                   case OR:   sprintf(buffer, "BOp\\nor");   break;
                   case XOR:  sprintf(buffer, "BOp\\nxor");  break;
                   case NAND: sprintf(buffer, "BOp\\nnand"); break;
                   case NOR:  sprintf(buffer, "BOp\\nnor");  break;
                   case NXOR: sprintf(buffer, "BOp\\nnxor"); break;
                   default:   sprintf(buffer, "Unknown\\nBOp"); break;
                 } break;
      case CMP:  switch(this->c_op){
                   case LT:  sprintf(buffer, "cmp\\n<");  break;
                   case LEQ: sprintf(buffer, "cmp\\n<="); break;
                   case EQ:  sprintf(buffer, "cmp\\n=");  break;
                   case GEQ: sprintf(buffer, "cmp\\n>="); break;
                   case GT:  sprintf(buffer, "cmp\\n>");  break;
                   case NEQ: sprintf(buffer, "cmp\\n<>"); break;
                   default:  sprintf(buffer, "Unkown\\ncmp"); break;
                 } break;
      case PRN:  sprintf(buffer, "print");                   break;
      default:   sprintf(buffer, "unkown\\nsyntax");         break;
    }
  }
};

#endif

