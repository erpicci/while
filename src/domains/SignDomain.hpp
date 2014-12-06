/** Abstract class used to describe the Sign Domain.
 * 
 * In the Sign Domain, the abstract state store informations only about
 * the sign of a variable: less than zero, zero and greater than zero.
 * Since the domain is equiped with both difference and division
 * arithmetic operation, also "top" and "bottom" are possible values. 
 * 
 * @file SignDomain.h
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @version 1.0
 * @date 14/03/2014
 */

#ifndef _SIGN_DOMAIN_H_
#define _SIGN_DOMAIN_H_



/** Class defining the Sign Domain. */
class SignDomain
{
public:
  /** Type of a value in the abstract domain. */
  typedef enum{
    BOT,       /**< Undefined value */
    NEG,       /**< Negative, less than zero */
    ZERO,      /**< Exactly zero */
    POS,       /**< Positive, greater than zero */
    TOP        /**< Anything, no information */
  } abstract_type;
  
  /** Typedef of a boolean in the abstract domain. */
  typedef enum{
    FALSE,     /**< False boolean value */
    TRUE,      /**< True boolean value */
    UNDEF      /**< Anything, no information */
  } abstract_bool;
  
  
  
  /*********************************************************************
   * Methods used to deal with Statements.
   ********************************************************************/

  /** Abstract interpretation of an assignment.
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
  
  
  
  /** Abstract interpretation of a skip.
   * A skip operation typically does nothing.
   */
  static void Skip(void)
  {
    // Do nothing.
  }
  
  
  
  /** Abstract interpretation of a composition.
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
    first->interpret<SignDomain>(S);
    second->interpret<SignDomain>(S);
  }
  
  
  
  /** Abstract interpretation of an if-then-else.
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
    if(b == TRUE)       then_branch->interpret<SignDomain>(S);
    else if(b == FALSE) else_branch->interpret<SignDomain>(S);
    else                fprintf(stderr, "[Sign::If] I don't know\n");
  }
  
  
  
  /** Abstract interpretation of a while-do.
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
    abstract_bool condition;
    
    condition = b->boolean_op<SignDomain>(S);
    while(condition == TRUE){
      body->interpret<SignDomain>(S);
      condition = b->boolean_op<SignDomain>(S);
    }
    if(condition == UNDEF) fprintf(stderr, "[Sign::While] I don't know.\n");
  }
  
  
  
  /** Abstract interpretation of a print.
   * A print construct is meant to print (typically to the standard
   * output channel) the resulting value of an arithmetic expression.
   * @param[in]  a           Result of the arithmetic expression
   */
  static void Print(abstract_type a){
    switch(a){
      case BOT:  cout << "> bot\n";        break;
      case NEG:  cout << "> negative\n";   break;
      case ZERO: cout << "> zero\n";       break;
      case POS:  cout << "> positive\n";   break;
      case TOP:  cout << "> top\n";        break;
      default:   cout << "> Unkown value"; break;
    }
  }
  
  
  
  /*********************************************************************
   * Methods used to deal with Arithmetic Operations.
   ********************************************************************/

  /** Abstract interpetation of a read access to a variable.
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
  
  
  
  /** Abstract interpretation of a numeric constant.
   * The given concrete, integer value is mapped to the corresponding
   * abstract value, and that abstract value is returned.
   * @param[in]  a           Concrete value to be "transalted"
   * @return     Abstract representation of the given concrete value
   */
  static abstract_type NumericValue(int a)
  {
    if(a < 0)       return NEG;
    else if(a == 0) return ZERO;
    else if(a > 0)  return POS;
    else            return TOP;
  }
  
  
  
  /** Abstract interpretation of an addition.
   * @param[in]  a           Augend
   * @param[in]  b           Addend
   * @return     The sum of a and b
   */
  static abstract_type Sum(abstract_type a, abstract_type b)
  {
    abstract_type sum_matrix[25] = {
      BOT,  BOT,  BOT,   BOT,  BOT,
      BOT,  NEG,  NEG,   TOP,  TOP,
      BOT,  NEG,  ZERO,  POS,  TOP,
      BOT,  TOP,  POS,   POS,  TOP,
      BOT,  TOP,  TOP,   TOP,  TOP
    };
    
    return sum_matrix[a*5 + b];
  }
  
  
  
  /** Abstract interpretation of a difference.
   * @param[in]  a           Minuend
   * @param[in]  b           Subtrahend
   * @return     The difference of a and b
   */
  static abstract_type Dif(abstract_type a, abstract_type b)
  {
    abstract_type dif_matrix[25] = {
      BOT,  BOT,  BOT,  BOT,  BOT,
      BOT,  TOP,  NEG,  NEG,  TOP,
      BOT,  POS,  ZERO, NEG,  TOP,
      BOT,  POS,  POS,  TOP,  TOP,
      BOT,  TOP,  TOP,  TOP,  TOP
    };

    return dif_matrix[a*5 + b];
  }
  
  
  
