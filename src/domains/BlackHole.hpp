/** BlackHole abstract interpretation.
 * Class handling the abstract interpretation in the BlackHole abstract
 * domain.
 * 
 * @file BlackHole.hpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @ingroup domains
 */
#ifndef _BLACKHOLE_HPP_
#define _BLACKHOLE_HPP_

#include <string>
#include <vector>

using namespace std;

/** Class representing the blackhole domain abstraction.
 * In the blackhole domain, every data goes to a place of permanent
 * oblivion. In words, the only possible answer is "I don't know".
 */
class BlackHole
{
  public:
  /** 'Less than' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not
   *                         smaller than the second one
   */
  bool operator< (BlackHole other);
  
  
  /** 'Less than or equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not
   *                         smaller than or equal to the second one
   */
  bool operator<=(BlackHole other);
  
  
  /** 'Equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not equal
   *                         to the second one
   */
  bool operator==(BlackHole other);
  
  
  /** 'Greater than or equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure greater
   *                         than or equal to the second one
   */
  bool operator>=(BlackHole other);


  /** 'Greater' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure greater
   *                         than the second one
   */
  bool operator> (BlackHole other);
  
  
  /** 'Not equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not equal
   *                         to the second one
   */
  bool operator!=(BlackHole other);
  
  
  /** Identity operator overloading.
   * @retval     BlackHole   Identity of the value
   */
  BlackHole operator+();
  
  
  /** Opposite operator overloading.
   * @retval     BlackHole   Opposite of the value
   */
  BlackHole operator-();
  
  
  /** Sum operator overloading.
   * @param[in]  other       Right-operand
   * @retval     BlackHole   Sum of the current and the given values
   */
  BlackHole operator+(BlackHole other);


  /** Subtraction operator overloading.
   * @param[in]  other       Right-operand
   * @retval     BlackHole   Difference between the current and the
   *                         given values
   */
  BlackHole operator-(BlackHole other);


  /** Multiplication operator overloading.
   * @param[in]  other       Right-operand
   * @retval     BlackHole   Product of the current and the given values
   */
  BlackHole operator*(BlackHole other);


  /** Integer division operator overloading.
   * @param[in]  other       Right-operand
   * @retval     BlackHole   Integer division between the current and
   *                         the given values
   */
  BlackHole operator/(BlackHole other);


  /** Remainder of the integer division operator overloading.
   * @param[in]  other       Right-operand
   * @retval     BlackHole   Remainder of the integer division between
   *                         the current and the given value
   */
  BlackHole operator%(BlackHole other);


  /** Power raising operator overloading.
   * @param[in]  other       Right-operand
   * @retval     BlackHole   Current value raised to the power of the
   *                         given one
   */
  BlackHole operator^(BlackHole other);
  
  
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
  static bool equal(BlackHole a, BlackHole b);
  
  
  /** Least upperbound between two values in the abstract domain is
   * computed.
   * @param[in]  a           First abstract value
   * @param[in]  b           Second abstract value
   * @retval     BlackHole   Least upperbound of a and b
   */
  static BlackHole lub(BlackHole a, BlackHole b);
  
  
  /** Widening operator.
   * No actual widening is used in the BlackHole domain.
   * @param[in]  a           Previous value
   * @param[in]  b           Current value
   * @retval     BlackHole   Widened value
   */
  static BlackHole nabla(BlackHole a, BlackHole b);
  
  
  /** Abstraction function.
   * For the particular case when given set is a singleton.
   * @param[in]  value       Value of the concrete domain
   * @retval     BlackHole   Abstract value corresponding to the
   *                         given concrete value
   */
  static BlackHole alpha(int value);
  
  
  /** Abstraction function.
   * @param[in]  values      Subset of the concrete domain
   * @retval     BlackHole   Abstract value corresponding to the least
   *                         upperbound of the concrete values
   */
  static BlackHole alpha(vector<int> values);
  
  
  /** Constant method returning an instance of the "I don't know" value.
   * @retval     BlackHole   Value representing no information
   */
  static BlackHole top();
};
#endif
