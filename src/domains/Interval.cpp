/** Interval abstract interpretation.
 * Class handling the abstract interpretation in the Interval abstract
 * domain.
 * 
 * @file Interval.cpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @ingroup domains
 */
#include <malloc.h>
#include <iostream>
#include <limits>

#include "Interval.hpp"


/** 'Less than' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not
 *                         smaller than the second one
 */
bool Interval::operator< (Interval other)
{
  return (lBound >= other.rBound) ? false : true;
}


/** 'Less than or equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not
 *                         smaller than or equal to the second one
 */
bool Interval::operator<=(Interval other)
{
  return (lBound > other.rBound) ? false : true;
}


/** 'Equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not equal
 *                         to the second one
 */
bool Interval::operator==(Interval other)
{
  return (lBound > other.rBound || rBound < other.lBound)
       ? false : true;
}


/** 'Greater than or equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure greater
 *                         than or equal to the second one
 */
bool Interval::operator>=(Interval other)
{
  return (rBound < other.lBound) ? false : true;
}


/** 'Greater' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure greater
 *                         than the second one
 */
bool Interval::operator> (Interval other)
{
  return (rBound <= other.lBound) ? false : true;
}


/** 'Not equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not equal
 *                         to the second one
 */
bool Interval::operator!=(Interval other)
{
  return (lBound == rBound && lBound == other.lBound &&
          other.lBound == other.rBound) ? false : true;
}


/** Identity operator overloading.
 * @retval     Interval    Identity of the value
 */
Interval Interval::operator+()
{
  return *this;
}


/** Opposite operator overloading.
 * @retval     Interval    Opposite of the value
 */
Interval Interval::operator-()
{
  Interval opp;
  
  opp.lBound = -rBound;
  opp.rBound = -lBound;
  
  return opp;
}


/** Sum operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Interval    Sum of the current and the given values
 */
Interval Interval::operator+(Interval other)
{
  Interval sum;
  
  sum.lBound = lBound + other.lBound;
  sum.rBound = rBound + other.rBound;
  
  return sum;
}


/** Subtraction operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Interval    Difference between the current and the
 *                         given values
 */
Interval Interval::operator-(Interval other)
{
  Interval sub;
  
  sub.lBound = lBound - other.rBound;
  sub.rBound = rBound - other.lBound;
  
  return sub;
}


/** Multiplication operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Interval    Product of the current and the given values
 */
Interval Interval::operator*(Interval other)
{
  long tmp;
  Interval mul;
  
  mul.lBound = lBound * other.lBound;
  mul.rBound = rBound * other.rBound;
  if(mul.lBound > mul.rBound){
    tmp = mul.lBound;
    mul.lBound = mul.rBound;
    mul.rBound = tmp;
  }
  
  return mul;
}


/** Integer division operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Interval    Integer division between the current and
 *                         the given values
 */
Interval Interval::operator/(Interval other)
{
  long tmp;
  Interval div;
  
  div.lBound = lBound / other.rBound;
  div.rBound = rBound / other.lBound;
  if(div.lBound > div.rBound){
    tmp = div.lBound;
    div.lBound = div.rBound;
    div.rBound = tmp;
  }
  
  return div;
}


/** Remainder of the integer division operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Interval    Remainder of the integer division between
 *                         the current and the given value
 */
Interval Interval::operator%(Interval other)
{
  Interval rem;
  
  if(other.lBound > 0){
    rem.lBound = 0L;
    rem.rBound = other.rBound - 1L;
  }
  else if(other.rBound < 0){
    rem.lBound = other.lBound + 1L;
    rem.rBound = 0L;
  }
  else{
    rem.lBound = other.lBound + 1L;
    rem.rBound = other.rBound - 1L;
  }
  
  return rem;
}


/** Power raising operator overloading.
 * @param[in]  other       Right-operand
 * @retval     Interval    Current value raised to the power of the
 *                         given one
 */
Interval Interval::operator^(Interval other)
{
  long i;
  Interval pow;
  
  pow.lBound = 1L;
  for(i = 0; i < other.lBound; ++i){
    pow.lBound *= (long) lBound;
  }
  
  pow.rBound = 1L;
  for(i = 0; i < other.rBound; ++i){
    pow.rBound *= (long) rBound;
  }
  
  if(lBound > rBound){
    i = lBound;
    lBound = rBound;
    rBound = i;
  }
  
  return pow;
}


/** Cast to const char * operator overloading.
 * This method is used to provide a textual representation of the
 * value.
 * @retval     const char * Textual representation of the value
 */
Interval::operator const char * ()
{
  char left[16], right[16];
  
  sprintf(left,  "%ld", lBound);
  sprintf(right, "%ld", rBound);
  
  string a =
    (lBound == numeric_limits<int>::min() ? "(-inf" : (string("[") + left))
  + string("; ")
  + (rBound == numeric_limits<int>::max() ? "+inf)" : (right + string("]")))
  ;
  
  return a.c_str();
}

  
/** Predicate testing whether two values are equal.
 * @param[in]  a           First operand
 * @param[in]  b           Second operand
 * @retval     bool        True if and only if values are precisely
 *                         equal
 */
bool Interval::equal(Interval a, Interval b)
{
  return (a.lBound == b.lBound && a.rBound == b.rBound);
}


/** Least upperBound between two values in the abstract domain is
 * computed.
 * @param[in]  a           First abstract value
 * @param[in]  b           Second abstract value
 * @retval     Interval    Least upperBound of a and b
 */
Interval Interval::lub(Interval a, Interval b)
{
  Interval lub;
  
  lub.lBound = (a.lBound < b.lBound) ? a.lBound : b.lBound;
  lub.rBound = (a.rBound > b.rBound) ? a.rBound : b.rBound;
  
  return lub;
}


/** Widening operator.
 * @param[in]  a           Previous value
 * @param[in]  b           Current value
 * @retval     Interval    Widened value
 */
Interval Interval::nabla(Interval a, Interval b)
{
  Interval widened;
  
  widened.lBound = (b.lBound < a.lBound)
                 ? numeric_limits<int>::min()
                 : b.lBound;
  widened.rBound = (b.rBound > a.rBound)
                 ? numeric_limits<int>::max()
                 : b.rBound;
  
  return widened;
}


/** Abstraction function.
 * For the particular case when given set is a singleton.
 * @param[in]  value       Value of the concrete domain
 * @retval     Interval    Abstract value corresponding to the
 *                         given concrete value
 */
Interval Interval::alpha(int value)
{
  Interval a;
  
  a.lBound = (long) value;
  a.rBound = (long) value;
  
  return a;
}


/** Abstraction function.
 * @param[in]  values      Subset of the concrete domain
 * @retval     Interval    Abstract value corresponding to the least
 *                         upperBound of the concrete values
 */
Interval Interval::alpha(vector<int> values)
{
  vector<int>::iterator it;
  Interval a;
  
  a = alpha(values[0]);
  for(it = values.begin(); it != values.end(); ++it){
    a = lub(a, alpha(*it));
  }
  
  return a;
}


/** Constant method returning an instance of the "I don't know" value.
 * @retval     Interval        Value representing no information
 */
Interval Interval::top()
{
  Interval top;
  
  top.lBound = (long) numeric_limits<int>::min();
  top.rBound = (long) numeric_limits<int>::max();
  
  return top;
}
