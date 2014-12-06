/** Concncrete domain.
 * 
 * The concrete domain for the While language is the set of integer
 * number equiped with the usual operations, as well as the boolean
 * algebra. This is actually an interepreter for the While language,
 * where no real static analysis is performed.
 * 
 * @file ConcreteDomain.h
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @version 0.9
 * @date 13/03/2014
 */

#ifndef _CONCRETE_DOMAIN_H_
#define _CONCRETE_DOMAIN_H_

/* Header file inclusion. */
#include "../AbstractDomain.h"
#include "../AbstractState.h"



/** Class defining the Concrete Domain.
 * The concrete domain for the While language implements the direct
 * interpretation of the absctract syntax tree.
 */
class ConcreteDomain : public AbstractDomain
{
public:
  /** Type of a value in the concrete domain. */
  typedef int abstract_type;
  
  /** Type of a boolean in the concrete domain. */
  typedef bool abstract_bool;
  
  
  
  /*********************************************************************
   * Methods used to deal with Statements.
   ********************************************************************/
  
  /** Concrete interpretation of an assignment.
   * The given value is assigned to the given variable, altering the
   * state of the program.
   * @param[in]  name        Name of the variable to which assign a
   *                         value
   * @param[in]  value       Abstract value to be assigned to the
   *                         variable
   * @param[out] S           State in which operate
   */
  static void Assignment(char name[],
                         abstract_type value,
                         AbstractState<abstract_type> *S)
  {
    S->write(name, value);
  }
  
  
  
  /** Concrete interpretation of a skip.
   * A skip operation typically does nothing.
   */
  static void Skip(void)
  {
    // Do nothing.
  }
  
  
  
  /** Concrete interpretation of a composition.
   * A composition "executes" the first piece of program, altering the
   * state, and then "executes" the second one on the modified state.
   * Another interpretation is that the second piece of code is composed
   * with the first one and that composition is appied to the initial
   * state.
   * @param[in]  first       First piece of code
   * @param[in]  second      Second piece of code
   * @param[in, out] S       State in whici operate
   */
  static void Cat(AST *first,
                  AST *second,
                  AbstractState<abstract_type> *S)
  {
    first->interpret<ConcreteDomain>(S);
    second->interpret<ConcreteDomain>(S);
  }
  
  
  
  /** Concrete interpretation of an if-then-else.
   * The if-then-else statement evaluates a boolean clausole and
   * executes either the "then-branch" or the "else-branch".
   * @param[in]  b           Boolean condition
   * @param[in]  then_branch Piece of program representing the then
   *                         branch
   * @param[in]  else_branch Piece of program representing the else
   *                         branch
   * @param[in, out] S       State in which operate
   */
  static void If(abstract_bool b,
                 AST *then_branch,
                 AST *else_branch,
                 AbstractState<abstract_type> *S)
  {
    if(b) then_branch->interpret<ConcreteDomain>(S);
    else  else_branch->interpret<ConcreteDomain>(S);
  }
  
  
  
  /** Concrete interpretation of a while-do.
   * The while-do statement evaluates a boolean expression and, if that
   * expression evaluates to true, the while body is executed, otherwise
   * the while loop is exited. Then this behaviour is repeated (until
   * the boolean expression evaluates to false in the updated state).
   * @param[in]  b           Piece of program representing the boolean
   *                         expression to be evaluated
   * @param[in]  body        Piece of program representing the while
   *                         body
   * @param[in, out] S       State in which operate
   */
  static void While(AST *b,
                    AST *body,
                    AbstractState<abstract_type> *S)
  {
    while(b->boolean_op<ConcreteDomain>(S))
      body->interpret<ConcreteDomain>(S);
  }
  
  
  
  /** Concrete interpretation of a print.
   * A print construct is meant to print (typically to the standard
   * output channel) the resulting value of an arithmetic expression.
   * @param[in]  a           Result of the arithmetic expression
   */
  static void Print(abstract_type a)
  {
    cout << "> " << a << "\n";
  }
  
  
  
  /*********************************************************************
   * Methods used to deal with Arithmetic Operations.
   ********************************************************************/
  
  /** Concrete interpetation of a read access to a variable.
   * The abstract value associated to the given vatriable is read from
   * the state.
   * @param[in]  literal     Name of the variable to be accessed
   * @param[in]  S           State in which operate
   * @return     Abstract value associated to the variable
   */
  static abstract_type VariableValue(const char literal[],
                                     AbstractState<abstract_type> *S)
  {
    return S->read(literal);
  }
  
  
  
  /** Concrete interpretation of a numeric constant.
   * The given concrete, integer value is mapped to the corresponding
   * abstract value, and that abstract value is returned.
   * @param[in]  a           Concrete value to be "transalted"
   * @return     Abstract representation of the given concrete value
   */
  static abstract_type NumericValue(int a)
  {
    return (abstract_type) a;
  }
  
  
  
