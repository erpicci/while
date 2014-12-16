/** Symmetric interval abstract interpretation.
 * Class handling the abstract interpretation in the Symmetric SInterval
 * abstract domain.
 * 
 * @file SInterval.cpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @ingroup domains
 */
#include <malloc.h>
#include <iostream>
#include <limits>

#include "SInterval.hpp"


/** 'Less than' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not
 *                         smaller than the second one
 */
bool SInterval::operator< (SInterval other)
{
  return (center - offset < other.center + other.offset) && !bottom;
}


/** 'Less than or equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not
 *                         smaller than or equal to the second one
 */
bool SInterval::operator<=(SInterval other)
{
  return (center - offset >= other.center + other.offset) && !bottom;
}


/** 'Equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not equal
 *                         to the second one
 */
bool SInterval::operator==(SInterval other)
{
  return (center - offset <= other.center + other.offset
      &&  center + offset >= other.center - other.offset)
      && !bottom;
}


/** 'Greater than or equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure greater
 *                         than or equal to the second one
 */
bool SInterval::operator>=(SInterval other)
{
  return (center + offset >= other.center - other.offset) && !bottom;
}


/** 'Greater' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure greater
 *                         than the second one
 */
bool SInterval::operator> (SInterval other)
{
  return (center + offset > other.center - other.offset) && !bottom;
}


/** 'Not equal to' operator overloading.
 * @param[in]  other       Right-operand
 * @retval     bool        False if left-operand is for sure not equal
 *                         to the second one
 */
bool SInterval::operator!=(SInterval other)
{
  return (center != other.center || offset != other.offset || offset == 0)
      && !bottom;
}


/** Identity operator overloading.
 * @retval     SInterval   Identity of the value
 */
SInterval SInterval::operator+()
{
  return *this;
}


/** Opposite operator overloading.
 * @retval     SInterval   Opposite of the value
 */
SInterval SInterval::operator-()
{
  SInterval opp;
  
  opp.center = -center;
  opp.offset = offset;
  opp.bottom = bottom;
  
  return opp;
}


/** Sum operator overloading.
 * @param[in]  other       Right-operand
 * @retval     SInterval   Sum of the current and the given values
 */
SInterval SInterval::operator+(SInterval other)
{
  SInterval sum;
  
  sum.center = center + other.center;
  sum.offset = offset + other.offset;
  sum.bottom = bottom || other.bottom;
  
  return sum;
}


/** Subtraction operator overloading.
 * @param[in]  other       Right-operand
 * @retval     SInterval   Difference between the current and the
 *                         given values
 */
SInterval SInterval::operator-(SInterval other)
{
  SInterval sub;
  
  sub.center = center - other.center;
  sub.offset = offset - other.offset;
  if(sub.offset < 0){
    sub.offset = -sub.offset;
  }
  sub.bottom = bottom || other.bottom;
  
  return sub;
}


/** Multiplication operator overloading.
 * @param[in]  other       Right-operand
 * @retval     SInterval   Product of the current and the given values
 */
SInterval SInterval::operator*(SInterval other)
{
  SInterval mul;
  
  mul.center = center * other.center;
  mul.offset = offset * other.offset;
  mul.bottom = bottom || other.bottom;
  
  return mul;
}


/** Integer division operator overloading.
 * @param[in]  other       Right-operand
 * @retval     SInterval   Integer division between the current and
 *                         the given values
 */
SInterval SInterval::operator/(SInterval other)
{
  SInterval div;
  
  if(other.center == 0 && other.offset == 0){
    div.bottom = true;
  }
  else if(other.center == 0 || other.offset == 0){
    div = top();
  }
  else{
    div.center = center / other.center;
    div.offset = offset / other.offset;
    div.bottom = bottom || other.bottom;
  }
  
  return div;
}


/** Remainder of the integer division operator overloading.
 * @param[in]  other       Right-operand
 * @retval     SInterval   Remainder of the integer division between
 *                         the current and the given value
 * @todo Precision can be improved.
 */
SInterval SInterval::operator%(SInterval other)
{
  SInterval rem;
  
  if(other.center == 0 && other.offset == 0){
    rem.bottom = true;
  }
  else{
    rem = top();
  }
  
  return rem;
}


/** Power raising operator overloading.
 * @param[in]  other       Right-operand
 * @retval     SInterval    Current value raised to the power of the
 *                         given one
 * @todo Precision can be improved.
 */
SInterval SInterval::operator^(SInterval other)
{
  SInterval pow;
  
  pow = top();
  pow.bottom = bottom || other.bottom;
  
  return pow;
}


/** Cast to const char * operator overloading.
 * This method is used to provide a textual representation of the
 * value.
 * @retval     const char * Textual representation of the value
 */
SInterval::operator const char * ()
{
  char c[16], off[16];
  
  sprintf(c,  "%ld", center);
  sprintf(off, "%ld", offset);
  
  if(bottom) return "bot";
  
  string a = c + string(" ±")
  + (offset == numeric_limits<short>::max() ? "inf" : off)
  ;
  
  return a.c_str();
}

  
/** Predicate testing whether two values are equal.
 * @param[in]  a           First operand
 * @param[in]  b           Second operand
 * @retval     bool        True if and only if values are precisely
 *                         equal
 */
bool SInterval::equal(SInterval a, SInterval b)
{
  return a.center == b.center && a.offset == b.offset
      && a.bottom == b.bottom;
}


/** Least upperBound between two values in the abstract domain is
 * computed.
 * @param[in]  a           First abstract value
 * @param[in]  b           Second abstract value
 * @retval     SInterval   Least upperBound of a and b
 */
SInterval SInterval::lub(SInterval a, SInterval b)
{
  SInterval lub;
  
  if(a.bottom) lub = b;
  else if(b.bottom) lub = a;
  else{
    lub.center = (a.center + b.center) / 2;
    lub.offset = (a.center > b.center
                  ? a.center - lub.center : b.center - lub.center)
               + (a.offset > b.offset ? a.offset : b.offset);
    lub.bottom = false;
  }
  
  return lub;
}


/** Widening operator.
 * @param[in]  a           Previous value
 * @param[in]  b           Current value
 * @retval     SInterval   Widened value
 */
SInterval SInterval::nabla(SInterval a, SInterval b)
{
  SInterval widened;
  
  widened.center = b.center;
  widened.offset = (b.offset > a.offset && b.center >= a.center)
                 ? numeric_limits<short>::max()
                 : b.offset;
  widened.bottom = b.bottom;
  
  return widened;
}


/** Abstraction function.
 * For the particular case when given set is a singleton.
 * @param[in]  value       Value of the concrete domain
 * @retval     SInterval    Abstract value corresponding to the
 *                         given concrete value
 */
SInterval SInterval::alpha(int value)
{
  SInterval a;
  
  a.center = (long) value;
  a.offset = 0L;
  a.bottom = false;
  
  return a;
}


/** Abstraction function.
 * @param[in]  values      Subset of the concrete domain
 * @retval     SInterval    Abstract value corresponding to the least
 *                         upperBound of the concrete values
 */
SInterval SInterval::alpha(vector<int> values)
{
  vector<int>::iterator it;
  SInterval a;
  
  a = alpha(values[0]);
  for(it = values.begin(); it != values.end(); ++it){
    a = lub(a, alpha(*it));
  }
  
  return a;
}


/** Constant method returning an instance of the "I don't know" value.
 * @retval     SInterval        Value representing no information
 */
SInterval SInterval::top()
{
  SInterval top;
  
  top.center = 0L;
  top.offset = numeric_limits<short>::max();
  top.bottom = false;
  
  return top;
}
