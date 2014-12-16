/** Sign abstract interpretation.
 * Class handling the abstract interpretation in the Sign abstract
 * domain.
 * 
 * @file Sign.hpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @ingroup domains
 */
#ifndef _SIGN_HPP_
#define _SIGN_HPP_

#include <string>
#include <vector>
#include "AbstractDomain.hpp"

using namespace std;

/** Class representing the sign domain abstraction.
 * In the sign domain, only the sign of an expression is considered,
 * namely minus, zero, positive. Bottom and top value are added in order
 * to achive correctness.
 */
class Sign
{
  public:
  /** 'Less than' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not
   *                         smaller than the second one
   */
  bool operator< (Sign other);
  
  
  /** 'Less than or equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not
   *                         smaller than or equal to the second one
   */
  bool operator<=(Sign other);
  
  
  /** 'Equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not equal
   *                         to the second one
   */
  bool operator==(Sign other);
  
  
  /** 'Greater than or equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure greater
   *                         than or equal to the second one
   */
  bool operator>=(Sign other);


  /** 'Greater' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure greater
   *                         than the second one
   */
  bool operator> (Sign other);
  
  
  /** 'Not equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not equal
   *                         to the second one
   */
  bool operator!=(Sign other);
  
  
  /** Identity operator overloading.
   * @retval     Sign        Identity of the value
   */
  Sign operator+();
  
  
  /** Opposite operator overloading.
   * @retval     Sign        Opposite of the value
   */
  Sign operator-();
  
  
  /** Sum operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Sign        Sum of the current and the given values
   */
  Sign operator+(Sign other);


  /** Subtraction operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Sign        Difference between the current and the
   *                         given values
   */
  Sign operator-(Sign other);


  /** Multiplication operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Sign        Product of the current and the given values
   */
  Sign operator*(Sign other);


  /** Integer division operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Sign        Integer division between the current and
   *                         the given values
   */
  Sign operator/(Sign other);


  /** Remainder of the integer division operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Sign        Remainder of the integer division between
   *                         the current and the given value
   */
  Sign operator%(Sign other);


  /** Power raising operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Sign        Current value raised to the power of the
   *                         given one
   */
  Sign operator^(Sign other);
  
  
  /** Cast to const char * operator overloading.
   * This method is used to provide a textual representation of the
   * value.
   * @retval     const char * Textual representation of the value
   */
  operator const char * ();
  
    
  /** Predicate testing whether two values are equal.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @retval     bool        True if and only if values are precisely
   *                         equal
   */
  static bool equal(Sign a, Sign b);
  
  
  /** Least upperbound between two values in the abstract domain is
   * computed.
   * @param[in]  a           First abstract value
   * @param[in]  b           Second abstract value
   * @retval     Sign        Least upperbound of a and b
   */
  static Sign lub(Sign a, Sign b);
  
  
  /** Widening operator.
   * No actual widening is used in the Sign domain.
   * @param[in]  a           Previous value
   * @param[in]  b           Current value
   * @retval     Sign        Widened value
   */
  static Sign nabla(Sign a, Sign b);
  
  
  /** Abstraction function.
   * For the particular case when given set is a singleton.
   * @param[in]  value       Value of the concrete domain
   * @retval     Sign        Abstract value corresponding to the
   *                         given concrete value
   */
  static Sign alpha(int value);
  
  
  /** Abstraction function.
   * @param[in]  values      Subset of the concrete domain
   * @retval     Sign        Abstract value corresponding to the least
   *                         upperbound of the concrete values
   */
  static Sign alpha(vector<int> values);
  
  
  /** Constant method returning an instance of the "I don't know" value.
   * @retval     Sign        Value representing no information
   */
  static Sign top();
  
  
  private:
  /** Type representing every possible value in the domain. */
  typedef enum{
    BOT,                ///< Bottom
    MINUS,              ///< Negative number
    ZERO,               ///< Exactly zero
    PLUS,               ///< Positive number
    TOP                 ///< Top
  } signType;
  
  signType value;       ///< Abstract value
};
#endif