  /** Abstract interpretation of a multiplication.
   * @param[in]  a           Multiplicand
   * @param[in]  b           Multiplier
   * @return     The product of a and b
   */
  static abstract_type Prod(abstract_type a, abstract_type b)
  {
    abstract_type prod_matrix[25] = {
      BOT,  BOT,  BOT,  BOT,  BOT,
      BOT,  POS,  ZERO, NEG,  TOP,
      BOT,  ZERO, ZERO, ZERO, TOP,
      BOT,  NEG,  ZERO, POS,  TOP,
      BOT,  TOP,  TOP,  TOP,  TOP
    };

    return prod_matrix[a*5 + b];
  }
  
  
  
  /** Abstract interpretation of a division.
   * @param[in]  a           Dividend
   * @param[in]  b           Divisor
   * @return     The integer division of a by b
   */
  static abstract_type Div(abstract_type a, abstract_type b)
  {
    abstract_type div_matrix[25] = {
      BOT,  BOT,  BOT,  BOT,  BOT,
      BOT,  TOP,  BOT,  TOP,  TOP,
      BOT,  ZERO, BOT,  ZERO, ZERO,
      BOT,  TOP,  BOT,  TOP,  TOP,
      BOT,  TOP,  BOT,  TOP,  TOP
    };

    return div_matrix[a*5 + b];
  }
  
  
  
  /** Abstract interpretation of the rest of the (integer) division.
   * @param[in]  a           Dividend
   * @param[in]  b           Divisor
   * @return     The rest of the integer division of a by b
   */
  static abstract_type Rem(abstract_type a, abstract_type b)
  {
    abstract_type rem_matrix[25] = {
      BOT,  BOT,  BOT,  BOT,  BOT,
      BOT,  TOP,  BOT,  TOP,  TOP,
      BOT,  ZERO, BOT,  ZERO, ZERO,
      BOT,  TOP,  BOT,  TOP,  TOP,
      BOT,  TOP,  BOT,  TOP,  TOP
    };

    return rem_matrix[a*5 + b];
  }
  
  
  
  /** Abstract interpretation of the exponentiation.
   * @param[in]  a           Base
   * @param[in]  b           Exponent
   * @return     a to the power of b
   */
  static abstract_type Pow(abstract_type a, abstract_type b)
  {
    abstract_type pow_matrix[25] = {
      BOT,  BOT,  BOT,  BOT,  BOT,
      BOT,  ZERO, POS,  TOP,  TOP,
      BOT,  ZERO, BOT,  ZERO, ZERO,
      BOT,  ZERO, POS,  POS,  POS,
      BOT,  ZERO, POS,  TOP,  TOP
    };

    return pow_matrix[a*5 + b];
  }
  
  
  
  /*********************************************************************
   * Methods used to deal with Boolean Expressions..
   ********************************************************************/

  /** Abstract interpretation of a boolean constant.
   * The boolean constant is mapped to its abstract (boolean) value, and
   * that value is returned.
   * @param[in]  literal     Constant boolean value to be "translated"
   * @return     Abstract boolean value
   */
  static abstract_bool Bool(const char literal[])
  {
    return (strcmp(literal, "true") == 0) ? TRUE : FALSE;
  }
  
  
  
  /** Abstract interpetation of the boolean negation.
   * The given (abstract) boolean value is negated.
   * @param[in]  a           Boolean value to be negated
   * @return     negated boolean value
   */
  static abstract_bool Not(abstract_bool a)
  {
    if(a == TRUE)       return FALSE;
    else if(a == FALSE) return TRUE;
    else                return UNDEF;
  }
  
  
  
  /** Abstract interpretation of the boolean "and" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a and b
   */
  static abstract_bool And(abstract_bool a, abstract_bool b)
  {
    abstract_bool and_matrix[9] = {
      FALSE, FALSE, UNDEF,
      FALSE, TRUE,  UNDEF,
      UNDEF, UNDEF, UNDEF
    };
    
    return and_matrix[a*3 + b];
  }
  
  
  
  /** Abstract interpretation of the boolean "or" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a or b
   */
  static abstract_bool Or(abstract_bool a, abstract_bool b)
  {
    abstract_bool or_matrix[9] = {
      FALSE, TRUE,  UNDEF,
      TRUE,  TRUE,  TRUE,
      UNDEF, TRUE,  UNDEF
    };

    return or_matrix[a*3 + b];
  }
  
  
  
