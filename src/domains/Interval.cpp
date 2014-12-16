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
  return (lBound < other.rBound) && !bottom;
}


/** 'Less than or equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not
 *                         smaller than or equal to the second one
 */
bool Interval::operator<=(Interval other)
{
  return (lBound <= other.rBound) && !bottom;
}


/** 'Equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not equal
 *                         to the second one
 */
bool Interval::operator==(Interval other)
{
  return (lBound <= other.rBound && rBound >= other.lBound) && !bottom;
}


/** 'Greater than or equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure greater
 *                         than or equal to the second one
 */
bool Interval::operator>=(Interval other)
{
  return (rBound >= other.lBound) && !bottom;
}


/** 'Greater' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure greater
 *                         than the second one
 */
bool Interval::operator> (Interval other)
{
  return (rBound > other.lBound) && !bottom;
}


/** 'Not equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not equal
 *                         to the second one
 */
bool Interval::operator!=(Interval other)
{
  return (lBound != rBound || lBound != other.lBound ||
          other.lBound != other.rBound) && !bottom;
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
  opp.bottom = bottom;
  
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
  sum.bottom = bottom || other.bottom ;
  
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
  sub.bottom = bottom || other.bottom;
  
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
  mul.bottom = bottom || other.bottom;
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
  
  div.bottom = bottom || other.bottom;
  if(other.rBound == 0 && other.lBound == 0){
    div.bottom = true;
    return div;
  }
  else if(other.rBound == 0 || other.lBound == 0){
    return top();
  }
  
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
  
  rem.bottom = bottom || other.bottom;
  if(other.rBound == 0 && other.lBound == 0){
    rem.bottom = true;
    return rem;
  }
  else if(other.rBound == 0 || other.lBound == 0){
    return top();
  }
  
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
  
  pow.bottom = bottom || other.bottom;
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
  
  if(bottom){ return "bot"; }
  
  string a =
    (lBound<=numeric_limits<short>::min() ? "(-inf" : (string("[") + left))
  + string("; ")
  + (rBound>=numeric_limits<short>::max() ? "+inf)" : (right + string("]")))
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
  return (a.lBound == b.lBound && a.rBound == b.rBound)
      &&  a.bottom == b.bottom;
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
  
  if(a.bottom) lub = b;
  if(b.bottom) lub = a;
  if(!a.bottom && !b.bottom){
    lub.lBound = (a.lBound < b.lBound) ? a.lBound : b.lBound;
    lub.rBound = (a.rBound > b.rBound) ? a.rBound : b.rBound;
    lub.bottom = false;
  }
  
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
                 ? numeric_limits<short>::min()
                 : b.lBound;
  widened.rBound = (b.rBound > a.rBound)
                 ? numeric_limits<short>::max()
                 : b.rBound;
  widened.bottom = b.bottom;
  
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
  a.bottom = false;
  
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
  
  top.lBound = (long) numeric_limits<short>::min();
  top.rBound = (long) numeric_limits<short>::max();
  top.bottom = false;
  
  return top;
}
