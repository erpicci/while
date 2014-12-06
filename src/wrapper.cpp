/** Wrapper used to "translate" C++ AST constructors into a C version.
 * 
 * AST uses C++ constructors to build Abstract Syntax (sub) Tree, and
 * this object oriented mechanism is not available in the lex/yacc (nor
 * flex/bison) system used to parse the source codes; therefore this
 * module offers a C like interface to the parser.
 * Alternative solutions are possible, i.e. using flex++, bison++ or
 * bisonc++, unfortunately they do not work properly at the moment. Also
 * the C++ support for (regular) bison is still experimental and, in any
 * case, it does not work properly at the moment, or is unstable.
 * 
 * @file wrapper.cpp
 * @author Marco Zanell <marco.zanella.9@studenti.unipd.it>
 * @version 1.0
 * @date 13/03/2014
 */


/* Header file inclusion. */
#include <vector>
#include "AST.h"



/** List of variables' names encountered during the parsing. */
vector<string> vars;



/***********************************************************************
 * Functions dealing with Statements.
 **********************************************************************/

/** Abstract "assignment" subtree.
 * An abstract subtree representing an assignement is created.
 * @param[in]  variable      Abstract subtree representing a variable
 * @param[in]  expression    Abstract subtree representing an
 *                           arithmetic expression.
 * @return     Abstract syntax (sub) tree representing an assignment
 */
void *_assignment(void *variable, void *expression)
{
  return (void *)
    new AST(AST::ASN, (AST *) variable, (AST *) expression);
}



/** Abstract "skip" subtree.
 * An abstract subtree representing a skip operation is created.
 * @return     Abstract syntax (sub) tree representing a skip
 */
void *_skip(void)
{
  return (void *)
    new AST(AST::SKP);
}



/** Abstract "concatenation" subtree.
 * An abstract subtree representing a concatenation operation is
 * created.
 * @param[in]  first         Abstract subtree representing the first
 *                           statement
 * @param[in]  second        Abstract subtree representing the second
 *                           statement
 * @return     Abstract syntax (sub) tree representing a concatenarion
 */
void *_concatenation(void *first, void *second)
{
  return (void *)
    new AST(AST::CAT, (AST *) first, (AST *) second);
}



/** Abstract "if-then-else" subtree.
 * An abstract subtree representing an if-then-else evaluation is
 * created.
 * @param[in]  condition     Abstract subtree representing a boolean
 *                           condition
 * @param[in]  then_branch   Abstract subtree representing the
 *                           then-branch
 * @param[in]  else_branch   Abstract subtree representing the
 *                           else-branch
 * @return     Abstract syntax (sub) tree representing the if-then-else
 *             statement
 */
void *_if(void *condition, void *then_branch, void *else_branch)
{
  return (void *)
    new AST(AST::IF,
            (AST *) condition,
            (AST *) then_branch,
            (AST *) else_branch);
}



/** Abstract "while...do" subtree.
 * An abstract subtree representing a while iteration is created.
 * @param[in]  condition     Abstract subtree representing the condition
 *                           over which iterate
 * @param[in]  body          Abstract subtree representing the body of
 *                           the while loop
 * @return     Abstract syntax (sub) tree representing the while loop
 *             statement
 */
void *_while(void *condition, void *body)
{
  return (void *)
    new AST(AST::WHL, (AST *) condition, (AST *) body);
}



/** Abstract "print" subtree.
 * An abstract subtree representing a print statement is created.
 * @param[in]  expression    Abstract subtree representing the
 *                           arithmetic expression to print
 * @return     Abstract syntax (sub) tree representing the print
 *             statement
 */
void *_print(void *expression)
{
  return (void *)
    new AST(AST::PRN, (AST *) expression);
}



/***********************************************************************
 * Functions dealing with Arithmetic Expressions.
 **********************************************************************/

/** Abstract "numeric constant" subtree.
 * An abstract subtree representing a numeric constant is created.
 * @param[in]  value         Numeric value of the constant
 * @return     Abstract syntax subtree representing the numeric constant
 */
void *_constant(int value)
{
  return (void *)
    new AST(AST::NUM, value);
}



/** Abstract "variable" subtree.
 * An abstract subtree representing a variable is created.
 * @param[in]  identifier    Name of the variable
 * @return     Abstract syntax (sub) tree representing the variable
 */
void *_variable(const char identifier[])
{
  vars.push_back(identifier);
  return (void *)
    new AST(AST::VAR, identifier);
}



/** Abstract "sum" subtree.
 * An abstract subtree representing an arithmetic sum is created.
 * @param[in]  first_op      Abstract subtree representing the first
 *                           operand
 * @param[in]  second_op     Abstarct subtree representin the second
 *                           operand
 * @return     Abstract syntax subtree representing an arithmetic sum
 */
void *_sum(void *first_op, void *second_op)
{
  return (void *)
    new AST(AST::AOP, AST::SUM, (AST *) first_op, (AST *) second_op);
}



