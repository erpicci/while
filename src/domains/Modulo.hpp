/** Modulo<N> abstract interpretation.
 * Template handling the abstract iterpretation in the Modulo<N> abstract
 * domain.
 * 
 * @file Modulo.hpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @ingroup domains
 */
#ifndef MODULO_H
#define MODULO_H

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

/** Class representing the interval domain abstraction.
 * In the interval domain, every value is identified by an interval that
 * contains the concrete value.
 */
template <int N = 2>
class Modulo
{
  public:
  /** 'Less than' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not
   *                         smaller than the second one
   */
  bool operator< (Modulo<N> other)
  {
    if     (this->carry == BOT || other.carry == BOT){ return false; }
    else if(this->carry == TOP || other.carry == TOP){ return true; }
    else    return !(this->value > 0 && other.value < 0);
  }
  
  
  /** 'Less than or equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not
   *                         smaller than or equal to the second one
   */
  bool operator<=(Modulo<N> other)
  {
    if     (this->carry == BOT || other.carry == BOT){ return false; }
    else if(this->carry == TOP || other.carry == TOP){ return true; }
    else    return !(this->value > 0 && other.value < 0);
  }
  
  
  /** 'Equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not equal
   *                         to the second one
   */
  bool operator==(Modulo<N> other)
  {
    if     (this->carry == BOT || other.carry == BOT){ return false; }
    else if(this->carry == TOP || other.carry == TOP){ return true; }
    else    return this->value == other.value;
  }
  
  
  /** 'Greater than or equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure greater
   *                         than or equal to the second one
   */
  bool operator>=(Modulo<N> other)
  {
    if     (this->carry == BOT || other.carry == BOT){ return false; }
    else if(this->carry == TOP || other.carry == TOP){ return true; }
    else    return !(this->value < 0 && other.value > 0);
  }
  
  
  /** 'Greater' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure greater
   *                         than the second one
   */
  bool operator> (Modulo<N> other)
  {
    if     (this->carry == BOT || other.carry == BOT){ return false; }
    else if(this->carry == TOP || other.carry == TOP){ return true; }
    else    return !(this->value < 0 && other.value > 0);
  }
  
  
  /** 'Not equal to' operator overloading.
   * @param[in]  other       Right-operand
   * @retval     bool        False if left-operand is for sure not equal
   *                         to the second one
   */
  bool operator!=(Modulo<N> other)
  {
    (void) other;
    return true;
  }


  /** Identity operator overloading.
   * @retval     Modulo<N>   Identity of the value
   */
  Modulo<N> operator+()
  {
    return *this;
  }
  
  
  /** Opposite operator overloading.
   * @retval     Modulo<N>   Opposite of the value
   */
  Modulo<N> operator-()
  {
    Modulo<N> Opp;
    
    Opp.carry = this->carry;
    Opp.value = -this->value;
    
    return Opp;
  }
  
  
  /** Sum operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Modulo<N>   Sum of the current and the given values
   */
  Modulo<N> operator+(Modulo<N> other)
  {
    Modulo<N> sum;
    
    if      (this->carry == TOP || other.carry == TOP){ sum.carry = TOP; }
    else if (this->carry == BOT || other.carry == BOT){ sum.carry = BOT; }
    else    sum = alpha(this->value + other.value);
    
    return sum;
  }
  
  
  /** Subtraction operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Modulo<N>   Difference between the current and the
   *                         given values
   */
  Modulo<N> operator-(Modulo<N> other)
  {
    Modulo<N> sub;
    
    if      (this->carry == TOP || other.carry == TOP){ sub.carry = TOP; }
    else if (this->carry == BOT || other.carry == BOT){ sub.carry = BOT; }
    else    sub = alpha(this->value - other.value);
    
    return sub;
  }
  
  
  /** Multiplication operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Modulo<N>   Product of the current and the given values
   */
  Modulo<N> operator*(Modulo<N> other)
  {
    Modulo<N> mul;
    
    if ((this->carry != TOP && this->value == 0)
    ||  (other.value != TOP && other.value == 0)){
      mul.carry = NUM; mul.value = 0;
    }
    else if (this->carry == TOP || other.carry == TOP){ mul.carry = TOP; }
    else if (this->carry == BOT || other.carry == BOT){ mul.carry = BOT; }
    else    mul = alpha(this->value * other.value);
    
    return mul;
  }
  
  
  /** Integer division operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Modulo<N>   Integer division between the current and
   *                         the given values
   */
  Modulo<N> operator/(Modulo<N> other)
  {
    Modulo<N> div;
    
    if(this->carry == BOT || other.carry == BOT ||
      (other.carry == NUM && other.value == 0)){
      div.carry = BOT;
    }
    else{
      div = top();
    }
    
    return div;
  }
  
  
  /** Remainder of the integer division operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Modulo<N>   Remainder of the integer division between
   *                         the current and the given value
   */
  Modulo<N> operator%(Modulo<N> other)
  {
    Modulo<N> rem;
    
    if(this->carry == BOT || other.carry == BOT ||
      (other.carry == NUM && other.value == 0)){
      rem.carry = BOT;
    }
    else{
      rem = top();
    }
    
    return rem;
  }
  
  
  /** Power raising operator overloading.
   * @param[in]  other       Right-operand
   * @retval     Modulo<N>   Current value raised to the power of the
   *                         given one
   */
  Modulo<N> operator^(Modulo<N> other)
  {
    Modulo<N> pow;
    
    if(this->carry == BOT || other.carry == BOT){
      pow.carry = BOT;
    }
    else if((other.carry != TOP && other.value < 0)
         || (this->carry != TOP && this->value == 0)){
      pow.carry = NUM;
      pow.value = 0;
    }
    else{
      pow = top();
    }
    
    return pow;
  }
  
  
  /** Cast to const char * operator overloading.
   * This method is used to provide a textual representation of the
   * value.
   * @retval     const char * Textual representation of the value
   */
  operator const char * ()
  {
    char buff[32];
    
    switch(carry){
      case BOT: return "bot";
      case NUM:
        sprintf(buff, "%d", value);
        return string(buff).c_str();
      case TOP: return "top";
      default:  return "top";
    }
  }


