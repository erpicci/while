/** Sign abstract interpretation.
 * Class handling the abstract interpretation in the Sign abstract
 * domain.
 * 
 * @file Sign.cpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @ingroup domains
 */
#include "Sign.hpp"


/** 'Less than' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not smaller
 *                         than the second one
 */
bool Sign::operator< (Sign other)
{
  bool table[] = {
    false, false, false, false, false,
    false, true,  true,  true,  true,
    false, false, false, true,  true,
    false, false, false, true,  true,
    false, true,  true,  true,  true
  };
  
  return table[value * 5 + other.value];
}


/** 'Less than or equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not smaller
 *                         than or equal to the second one
 */
bool Sign::operator<=(Sign other)
{
  bool table[] = {
    false, false, false, false, false,
    false, true,  true,  true,  true,
    false, false, true,  true,  true,
    false, false, false, true,  true,
    false, true,  true,  true,  true
  };
  
  return table[value * 5 + other.value];
}


/** 'Equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not equal
 *                         to the second one
 */
bool Sign::operator==(Sign other)
{
  bool table[] = {
    false, false, false, false, false,
    false, true,  false, false, true,
    false, false, true,  false, true,
    false, false, false, true,  true,
    false, true,  true,  true,  true
  };
  
  return table[value * 5 + other.value];
}


/** 'Greater than or equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure greater
 *                         than or equal to the second one
 */
bool Sign::operator>=(Sign other)
{
  return other <= *this;
}


/** 'Greater' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure greater
 *                         than the second one
 */
bool Sign::operator> (Sign other)
{
  return other < *this;
}


/** 'Not equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not equal
 *                         to the second one
 */
bool Sign::operator!=(Sign other)
{
  return !(value == BOT || other.value == BOT ||
          (value == ZERO && other.value == ZERO));
}


/** Identity operator overloading.
 * @retval     Sign        Identity of the value
 */
Sign Sign::operator+()
{
  return *this;
}


/** Opposite operator overloading.
 * @retval     Sign        Opposite of the value
 */
Sign Sign::operator-()
{
  Sign opp;
  signType table[] = {BOT, PLUS, ZERO, MINUS, TOP};
  
  opp.value = table[value];
  
  return opp;
}

  
/** Sum operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Sign        Sum of the current and the given values
 */
Sign Sign::operator+(Sign other)
{
  Sign sum;
  signType table[] = {
    BOT,   BOT,   BOT,   BOT,   BOT,
    BOT,   MINUS, MINUS, TOP,   TOP,
    BOT,   MINUS, ZERO,  PLUS,  TOP,
    BOT,   TOP,   PLUS,  PLUS,  TOP,
    BOT,   TOP,   TOP,   TOP,   TOP
  };
  
  sum.value = table[value * 5 + other.value];
  
  return sum;
}


/** Subtraction operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Sign        Difference between the current and the
 *                         given values
 */
Sign Sign::operator-(Sign other)
{
  Sign sub;
  signType table[] = {
    BOT,  BOT,   BOT,   BOT,   BOT,
    BOT,  TOP,   MINUS, MINUS, TOP,
    BOT,  PLUS,  ZERO,  MINUS, TOP,
    BOT,  PLUS,  PLUS,  TOP,   TOP,
    BOT,  TOP,   TOP,   TOP,   TOP
  };
  
  sub.value = table[value * 5 + other.value];
  
  return sub;
}


/** Multiplication operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Sign        Product of the current and the given values
 */
Sign Sign::operator*(Sign other)
{
  Sign mul;
  signType table[] = {
    BOT,   BOT,   BOT,   BOT,   BOT,
    BOT,   PLUS,  ZERO,  MINUS, TOP,
    BOT,   ZERO,  ZERO,  ZERO,  ZERO,
    BOT,   MINUS, ZERO,  PLUS,  TOP,
    BOT,   TOP,   ZERO,  TOP,   TOP
  };
  
  mul.value = table[value * 5 + other.value];
  
  return mul;
}


/** Integer division operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Sign        Integer division between the current and
 *                         the given values
 */