/** Abstract "difference" subtree.
 * An abstract subtree representing an arithmetic difference is created.
 * @param[in]  first_op      Abstract subtree representing the first
 *                           operand
 * @param[in]  second_op     Abstarct subtree representin the second
 *                           operand
 * @return     Abstract syntax subtree representing an arithmetic
 *             difference
 */
void *_difference(void *first_op, void *second_op)
{
  return (void *)
    new AST(AST::AOP, AST::DIF, (AST *) first_op, (AST *) second_op);
}



/** Abstract "multiplication" subtree.
 * An abstract subtree representing an arithmetic multiplication is
 * created.
 * @param[in]  first_op      Abstract subtree representing the first
 *                           operand
 * @param[in]  second_op     Abstarct subtree representin the second
 *                           operand
 * @return     Abstract syntax subtree representing an arithmetic
 *             multiplication
 */
void *_product(void *first_op, void *second_op)
{
  return (void *)
    new AST(AST::AOP, AST::MUL, (AST *) first_op, (AST *) second_op);
}



/** Abstract "division" subtree.
 * An abstract subtree representing an integer division is created.
 * @param[in]  first_op      Abstract subtree representing the first
 *                           operand
 * @param[in]  second_op     Abstarct subtree representin the second
 *                           operand
 * @return     Abstract syntax subtree representing an integer
 *             division
 */
void *_division(void *first_op, void *second_op)
{
  return (void *)
    new AST(AST::AOP, AST::DIV, (AST *) first_op, (AST *) second_op);
}



/** Abstract "rem" subtree.
 * An abstract subtree representing an integer rem is created.
 * @param[in]  first_op      Abstract subtree representing the first
 *                           operand
 * @param[in]  second_op     Abstarct subtree representin the second
 *                           operand
 * @return     Abstract syntax subtree representing an integer rem
 */
void *_rem(void *first_op, void *second_op)
{
  return (void *)
    new AST(AST::AOP, AST::REM, (AST *) first_op, (AST *) second_op);
}



/** Abstract "power" subtree.
 * An abstract subtree representing an integer power is created.
 * @param[in]  base          Abstract subtree representing the base
 * @param[in]  exponent      Abstarct subtree representin the exponent
 * @return     Abstract syntax subtree representing an integer power
 */
void *_pow(void *base, void *exponent)
{
  return (void *)
    new AST(AST::AOP, AST::POW, (AST *) base, (AST *) exponent);
}



/***********************************************************************
 * Functions dealing with Boolean Expressions.
 **********************************************************************/

/** Abstract boolean constant.
 * An abstract subtree representing a boolean contant is created.
 * @param[in]  constant      String representing the boolean constant
 * @return     Abstract syntax subtree representing a boolean constant
 */
void *_boolean(const char constant[])
{
  return (void *)
    new AST(AST::BOOL, constant);
}



/** Abstract boolean negation.
 * An abstract subtree representing a boolean negation is created.
 * @param[in]  boolean       Abstract subtree representing the boolean
 *                           expression to be negated
 * @return     Abstract syntax subtree representing the boolean negation
 */
void *_not(void *boolean)
{
  return (void *)
    new AST(AST::NOT, (AST *) boolean);
}



/** Abstract "and" subtree.
 * An abstract subtree representing an and boolean operation is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           boolean operand
 * @param[in]  second        Abstract subtree representing the second
 *                           boolean operand
 * @return     Abstract syntax subtree representing the and boolean
 *             expression
 */
void *_and(void *first, void *second)
{
  return (void *)
    new AST(AST::BOP, AST::AND, (AST *) first, (AST *) second);
}



/** Abstract "or" subtree.
 * An abstract subtree representing an or boolean operation is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           boolean operand
 * @param[in]  second        Abstract subtree representing the second
 *                           boolean operand
 * @return     Abstract syntax subtree representing the or boolean
 *             expression
 */
void *_or(void *first, void *second)
{
  return (void *)
    new AST(AST::BOP, AST::OR, (AST *) first, (AST *) second);
}



/** Abstract "xor" subtree.
 * An abstract subtree representing an xor boolean operation is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           boolean operand
 * @param[in]  second        Abstract subtree representing the second
 *                           boolean operand
 * @return     Abstract syntax subtree representing the xor boolean
 *             expression
 */
void *_xor(void *first, void *second)
{
  return (void *)
    new AST(AST::BOP, AST::XOR, (AST *) first, (AST *) second);
}



/** Abstract "nand" subtree.
 * An abstract subtree representing an not and boolean operation is
 * created.
 * @param[in]  first         Abstract subtree representing the first
 *                           boolean operand
 * @param[in]  second        Abstract subtree representing the second
 *                           boolean operand
 * @return     Abstract syntax subtree representing the nand boolean
 *             expression
 */