  /** Predicate testing whether two values are equal.
   * @param[in]  a           First operand
   * @param[in]  b           Second operand
   * @retval     bool        True if and only if values are precisely
   *                         equal
   */
  static bool equal(Modulo<N> a, Modulo<N> b)
  {
    return (a.carry == NUM && b.carry == NUM)
         ? a.value == b.value
         : a.carry == b.carry;
  }


  /** Least upperbound between two values in the abstract domain is
   * computed.
   * @param[in]  a           First abstract value
   * @param[in]  b           Second abstract value
   * @retval     Modulo<N>    Least upperbound of a and b
   */
  static Modulo<N> lub(Modulo<N> a, Modulo<N> b)
  {
    Modulo<N> lub;
    
    if(a.carry == TOP || b.carry == TOP){
      lub.carry = TOP;
    }
    else if(a.carry == BOT && b.carry == BOT){
      lub.carry = BOT;
    }
    else if(a.carry == BOT){ lub = b; }
    else if(b.carry == BOT){ lub = a; }
    else if(a.value == b.value){ lub = a; }
    else{ lub = top(); }
    
    return lub;
  }
  
  
  /** Widening operator.
   * No actual widening is used in the Modulo<N> domain.
   * @param[in]  a           Previous value
   * @param[in]  b           Current value
   * @retval     Modulo<N>    Widened value
   */
  static Modulo<N> nabla(Modulo<N> a, Modulo<N> b)
  {
    (void) a;
    return b;
  }
  
  
  /** Abstraction function.
   * For the particular case when given set is a singleton.
   * @param[in]  value       Value of the concrete domain
   * @retval     Modulo<N>    Abstract value corresponding to the
   *                         given concrete value
   */
  static Modulo<N> alpha(int value)
  {
    Modulo<N> a;
    
    if(N == 0){
      a.carry = BOT;
    }
    else{
      a.carry = NUM;
      a.value = value % N;
    }
    
    return a;
  }


  /** Abstraction function.
   * @param[in]  values      Subset of the concrete domain
   * @retval     Modulo<N>    Abstract value corresponding to the least
   *                         upperbound of the concrete values
   */
  static Modulo<N> alpha(vector<int> values)
  {
    vector<int>::iterator it;
    Modulo<N> a;
    
    a = alpha(values[0]);
    for(it = values.begin(); it != values.end(); ++it){
      a = lub(a, alpha(*it));
    }
    
    return a;
  }
  
  
  /** Constant method returning an instance of the "I don't know" value.
   * @retval     Modulo<N>        Value representing no information
   */
  static Modulo<N> top()
  {
    Modulo<N> top;
    top.carry = TOP;
    return top;
  }
  
  
  private:
  /** Type representing classes of possible abstract values. */
  typedef enum{
    BOT,           ///< Impossible value
    NUM,           ///< Remainder of the integer division is carried
    TOP            ///< No information is carried
  } carryType;
  carryType carry; ///< Type of carried information
  int value;       ///< Remainder of the integer division
};
#endif
