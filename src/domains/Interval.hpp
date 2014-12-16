/** Interval abstract interpretation.
 * Class handling the abstract interpretation in the Interval abstract
 * domain.
 * 
 * @file Interval.hpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @ingroup domains
 */
#ifndef _INTERVAL_HPP_
#define _INTERVAL_HPP_

#include <string>
#include <vector>

using namespace std;

/** Class representing the interval domain abstraction.
 * In the interval domain, every value is identified by an interval that
 * contains the concrete value.
 */
class Interval
{
  public:
  /** 'Less than' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not
   *                         smaller than the second one
   */
  bool operator< (Interval other);
  
  
  /** 'Less than or equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not
   *                         smaller than or equal to the second one
   */
  bool operator<=(Interval other);
  
  
  /** 'Equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not equal
   *                         to the second one
   */
  bool operator==(Interval other);
  
  
  /** 'Greater than or equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure greater
   *                         than or equal to the second one
   */
  bool operator>=(Interval other);


  /** 'Greater' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure greater
   *                         than the second one
   */
  bool operator> (Interval other);
  
  
  /** 'Not equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not equal
   *                         to the second one
   */
  bool operator!=(Interval other);
  
  
  /** Identity operator overloading.
   * @retval     Interval    Identity of the value
   */
  Interval operator+();
  
  
  /** Opposite operator overloading.
   * @retval     Interval    Opposite of the value
   */
  Interval operator-();
  
  
  /** Sum operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Interval    Sum of the current and the given values
   */
  Interval operator+(Interval other);


  /** Subtraction operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Interval    Difference between the current and the
   *                         given values
   */
  Interval operator-(Interval other);


  /** Multiplication operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Interval    Product of the current and the given values
   */
  Interval operator*(Interval other);


  /** Integer division operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Interval    Integer division between the current and
   *                         the given values
   */
  Interval operator/(Interval other);


  /** Remainder of the integer division operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Interval    Remainder of the integer division between
   *                         the current and the given value
   */
  Interval operator%(Interval other);


  /** Power raising operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Interval    Current value raised to the power of the
   *                         given one
   */
  Interval operator^(Interval other);
  
  
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
  static bool equal(Interval a, Interval b);
  
  
  /** Least upperbound between two values in the abstract domain is
   * computed.
   * @param[in]  a           First abstract value
   * @param[in]  b           Second abstract value
   * @retval     Interval    Least upperbound of a and b
   */
  static Interval lub(Interval a, Interval b);
  
  
  /** Widening operator.
   * No actual widening is used in the Interval domain.
   * @param[in]  a           Previous value
   * @param[in]  b           Current value
   * @retval     Interval    Widened value
   */
  static Interval nabla(Interval a, Interval b);
  
  
  /** Abstraction function.
   * For the particular case when given set is a singleton.
   * @param[in]  value       Value of the concrete domain
   * @retval     Interval    Abstract value corresponding to the
   *                         given concrete value
   */
  static Interval alpha(int value);
  
  
  /** Abstraction function.
   * @param[in]  values      Subset of the concrete domain
   * @retval     Interval    Abstract value corresponding to the least
   *                         upperbound of the concrete values
   */
  static Interval alpha(vector<int> values);
  
  
  /** Constant method returning an instance of the "I don't know" value.
   * @retval     Interval        Value representing no information
   */
  static Interval top();
  
  
  private:
  bool bottom;          ///< True if the value is bottom
  long lBound;          ///< Left bound of the interval
  long rBound;          ///< Right bound of the interval
};
#endif
