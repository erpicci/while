/** BlackHole abstract interpretation.
 * Class handling the abstract interpretation in the BlackHole abstract
 * domain.
 * 
 * @file BlackHole.cpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @ingroup domains
 */
#include "BlackHole.hpp"


/** 'Less than' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not
 *                         smaller than the second one
 */
bool BlackHole::operator< (BlackHole other)
{
  (void) other;
  return true;
}


/** 'Less than or equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not
 *                         smaller than or equal to the second one
 */
bool BlackHole::operator<=(BlackHole other)
{
  (void) other;
  return true;
}


/** 'Equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not equal
 *                         to the second one
 */
bool BlackHole::operator==(BlackHole other)
{
  (void) other;
  return true;
}


/** 'Greater than or equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure greater
 *                         than or equal to the second one
 */
bool BlackHole::operator>=(BlackHole other)
{
  (void) other;
  return true;
}


/** 'Greater' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure greater
 *                         than the second one
 */
bool BlackHole::operator> (BlackHole other)
{
  (void) other;
  return true;
}


/** 'Not equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not equal
 *                         to the second one
 */
bool BlackHole::operator!=(BlackHole other)
{
  (void) other;
  return true;
}


/** Identity operator overloading.
 * @retval     BlackHole   Identity of the value
 */
BlackHole BlackHole::operator+()
{
  return BlackHole();
}


/** Opposite operator overloading.
 * @retval     BlackHole   Opposite of the value
 */
BlackHole BlackHole::operator-()
{
  return BlackHole();
}


/** Sum operator overloading.
 * @param[in]  other       Right-operand
 * @retval     BlackHole   Sum of the current and the given values
 */
BlackHole BlackHole::operator+(BlackHole other)
{
  (void) other;
  return BlackHole();
}


/** Subtraction operator overloading.
 * @param[in]  other       Right-operand
 * @retval     BlackHole   Difference between the current and the
 *                         given values
 */
BlackHole BlackHole::operator-(BlackHole other)
{
  (void) other;
  return BlackHole();
}


/** Multiplication operator overloading.
 * @param[in]  other       Right-operand
 * @retval     BlackHole   Product of the current and the given values
 */
BlackHole BlackHole::operator*(BlackHole other)
{
  (void) other;
  return BlackHole();
}


/** Integer division operator overloading.
 * @param[in]  other       Right-operand
 * @retval     BlackHole   Integer division between the current and
 *                         the given values
 */
BlackHole BlackHole::operator/(BlackHole other)
{
  (void) other;
  return BlackHole();
}


/** Remainder of the integer division operator overloading.
 * @param[in]  other       Right-operand
 * @retval     BlackHole   Remainder of the integer division between
 *                         the current and the given value
 */
BlackHole BlackHole::operator%(BlackHole other)
{
  (void) other;
  return BlackHole();
}


/** Power raising operator overloading.
 * @param[in]  other       Right-operand
 * @retval     BlackHole   Current value raised to the power of the
 *                         given one
 */
BlackHole BlackHole::operator^(BlackHole other)
{
  (void) other;
  return BlackHole();
}


/** Cast to const char * operator overloading.
 * This method is used to provide a textual representation of the
 * value.
 * @retval     const char * Textual representation of the value
 */
BlackHole::operator const char * ()
{
  return "I don't know";
}

  
/** Predicate testing whether two values are equal.
 * @param[in]  a           First operand
 * @param[in]  b           Second operand
 * @retval     bool        True if and only if values are precisely
 *                         equal
 */
bool BlackHole::equal(BlackHole a, BlackHole b)
{
  (void) a;
  (void) b;
  return true;
}


/** Least upperbound between two values in the abstract domain is
 * computed.
 * @param[in]  a           First abstract value
 * @param[in]  b           Second abstract value
 * @retval     BlackHole   Least upperbound of a and b
 */
BlackHole BlackHole::lub(BlackHole a, BlackHole b)
{
  (void) a;
  (void) b;
  return BlackHole();
}


/** Widening operator.
 * No actual widening is used in the BlackHole domain.
 * @param[in]  a           Previous value
 * @param[in]  b           Current value
 * @retval     BlackHole   Widened value
 */
BlackHole BlackHole::nabla(BlackHole a, BlackHole b)
{
  (void) a;
  (void) b;
  return BlackHole();
}


/** Abstraction function.
 * For the particular case when given set is a singleton.
 * @param[in]  value       Value of the concrete domain
 * @retval     BlackHole   Abstract value corresponding to the
 *                         given concrete value
 */
BlackHole BlackHole::alpha(int value)
{
  (void) value;
  return BlackHole();
}


/** Abstraction function.
 * @param[in]  values      Subset of the concrete domain
 * @retval     BlackHole   Abstract value corresponding to the least
 *                         upperbound of the concrete values
 */
BlackHole BlackHole::alpha(vector<int> values)
{
  (void) values;
  return BlackHole();
}


/** Constant method returning an instance of the "I don't know" value.
 * @retval     BlackHole   Value representing no information
 */
BlackHole BlackHole::top()
{
  return BlackHole();
}
