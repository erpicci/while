/** Parametric abstract sate.
 * Class template to handle a parametric abstract state, where the
 * parameter tells the type of the variables in the state itself.
 * 
 * @file AbstractState.hpp
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
#ifndef ABSTRACT_STATE_HPP
#define ABSTRACT_STATE_HPP

#include <iostream>
#include <string>
#include <map>

using namespace std;


/** Template representing an abstract state. */
template <typename T>
class AbstractState
{
  public:
  /** 'Less than or equal to' operator overloading.
   * @param[in]  other       Abstract state to be compared
   * @retval     bool        True if and only if every variable in the
   *                         first state is defined with the same
   *                         value also in the second state
   */
  bool operator<=(AbstractState<T> other)
  {
    bool included = true;
    typename map<string, T>::iterator it;
    
    it = state.begin();
    while(included && it != state.end()){
      included = T::equal(it->second, other.state[it->first]);
      ++it;
    }
    
    return included;
  }
  
  
  /** 'Equal to' operator overloading.
   * @param[in]  other       Abstract state to be compared
   * @retval     bool        True if and only if states map the same
   *                         variable name to the same value
   */
  bool operator==(AbstractState<T> other)
  {
    return *this <= other && other <= *this;
  }
  
  
  /** 'Not equal to' operator overloading.
   * @param[in]  other       Abstract state to be compared
   * @retval     bool        True if and only if states are not equal
   */
  bool operator!=(AbstractState<T> other)
  {
    return !(*this == other);
  }
  
  
  /** A lookup operation is performed on the state.
   * @param[in]  var         Name of the variable to be returned
   * @retval     T           Abstract value associated to the variable
   */
  T load(string var)
  {
    return state[var];
  }
  
  
  /** Abstract value of the given variable is updated.
   * If variable was not in state, it is added.
   * @param[in]  var         Name of the variable to be updated
   * @param[in]  value       New abstract value of the variable
   */
  void store(string var, T value)
  {
    state[var] = value;
  }
  
  
  /** A textual representation of the state is provided.
   * State is dumped to standart output.
   */
  void dump()
  {
    typename map<string, T>::iterator it;
    
    cout << "[";
    for(it = state.begin(); it != state.end(); ++it){
      cout << it->first << " -> " << it->second << ", ";
    }
    cout << "]" << endl;
  }
  
  
  /** Least upperbound between abstract states is returned into a new
   * abstract state.
   * @param[in]  s1          First state to be compared
   * @param[in]  s2          Second state to be compared
   * @retval     AbstractState<T> Least upperbound between states
   */
  static AbstractState<T> lub(AbstractState<T> s1, AbstractState<T> s2)
  {
    AbstractState<T> lub;
    typename map<string, T>::iterator it;
    string var;
    
    // Common entries with same values and different entries are copied
    // directly. Conflicting entries are resolved with a least
    // upperbound computation.
    lub.state = s1.state;
    for(it = s2.state.begin(); it != s2.state.end(); ++it){
      var = it->first;
      if(lub.state.find(var) == lub.state.end()){
        lub.state[var] = it->second; 
      }
      else{
        lub.state[var] =  T::lub(s1.state[var], it->second);
      }
    }
    return lub;
  }
  
  
  /** Widening operation is performed on every element of the state.
   * Given two states, widening is applied.
   * @param[in]  s1          Previous state
   * @param[in]  s2          Current state
   * @retval     AbstractState State where every element has been widened
   */
  static AbstractState<T> widening(AbstractState<T> s1, AbstractState<T> s2)
  {
    AbstractState<T> widened;
    typename map<string, T>::iterator it;
    
    for(it = s2.state.begin(); it != s2.state.end(); ++it){
      widened.state[it->first] = T::nabla(s1.state[it->first], it->second);
    }
    
    return widened;
  }
  
  
  private:
  map<string, T> state; ///< Set of bindings variable - abstract value
};
#endif
