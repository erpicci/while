/** Abstract syntax tree.
 * Class handling an abstract syntax tree, built by the parser. Such a
 * tree can be traversed to perform an abstract interpretation.
 * 
 * @file AST.hpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
#ifndef _AST_HPP_
#define _AST_HPP_

#include <vector>
#include <string>

#include "AbstractState.hpp"

using namespace std;


/** Class representing an abstract syntax tree. */
class AST
{
  public:
  /** Type representing a statement. */
  typedef enum{
    Asn,           ///< 'Assignment' statement
    Skp,           ///< 'Skip' statement
    Seq,           ///< 'Sequential composition' statement
    If,            ///< 'If-then-else' branch statement
    Whl,           ///< 'While' loop statement
    Prn,           ///< 'Print' statement
    In             ///< 'Input' statement
  } StmType;
  
  
  /** Type representing an arithmetic expression. */
  typedef enum{
    Num,           ///< Constant, integer value
    Var,           ///< Variable, identifier
    Id,            ///< Identity (i.e. +a)
    Opp,           ///< Opposite (i.e. -a)
    Sum,           ///< Sum
    Sub,           ///< Subtraction
    Mul,           ///< Multiplication
    Div,           ///< Integer division
    Rem,           ///< Rest of the integer division
    Pow            ///< Raise to the power
  } AExpType;
  
  
  /** Type representing a boolean expresson or comparison. */
  typedef enum{
    Bool,          ///< Constant, boolean value
    Not,           ///< Logical negation
    And,           ///< Logical conjunction
    Or,            ///< Logical disjunction
    Xor,           ///< Logical exclusive disjunction
    Nand,          ///< Negated conjunction
    Nor,           ///< Negated disjunction
    Xnor,          ///< Negated exclusive disjunction
    Lt,            ///< 'Less than' comparison
    Leq,           ///< 'Less than or equal to' comparison
    Eq,            ///< 'Equal to' comparison
    Geq,           ///< 'Greater than or equal to' comparison
    Gt,            ///< 'Greater than' comparison
    Neq            ///< 'Not equal to' comparison
  } BExpType;
  
  
  /** Constructor of a 0-ary statement abstract syntax node.
   * 0-ary statements are: skip (Skp).
   * @param[in]  type        Type of the statement
   */
  AST(StmType type);
  
  
  /** Constructor of a unary statement abstract syntax node.
   * Unary statements are: print (Prn), input (In).
   * @param[in]  type        Type of the stament
   * @param[in]  first       Subtree representing the argument
   */
  AST(StmType type, AST *first);
  
  
  /** Constructor of a binary statement abstract syntax node.
   * Binary statements are: assignment (Asn), sequential composition
   * (Seq), while loop (Whl).
   * @param[in]  type        Type of the statement
   * @param[in]  first       Subtree representing the first argument
   * @param[in]  second      Subtree representing the second argument
   */
  AST(StmType type, AST *first, AST *second);
  
  
  /** Constructor of a ternary statement abstract syntax node.
   * Ternary statements are: if-then-else branch (If).
   * @param[in]  type        Type of the statement
   * @param[in]  first       Subtree representing the first argument
   * @param[in]  second      Subtree representing the second argument
   * @param[in]  third       Subtree representing the third argument
   */
  AST(StmType type, AST *first, AST *second, AST *third);
  
  
  /** Constructor of a numeric constant abstract syntax node.
   * Numeric constant expressions are: num (Num).
   * @param[in]  type        Type of the arithmetic expression
   * @param[in]  num         Constant, integer value
   */
  AST(AExpType type, int num);
  
  
  /** Constructor of a variable synatax node.
   * Varibales are: var (Var).
   * @param[in]  type        Type of the arithmetic expression
   * @param[in]  var         Name of the variable
   */
  AST(AExpType type, string var);
  
  
  /** Constructor of an unary arithmetic expression abstract syntax node.
   * Unary arithmetic expressions are: identity (Id), opposite (Opp).
   * @param[in]  type        Type of the arithmetic expression
   * @param[in]  a           Operand
   */
  AST(AExpType type, AST *a);
  
  
  /** Constructor of a binary arithmetic expression abstract syntax node.
   * Binary arithmetic expressions are: sum (Sum), subtraction (Sub),
   * multiplication (Mul), integer division (Div), remainder of the
   * integer division (Rem), raise to the power (Pow).
   * @param[in]  type        Type of the arithmetic expression
   * @param[in]  a1          First operand
   * @param[in]  a2          Second operand
   */
  AST(AExpType type, AST *a1, AST *a2);
  
  
  /** Constructor of a constant, boolean value.
   * Constant, boolean values are: boolean (Bool).
   * @param[in]  type        Type of the boolean value
   * @param[in]  boolean     Boolean value
   */
  AST(BExpType type, bool boolean);
  
  
  /** Constructor of a unary boolean expression abstract syntax node.
   * Unary boolean expressions are: logical negation (Not).
   * @param[in]  type        Type of the boolean expression
   * @param[in]  b           Operand
   */
  AST(BExpType type, AST *b);
  
  
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
  AST(BExpType type, AST *b1, AST *b2);
  
  
  /** Destructor of an abstract syntax tree. */
  ~AST();
  
  
  /** A textual representation of the node is provided.
   * @retval     string      String representing the node
   */
  string toString();
  
  
  /** Abstract syntax tree is exported to graphviz.
   * The abstract syntax tree rooted in the current node is esported
   * into a file which can later be compiled using graphviz.
   * @param[in]  filename    Path to the output file
   */
  void toGraphviz(const char *filename);
  
  
  /** Abstract syntax tree is interpreted from the bottom state.
   * Type of (abstract) interpretation is parametric.
   * @retval     AbstractState Final state
   */
  template <typename D>
  AbstractState<D> interpret()
  {
    return interpret(AbstractState<D>());
  }
  
  
  /** Abstract syntax tree is interpreted in the given state.
   * Type of (abstract) interpretation is parametric.
   * @param[in]  state       Initial state
   * @retval     AbstractState Final state
   */
  template <typename D>
  AbstractState<D> interpret(AbstractState<D> state)
  {
    AbstractState<D> s;
    
    // If node is not a statement, just return the current state.
    if(type != Stm){ return state; }
    
    // Correct action is taken depending on the statement type.
    switch(opcode.statement){
      case Asn:
        state.store(*(sons[0]->value.var), sons[1]->A(state));
        return state;
      
      case Skp:
        return state;
      
      case Seq:
        return sons[1]->interpret(sons[0]->interpret(state));
      
      case If:
        return AbstractState<D>::lub(
          sons[1]->interpret(sons[0]->B(state)),
          sons[2]->interpret(sons[0]->neg().B(state))
        );
      
      case Whl:
        do{
          s     = state;
          state = sons[1]->interpret(sons[0]->B(state));
          state = AbstractState<D>::lub(s, state);
          state = AbstractState<D>::widening(s, state);
        }
        while(s != state);
        state = sons[0]->neg().B(state);
        return state;
      
      case Prn:
        return state;
      
      case In:
        state.store(*(sons[0]->value.var), D::top());
        return state;
      
      default:
        cerr << "[AST::Interpret]: Unrecognized statement opcode value: "
             << opcode.statement << "." << endl;
        return state;
    }
  }
  
  
  /** An arithmetic expression is evaluated in the given state.
   * Abstract evaluation is parametric.
   * @param[in]  state       Initial state
   * @retval     T           Resulting abstract value
   */
  template <typename T>
  T A(AbstractState<T> state)
  {
    // If node is not an arithmetic expression, just return an empty value.
    if(type != AExp){ return T(); }
    
    // Correct action is taken depending on the type of operation.
    switch(opcode.arithmetic){
      case Num: return T::alpha(value.num);
      case Var: return state.load(*(value.var));
      case Id:  return +(sons[0]->A(state));
      case Opp: return -(sons[0]->A(state));
      case Sum: return sons[0]->A(state) + sons[1]->A(state);
      case Sub: return sons[0]->A(state) - sons[1]->A(state);
      case Mul: return sons[0]->A(state) * sons[1]->A(state);
      case Div: return sons[0]->A(state) / sons[1]->A(state);
      case Rem: return sons[0]->A(state) % sons[1]->A(state);
      case Pow: return sons[0]->A(state) ^ sons[1]->A(state);
      default:
        cerr << "[AST::A]: Unrecognized arithmetic opcode value: "
             << opcode.arithmetic << "." << endl;
        return T();
    }
  }
  
  
  /** Boolean expression is evaluated in the given state.
   * Type of abstract evaluation is parametric.
   * @param[in]  state       Initial state
   * @retval     AbstractState The state itself if the evaluation was
   *                         true, the bottom state otherwise
   */
  template <typename D>
  AbstractState<D> B(AbstractState<D> state)
  {
    AbstractState<D> bottom, s;
   
    // If node is not a boolean expression, just return the current state.
    if(type != BExp){ return state; }
    
    // Correct action is taken depending on the type of expression.
    switch(opcode.boolean){
      case Bool:
        return (value.boolean) ? state : bottom;
      
      case Not:
        return sons[0]->neg().B(state);
      
      case And:
        return sons[1]->B(sons[0]->B(state));
      
      case Or:
        return AbstractState<D>::lub(
          sons[0]->B(state),
          sons[1]->B(state)
        );
      
      case Xor:
        return AbstractState<D>::lub(
          sons[0]->B(sons[1]->neg().B(state)),
          sons[0]->neg().B(sons[1]->B(state))
        );
      
      case Nand: case Nor:  case Xnor:
        return (neg().B(state) == bottom)
             ? state : bottom;
      
      case Lt:
        return (sons[0]->A(state) < sons[1]->A(state))
             ? state : bottom;
      
      case Leq:
        return (sons[0]->A(state) <= sons[1]->A(state))
             ? state : bottom;
      
      case Eq:
        return (sons[0]->A(state) == sons[1]->A(state))
             ? state : bottom;
      
      case Geq:
        return (sons[0]->A(state) >= sons[1]->A(state))
             ? state : bottom;
      
      case Gt:
        return (sons[0]->A(state) > sons[1]->A(state))
             ? state : bottom;
      
      case Neq:
        return (sons[0]->A(state) != sons[1]->A(state))
             ? state : bottom;
      
      default:
        cerr << "[AST::B]: Unrecognized boolean opcode value: "
             << opcode.boolean << "." << endl;
        return state;
    }
  }
  
  
  /** Concrete excecution is performed starting from the bottom state.
   * @retval     AbstractState State containing the result of the
   *                         (concrete) compupation
   */
  AbstractState<int> execute();
  
  
  /** Concrete excecution is performed starting from the given state.
   * @param[in]  state       Initial state
   * @retval     AbstractState State containing the result of the
   *                         (concrete) compupation
   */
  AbstractState<int> execute(AbstractState<int> state);
  
  
  /** An arithmetic expression is evaluated in the given state.
   * Evaluation is performed on the concrete values.
   * @param[in]  state       Concrete state where expression is
   *                         evaluated
   * @retval     int         Evaluated arithmetic expression
   */
  int A(AbstractState<int> state);
  
  
  /** Boolean expression is evaluated in the given state.
   * Evaluation is perfomed on the concrete values.
   * @param[in]  state       Initial state
   * @retval     bool        True if and only if the boolean expression
   *                         evaluates to true
   */
  bool B(AbstractState<int>);
  
  
  private:
  /** Type of an abstract syntax node. */
  typedef enum{
    Stm,                ///< Statement node
    AExp,               ///< Arithmetic expression node
    BExp                ///< Boolean expression node
  } nodeType;
  
