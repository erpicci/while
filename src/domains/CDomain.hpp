#ifndef _C_DOMAIN_HPP_
#define _C_DOMAIN_HPP_

#include "../AbstractDomain.h"

#include <string>
#include <iostream>


class CDomain : public AbstractDomain
{
  public:
  typedef string abstract_type;
  typedef enum{B_BOT, FALSE, TRUE, B_TOP} abstract_bool;
  
//  static void Assignment(){}
  static void Skip(void)
  {
    // Do nothing.
  }
  
  static void Cat(void)
  {
    // Do nothing.
    cout << ";\n";
  }
  
//  static void If(abstract_bool b, ???){}
  
//  static void While(abstract_bool b, ???){}
  
  static void Print(abstract_type a)
  {
    cout << "printf(\"%d\n\", " << a << ")\n";
  }
  
  
  
  static abstract_type AbstractValue(int a)
  {
    return "??";
  }
  
  
  
  static abstract_type Sum(abstract_type a, abstract_type b)
  {
    cout << "(" <<  a << "+" << b << ")";
    return "??";
  }
 
  
  
  static bool And(bool a, bool b)
  {
    return "??";
  }
   
  static bool Lt(abstract_type a, abstract_type b)
  {
    return "??";
  }
};




#endif