void *_nand(void *first, void *second)
{
  return (void *)
    new AST(AST::BOP, AST::NAND, (AST *) first, (AST *) second);
}



/** Abstract "nor" subtree.
 * An abstract subtree representing an not or boolean operation is
 * created.
 * @param[in]  first         Abstract subtree representing the first
 *                           boolean operand
 * @param[in]  second        Abstract subtree representing the second
 *                           boolean operand
 * @return     Abstract syntax subtree representing the nor boolean
 *             expression
 */
void *_nor(void *first, void *second)
{
  return (void *)
    new AST(AST::BOP, AST::NOR, (AST *) first, (AST *) second);
}



/** Abstract "nxor" subtree.
 * An abstract subtree representing an not xor boolean operation is
 * created.
 * @param[in]  first         Abstract subtree representing the first
 *                           boolean operand
 * @param[in]  second        Abstract subtree representing the second
 *                           boolean operand
 * @return     Abstract syntax subtree representing the nxor boolean
 *             expression
 */
void *_nxor(void *first, void *second)
{
  return (void *)
    new AST(AST::BOP, AST::NXOR, (AST *) first, (AST *) second);
}



/** Abstract "less than" subtree.
 * An abstract subtree representing a less than comparison is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           arithmetic operand
 * @param[in]  second        Abstract subtree representing the second
 *                           arithmetic operand
 * @return     Abstract syntax subtree representing the less than
 *             comparison
 */
void *_lt(void *first, void *second)
{
  return (void *)
    new AST(AST::CMP, AST::LT, (AST *) first, (AST *) second);
}



/** Abstract "less or equal" subtree.
 * An abstract subtree representing a less or equal comparison is
 * created.
 * @param[in]  first         Abstract subtree representing the first
 *                           arithmetic operand
 * @param[in]  second        Abstract subtree representing the second
 *                           arithmetic operand
 * @return     Abstract syntax subtree representing the less or equal
 *             comparison
 */
void *_leq(void *first, void *second)
{
  return (void *)
    new AST(AST::CMP, AST::LEQ, (AST *) first, (AST *) second);
}



/** Abstract "equal" subtree.
 * An abstract subtree representing an equality comparison is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           arithmetic operand
 * @param[in]  second        Abstract subtree representing the second
 *                           arithmetic operand
 * @return     Abstract syntax subtree representing the equality
 *             comparison
 */
void *_eq(void *first, void *second)
{
  return (void *)
    new AST(AST::CMP, AST::EQ, (AST *) first, (AST *) second);
}



/** Abstract "greater or equal" subtree.
 * An abstract subtree representing a greater or equal comparison is
 * created.
 * @param[in]  first         Abstract subtree representing the first
 *                           arithmetic operand
 * @param[in]  second        Abstract subtree representing the second
 *                           arithmetic operand
 * @return     Abstract syntax subtree representing the greater or equal
 *             comparison
 */
void *_geq(void *first, void *second)
{
  return (void *)
    new AST(AST::CMP, AST::GEQ, (AST *) first, (AST *) second);
}



/** Abstract "greater than" subtree.
 * An abstract subtree representing a greater than comparison is
 * created.
 * @param[in]  first         Abstract subtree representing the first
 *                           arithmetic operand
 * @param[in]  second        Abstract subtree representing the second
 *                           arithmetic operand
 * @return     Abstract syntax subtree representing the greater than
 *             comparison
 */
void *_gt(void *first, void *second)
{
  return (void *)
    new AST(AST::CMP, AST::GT, (AST *) first, (AST *) second);
}



/** Abstract "not equal" subtree.
 * An abstract subtree representing an inequality comparison is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           arithmetic operand
 * @param[in]  second        Abstract subtree representing the second
 *                           arithmetic operand
 * @return     Abstract syntax subtree representing the inequality
 *             comparison
 */
void *_neq(void *first, void *second)
{
  return (void *)
    new AST(AST::CMP, AST::NEQ, (AST *) first, (AST *) second);
}



/** The list of variables encountered during the parsing is returned.
 * A matrix of characters is allocated. When done, memory frees should
 * be called.
 * @param[out] variables     Pointer to the array of names
 * @param[out] number        Number of encountered variables
 */
void variables(char ***variables, unsigned int *number)
{
  unsigned int i, size;
  
  size = vars.size();
  *number = size;
  
  /* Variables array is allocated. */
  *variables = (char **) malloc(size * sizeof(char *));
  if(*variables == NULL){
    fprintf(stderr, "[variables] Out of memory\n");
    return;
  }
  
  /* Each variable name is copied into the array. */
  for(i = 0; i < size; i++){
    (*variables)[i] = (char *) malloc(vars[i].size() * sizeof(char));
    if((*variables)[i] == NULL){
      fprintf(stderr, "[variables] Out of memory\n");
      return;
    }
    strcpy((*variables)[i], vars[i].c_str());
  }
}