  /** Type representing a value associated to the node. */
  typedef union{
    int  num;           ///< Constant, integer value
    string *var;        ///< Name of a variable
    bool boolean;       ///< Constant, boolean value
  } valueType;
  
  /** Type representing the opcode of the node. */
  typedef union{
    StmType    statement;    ///< Node is a statement
    AExpType   arithmetic;   ///< Node is an arithmetic expression
    BExpType   boolean;      ///< Node is a boolean expression
  } opcodeType;
  
  
  static unsigned int lastID;  ///< Last assigned nodeID
  unsigned int nodeID;  ///< ID of the node
  nodeType     type;    ///< Type of the node
  AST *        parent;  ///< Pointer to parent node
  vector<AST*> sons;    ///< List of sons
  valueType    value;   ///< Value associated to the node, if any
  opcodeType   opcode;  ///< Opcode of the node
  
  
  /** Boolean expression is negated.
   * Boolean expression associated to the current node is reversed and
   * returned into a new sub-tree.
   * For instance, if current node contains a 'less than' comparison
   * between arithmetic expressions a1 and a2, a new sub-tree is created,
   * whose root is a node representing a 'greater than or equal to'
   * comparison between a1 and a2.
   * @retval     AST         Negated boolean expression
   */
  AST neg();
};
#endif