  /** Concrete interpretation of an addition.
   * @param[in]  a           Augend
   * @param[in]  b           Addend
   * @return     The sum of a and b
   */
  static abstract_type Sum(abstract_type a, abstract_type b)
  {
    return a + b;
  }
  
  
  
  /** Concrete interpretation of a difference.
   * @param[in]  a           Minuend
   * @param[in]  b           Subtrahend
   * @return     The difference of a and b
   */
  static abstract_type Dif(abstract_type a, abstract_type b)
  {
    return a - b;
  }
  
  
  
  /** Concrete interpretation of a multiplication.
   * @param[in]  a           Multiplicand
   * @param[in]  b           Multiplier
   * @return     The product of a and b
   */
  static abstract_type Prod(abstract_type a, abstract_type b)
  {
    return a * b;
  }
 
  
  
  /** Concrete interpretation of a division.
   * @param[in]  a           Dividend
   * @param[in]  b           Divisor
   * @return     The integer division of a by b
   */
  static abstract_type Div(abstract_type a, abstract_type b)
  {
    return a / b;
  }
 
  
  
  /** Concrete interpretation of the rest of the (integer) division.
   * @param[in]  a           Dividend
   * @param[in]  b           Divisor
   * @return     The rest of the integer division of a by b
   */
  static abstract_type Rem(abstract_type a, abstract_type b)
  {
    return a % b;
  }
 
  
  
  /** Concrete interpretation of the exponentiation.
   * @param[in]  a           Base
   * @param[in]  b           Exponent
   * @return     a to the power of b
   */
  static abstract_type Pow(abstract_type a, abstract_type b)
  {
    abstract_type pow;
    unsigned int i;
    
    if(b < 0){
      return 0;
    }
    
    pow = 1;
    for(i = 0; i < (unsigned int) b; i++){
      pow *= a;
    }
    
    return pow;
  }
 
  
  
  /*********************************************************************
   * Methods used to deal with Boolean Expressions..
   ********************************************************************/
  
  /** Concrete interpretation of a boolean constant.
   * The boolean constant is mapped to its abstract (boolean) value, and
   * that value is returned.
   * @param[in]  literal     Constant boolean value to be "translated"
   * @return     Abstract boolean value
   */
  static abstract_bool Bool(const char literal[])
  {
    return (strcmp(literal, "true") == 0);
  }
  
  
  
  /** Concrete interpetation of the boolean negation.
   * The given (abstract) boolean value is negated.
   * @param[in]  a           Boolean value to be negated
   * @return     negated boolean value
   */
  static abstract_bool Not(abstract_bool a)
  {
    return !a;
  }
  
  
  
  /** Concrete interpretation of the boolean "and" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a and b
   */
  static abstract_bool And(abstract_bool a, abstract_bool b)
  {
    return a && b;
  }
  
  
  
  /** Concrete interpretation of the boolean "or" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a or b
   */
  static abstract_bool Or(abstract_bool a, abstract_bool b)
  {
    return a || b;
  }
  
  
  
  /** Concrete interpretation of the boolean "xor" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a xor b
   */
  static abstract_bool Xor(abstract_bool a, abstract_bool b)
  {
    return (!a && b) || (a && !b);
  }
  
  
  
  /** Concrete interpretation of the boolean "nand" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a nand b
   */
  static abstract_bool Nand(abstract_bool a, abstract_bool b)
  {
    return !(a && b);
  }
  
  
  
  /** Concrete interpretation of the boolean "nor" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a nor b
   */
  static abstract_bool Nor(abstract_bool a, abstract_bool b)
  {
    return !(a || b);
  }
  
  
  
  /** Concrete interpretation of the boolean "nxor" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a nxor b
   */
  static abstract_bool Nxor(abstract_bool a, abstract_bool b)
  {
    return !((!a && b) || (a && !b));
  }
  
  
  
  /** Concrete interpretation of the "less than" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a < b
   */
  static abstract_bool Lt(abstract_type a, abstract_type b)
  {
    return a < b;
  }
  
  
  
  /** Concrete interpretation of the "less or equal" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a <= b
   */
  static abstract_bool Leq(abstract_type a, abstract_type b)
  {
    return a <= b;
  }
  
  
  
  /** Concrete interpretation of the "equal to" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a = b
   */
  static abstract_bool Eq(abstract_type a, abstract_type b)
  {
    return a == b;
  }
  
  
  
  /** Concrete interpretation of the "greater or equal" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a >= b
   */
  static abstract_bool Geq(abstract_type a, abstract_type b)
  {
    return a >= b;
  }
  
  
  
  /** Concrete interpretation of the "greater than" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a > b
   */
  static abstract_bool Gt(abstract_type a, abstract_type b)
  {
    return a > b;
  }
  
  
  
  /** Concrete interpretation of the "not equal" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a != b
   */
  static abstract_bool Neq(abstract_type a, abstract_type b)
  {
    return a != b;
  }
};

#endif