  /** Abstract interpretation of the boolean "xor" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a xor b
   */
  static abstract_bool Xor(abstract_bool a, abstract_bool b)
  {
    abstract_bool xor_matrix[9] = {
      FALSE, TRUE,  UNDEF,
      TRUE,  FALSE, UNDEF,
      UNDEF, UNDEF, UNDEF
    };

    return xor_matrix[a*3 + b];
  }
  
  
  
  /** Abstract interpretation of the boolean "nand" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a nand b
   */
  static abstract_bool Nand(abstract_bool a, abstract_bool b)
  {
    abstract_bool nand_matrix[9] = {
      TRUE,  TRUE,  UNDEF,
      TRUE,  FALSE, UNDEF,
      UNDEF, TRUE,  UNDEF
    };

    return nand_matrix[a*3 + b];
  }
  
  
  
  /** Abstract interpretation of the boolean "nor" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a nor b
   */
  static abstract_bool Nor(abstract_bool a, abstract_bool b)
  {
    abstract_bool nor_matrix[9] = {
      TRUE,  FALSE, UNDEF,
      FALSE, FALSE, FALSE,
      UNDEF, FALSE, UNDEF
    };

    return nor_matrix[a*3 + b];
  }
  
  
  
  /** Abstract interpretation of the boolean "nxor" operation.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a nxor b
   */
  static abstract_bool Nxor(abstract_bool a, abstract_bool b)
  {
    abstract_bool nxor_matrix[9] = {
      TRUE,  FALSE, UNDEF,
      FALSE, TRUE,  UNDEF,
      UNDEF, UNDEF, UNDEF
    };

    return nxor_matrix[a*3 + b];
  }
  
  
  
  /** Abstract interpretation of the "less than" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a < b
   */
  static abstract_bool Lt(abstract_type a, abstract_type b)
  {
    abstract_bool lt_matrix[25] = {
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF,
      UNDEF, UNDEF, TRUE,  TRUE,  UNDEF,
      UNDEF, FALSE, FALSE, TRUE,  UNDEF,
      UNDEF, FALSE, FALSE, UNDEF, UNDEF,
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF
    };
    
    return lt_matrix[a*5 + b];
  }
  
  
  
  /** Abstract interpretation of the "less or equal" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a <= b
   */
  static abstract_bool Leq(abstract_type a, abstract_type b)
  {
    abstract_bool leq_matrix[25] = {
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF,
      UNDEF, UNDEF, TRUE,  TRUE,  UNDEF,
      UNDEF, FALSE, TRUE,  TRUE,  UNDEF,
      UNDEF, FALSE, FALSE, UNDEF, UNDEF,
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF
    };

    return leq_matrix[a*5 + b];
  }
  
  
  
  /** Abstract interpretation of the "equal to" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a = b
   */
  static abstract_bool Eq(abstract_type a, abstract_type b)
  {
    abstract_bool eq_matrix[25] = {
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF,
      UNDEF, UNDEF, FALSE, FALSE, UNDEF,
      UNDEF, FALSE, TRUE,  FALSE, UNDEF,
      UNDEF, FALSE, FALSE, UNDEF, UNDEF,
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF
    };
    
    return eq_matrix[a*5 + b];
  }
  
  
  
  /** Abstract interpretation of the "greater or equal" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a >= b
   */
  static abstract_bool Geq(abstract_type a, abstract_type b)
  {
    abstract_bool geq_matrix[25] = {
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF,
      UNDEF, UNDEF, FALSE, FALSE, UNDEF,
      UNDEF, TRUE,  TRUE,  FALSE, UNDEF,
      UNDEF, TRUE,  TRUE,  UNDEF, UNDEF,
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF
    };
    
    return geq_matrix[a*5 + b];
  }
  
  
  
  /** Abstract interpretation of the "greater than" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a > b
   */
  static abstract_bool Gt(abstract_type a, abstract_type b)
  {
    abstract_bool gt_matrix[25] = {
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF,
      UNDEF, UNDEF, FALSE, FALSE, UNDEF,
      UNDEF, TRUE,  FALSE, FALSE, UNDEF,
      UNDEF, TRUE,  TRUE,  UNDEF, UNDEF,
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF
    };
    
    return gt_matrix[a*5 + b];
  }
  
  
  
  /** Abstract interpretation of the "not equal" comparison.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @return     The evaluation of a != b
   */
  static abstract_bool Neq(abstract_type a, abstract_type b)
  {
    abstract_bool neq_matrix[25] = {
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF,
      UNDEF, UNDEF, TRUE,  TRUE,  UNDEF,
      UNDEF, TRUE,  FALSE, TRUE,  UNDEF,
      UNDEF, TRUE,  TRUE,  UNDEF, UNDEF,
      UNDEF, UNDEF, UNDEF, UNDEF, UNDEF
    };
    
    return neq_matrix[a*5 + b];
  }
};


#endif