Sign Sign::operator/(Sign other)
{
  Sign div;
  signType table[] = {
    BOT,   BOT,   BOT,   BOT,   BOT,
    BOT,   PLUS,  BOT,   MINUS, TOP,
    BOT,   ZERO,  BOT,   ZERO,  ZERO,
    BOT,   MINUS, BOT,   PLUS,  TOP,
    BOT,   TOP,   BOT,   TOP,   TOP
  };
  
  div.value = table[value * 5 + other.value];
  
  return div;
}


/** Remainder of the integer division operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Sign        Remainder of the integer division between
 *                         the current and the given value
 */
Sign Sign::operator%(Sign other)
{
  Sign rem;
  signType table[] = {
    BOT,   BOT,   BOT,   BOT,   BOT,
    BOT,   MINUS, BOT,   MINUS, MINUS,
    BOT,   ZERO,  BOT,   ZERO,  ZERO,
    BOT,   PLUS,  BOT,   PLUS,  PLUS,
    BOT,   TOP,   BOT,   TOP,   TOP
  };
  
  rem.value = table[value * 5 + other.value];
  
  return rem;
}


/** Power raising operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Sign        Current value raised to the power of the
 *                         given one
 */
Sign Sign::operator^(Sign other)
{
  Sign pow;
  signType table[] = {
    BOT,   BOT,   BOT,   BOT,   BOT,
    BOT,   ZERO,  PLUS,  TOP,   TOP,
    BOT,   BOT,   BOT,   ZERO,  ZERO,
    BOT,   ZERO,  PLUS,  PLUS,  TOP,
    BOT,   ZERO,  PLUS,  TOP,   TOP
  };
  
  pow.value = table[value * 5 + other.value];
  
  return pow;
}


/** Cast to const char * operator overloading.
 * This method is used to provide a textual representation of the
 * value.
 * @retval     const char * Textual representation of the value
 */
Sign::operator const char * ()
{
  switch(value){
    case BOT:   return "bot";
    case MINUS: return "-";
    case ZERO:  return "0";
    case PLUS:  return "+";
    case TOP:   return "top";
    default:    return "Unknown abstract value";
  }
}


/** Predicate testing whether two values are equal.
 * @param[in]  a           First operand
 * @param[in]  b           Second operand
 * @retval     bool        True if and only if values are precisely
 *                         equal
 */
bool Sign::equal(Sign a, Sign b)
{
  return a.value == b.value;
}


/** Least upperbound between two values in the abstract domain is
 * computed.
 * @param[in]  a           First abstract value
 * @param[in]  b           Second abstract value
 * @retval     Sign        Least upperbound of a and b
 */
Sign Sign::lub(Sign a, Sign b)
{
  Sign lub;
  signType table[] = {
    BOT,   MINUS, ZERO,  PLUS,  TOP,
    MINUS, MINUS, TOP,   TOP,   TOP,
    ZERO,  TOP,   ZERO,  TOP,   TOP,
    PLUS,  TOP,   TOP,   PLUS,  TOP,
    TOP,   TOP,   TOP,   TOP,   TOP
  };
  
  lub.value = table[a.value * 5 + b.value];
  
  return lub;
}


/** Widening operator.
 * No actual widening is used in the Sign domain.
 * @param[in]  a           Previous value
 * @param[in]  b           Current value
 * @retval     Sign        Widened value
 */
Sign Sign::nabla(Sign a, Sign b)
{
  (void) a;
  return b;
}


/** Abstraction function.
 * For the particular case when given set is a singleton.
 * @param[in]  value       Value of the concrete domain
 * @retval     Sign        Abstract value corresponding to the
 *                         given concrete value
 */
Sign Sign::alpha(int value)
{
  Sign a;
  
  a.value = (value == 0) ? ZERO
          : ((value < 0) ? MINUS : PLUS);
  
  return a;
}


/** Abstraction function.
 * @param[in]  values      Subset of the concrete domain
 * @retval     Sign        Abstract value corresponding to the least
 *                         upperbound of the concrete values
 */
Sign Sign::alpha(vector<int> values)
{
  vector<int>::iterator it;
  Sign a;
  
  a.value = BOT;
  for(it = values.begin(); it != values.end(); ++it){
    a.value = lub(a, alpha(*it)).value;
  }
  
  return a;
}


/** Constant method returning an instance of the "I don't know" value.
 * @retval     Sign        Value representing no information
 */
Sign Sign::top()
{
  Sign top;
  
  top.value = TOP;
  
  return top;
}
