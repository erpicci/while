/** Symmetric interval abstract interpretation.
 * Class handling the abstract interpretation in the Symmetric SInterval
 * abstract domain.
 * 
 * @file SInterval.hpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @ingroup domains
 */
#ifndef _SINTERVAL_HPP_
#define _SINTERVAL_HPP_

#include <string>
#include <vector>

using namespace std;

/** Class representing the symmetric interval domain abstraction.
 * In the symmetric interval domain, every value is identified by an
 * interval that contains the concrete value. Such interval is
 * identified by a central point and an offset which extends in both
 * directions.
 */
class SInterval
{
  public:
  /** 'Less than' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not
   *                         smaller than the second one
   */
  bool operator< (SInterval other);
  
  
  /** 'Less than or equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not
   *                         smaller than or equal to the second one
   */
  bool operator<=(SInterval other);
  
  
  /** 'Equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not equal
   *                         to the second one
   */
  bool operator==(SInterval other);
  
  
  /** 'Greater than or equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure greater
   *                         than or equal to the second one
   */
  bool operator>=(SInterval other);


  /** 'Greater' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure greater
   *                         than the second one
   */
  bool operator> (SInterval other);
  
  
  /** 'Not equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not equal
   *                         to the second one
   */
  bool operator!=(SInterval other);
  
  
  /** Identity operator overloading.
   * @retval     SInterval    Identity of the value
   */
  SInterval operator+();
  
  
  /** Opposite operator overloading.
   * @retval     SInterval    Opposite of the value
   */
  SInterval operator-();
  
  
  /** Sum operator overloading.
   * @param[in]  other       Right-operand
   * @retval     SInterval    Sum of the current and the given values
   */
  SInterval operator+(SInterval other);


  /** Subtraction operator overloading.
   * @param[in]  other       Right-operand
   * @retval     SInterval    Difference between the current and the
   *                         given values
   */
  SInterval operator-(SInterval other);


  /** Multiplication operator overloading.
   * @param[in]  other       Right-operand
   * @retval     SInterval    Product of the current and the given values
   */
  SInterval operator*(SInterval other);


  /** Integer division operator overloading.
   * @param[in]  other       Right-operand
   * @retval     SInterval    Integer division between the current and
   *                         the given values
   */
  SInterval operator/(SInterval other);


  /** Remainder of the integer division operator overloading.
   * @param[in]  other       Right-operand
   * @retval     SInterval    Remainder of the integer division between
   *                         the current and the given value
   */
  SInterval operator%(SInterval other);


  /** Power raising operator overloading.
   * @param[in]  other       Right-operand
   * @retval     SInterval    Current value raised to the power of the
   *                         given one
   */
  SInterval operator^(SInterval other);
  
  
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
  static bool equal(SInterval a, SInterval b);
  
  
  /** Least upperbound between two values in the abstract domain is
   * computed.
   * @param[in]  a           First abstract value
   * @param[in]  b           Second abstract value
   * @retval     SInterval    Least upperbound of a and b
   */
  static SInterval lub(SInterval a, SInterval b);
  
  
  /** Widening operator.
   * No actual widening is used in the SInterval domain.
   * @param[in]  a           Previous value
   * @param[in]  b           Current value
   * @retval     SInterval    Widened value
   */
  static SInterval nabla(SInterval a, SInterval b);
  
  
  /** Abstraction function.
   * For the particular case when given set is a singleton.
   * @param[in]  value       Value of the concrete domain
   * @retval     SInterval    Abstract value corresponding to the
   *                         given concrete value
   */
  static SInterval alpha(int value);
  
  
  /** Abstraction function.
   * @param[in]  values      Subset of the concrete domain
   * @retval     SInterval    Abstract value corresponding to the least
   *                         upperbound of the concrete values
   */
  static SInterval alpha(vector<int> values);
  
  
  /** Constant method returning an instance of the "I don't know" value.
   * @retval     SInterval        Value representing no information
   */
  static SInterval top();
  
  
  private:
  long center;          ///< Central point of the symmetric interval
  long offset;          ///< Offset
  bool bottom;          ///< True if the value is bottom
};
#endif
