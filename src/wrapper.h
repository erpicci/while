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
 * @file wrapper.h
 * @author Marco Zanell <marco.zanella.9@studenti.unipd.it>
 * @version 1.0
 * @date 13/03/2014
 */

#ifndef _WRAPPER_H_
#define _WRAPPER_H_



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
void *_assignment(void *variable, void *expression);



/** Abstract "skip" subtree.
 * An abstract subtree representing a skip operation is created.
 * @return     Abstract syntax (sub) tree representing a skip
 */
void *_skip(void);



/** Abstract "concatenation" subtree.
 * An abstract subtree representing a concatenation operation is
 * created.
 * @param[in]  first         Abstract subtree representing the first
 *                           statement
 * @param[in]  second        Abstract subtree representing the second
 *                           statement
 * @return     Abstract syntax (sub) tree representing a concatenarion
 */
void *_concatenation(void *first, void *second);



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
void *_if(void *condition, void *then_branch, void *else_branch);



/** Abstract "while...do" subtree.
 * An abstract subtree representing a while iteration is created.
 * @param[in]  condition     Abstract subtree representing the condition
 *                           over which iterate
 * @param[in]  body          Abstract subtree representing the body of
 *                           the while loop
 * @return     Abstract syntax (sub) tree representing the while loop
 *             statement
 */
void *_while(void *condition, void *body);



/** Abstract "print" subtree.
 * An abstract subtree representing a print statement is created.
 * @param[in]  expression    Abstract subtree representing the
 *                           arithmetic expression to print
 * @return     Abstract syntax (sub) tree representing the print
 *             statement
 */
void *_print(void *expression);



/***********************************************************************
 * Functions dealing with Arithmetic Expressions.
 **********************************************************************/

/** Abstract "numeric constant" subtree.
 * An abstract subtree representing a numeric constant is created.
 * @param[in]  value         Numeric value of the constant
 * @return     Abstract syntax subtree representing the numeric constant
 */
void *_constant(int value);



/** Abstract "variable" subtree.
 * An abstract subtree representing a variable is created.
 * @param[in]  identifier    Name of the variable
 * @return     Abstract syntax subtree representing the variable
 */ 
void *_variable(const char identifier[]);



/** Abstract "sum" subtree.
 * An abstract subtree representing an arithmetic sum is created.
 * @param[in]  first_op      Abstract subtree representing the first
 *                           operand
 * @param[in]  second_op     Abstarct subtree representin the second
 *                           operand
 * @return     Abstract syntax subtree representing an arithmetic sum
 */
void *_sum(void *first_op, void *second_op);



/** Abstract "difference" subtree.
 * An abstract subtree representing an arithmetic difference is created.
 * @param[in]  first_op      Abstract subtree representing the first
 *                           operand
 * @param[in]  second_op     Abstarct subtree representin the second
 *                           operand
 * @return     Abstract syntax subtree representing an arithmetic
 *             difference
 */
void *_difference(void *first_op, void *second_op);



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
void *_product(void *first_op, void *second_op);



/** Abstract "division" subtree.
 * An abstract subtree representing an integer division is created.
 * @param[in]  first_op      Abstract subtree representing the first
 *                           operand
 * @param[in]  second_op     Abstarct subtree representin the second
 *                           operand
 * @return     Abstract syntax subtree representing an integer
 *             division
 */
void *_division(void *first_op, void *second_op);



/** Abstract "rem" subtree.
 * An abstract subtree representing an integer rem is created.
 * @param[in]  first_op      Abstract subtree representing the first
 *                           operand
 * @param[in]  second_op     Abstarct subtree representin the second
 *                           operand
 * @return     Abstract syntax subtree representing an integer rem
 */
void *_rem(void *first_op, void *second_op);



/** Abstract "power" subtree.
 * An abstract subtree representing an integer power is created.
 * @param[in]  base          Abstract subtree representing the base
 * @param[in]  exponent      Abstarct subtree representin the exponent
 * @return     Abstract syntax subtree representing an integer power
 */
void *_pow(void *base, void *exponent);



/***********************************************************************
 * Functions dealing with Boolean Expressions.
 **********************************************************************/

/** Abstract boolean constant.
 * An abstract subtree representing a boolean constant is created.
 * @param[in]  constant      String representing the boolean constant
 * @return     Abstract syntax subtree representing a boolean constant
 */
void *_boolean(const char constant[]);



/** Abstract boolean negation.
 * An abstract subtree representing a boolean negation is created.
 * @param[in]  boolean       Abstract subtree representing the boolean
 *                           expression to be negated
 * @return     Abstract syntax subtree representing the boolean negation
 */
void *_not(void *boolean);



/** Abstract "and" subtree.
 * An abstract subtree representing an and boolean operation is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           boolean operand
 * @param[in]  second        Abstract subtree representing the second
 *                           boolean operand
 * @return     Abstract syntax subtree representing the and boolean
 *             expression
 */
void *_and(void *first, void *second);



/** Abstract "or" subtree.
 * An abstract subtree representing an or boolean operation is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           boolean operand
 * @param[in]  second        Abstract subtree representing the second
 *                           boolean operand
 * @return     Abstract syntax subtree representing the or boolean
 *             expression
 */
void *_or(void *first, void *second);



/** Abstract "xor" subtree.
 * An abstract subtree representing an xor boolean operation is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           boolean operand
 * @param[in]  second        Abstract subtree representing the second
 *                           boolean operand
 * @return     Abstract syntax subtree representing the xor boolean
 *             expression
 */
void *_xor(void *first, void *second);



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
void *_nand(void *first, void *second);



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
void *_nor(void *first, void *second);



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
void *_nxor(void *first, void *second);



/** Abstract "less than" subtree.
 * An abstract subtree representing a less than comparison is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           arithmetic operand
 * @param[in]  second        Abstract subtree representing the second
 *                           arithmetic operand
 * @return     Abstract syntax subtree representing the less than
 *             comparison
 */
void *_lt(void *first, void *second);



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
void *_leq(void *first, void *second);



/** Abstract "equal" subtree.
 * An abstract subtree representing an equality comparison is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           arithmetic operand
 * @param[in]  second        Abstract subtree representing the second
 *                           arithmetic operand
 * @return     Abstract syntax subtree representing the equality
 *             comparison
 */
void *_eq(void *first, void *second);



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
void *_geq(void *first, void *second);



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
void *_gt(void *first, void *second);



/** Abstract "not equal" subtree.
 * An abstract subtree representing an inequality comparison is created.
 * @param[in]  first         Abstract subtree representing the first
 *                           arithmetic operand
 * @param[in]  second        Abstract subtree representing the second
 *                           arithmetic operand
 * @return     Abstract syntax subtree representing the inequality
 *             comparison
 */
void *_neq(void *first, void *second);



/** The list of variables encountered during the parsing is returned.
 * A matrix of characters is allocated. When done, memory frees should
 * be called.
 * @param[out] variables     Pointer to the array of names
 * @param[out] number        Number of encountered variables
 */
void variables(char ***variables, unsigned int *number);

#endif

