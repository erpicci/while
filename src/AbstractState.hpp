/** Template for an abstract state.
 * 
 * Class template to handle a parametric abstract state, where the
 * parameter tells the type of the variables in the state itself.
 * 
 * @file AbstractState.h
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 * @version 0.9
 * @date 11/03/2014
 */


#ifndef _ABSTRACT_STATE_H_
#define _ABSTRACT_STATE_H_

/* Header file inclusion. */
#include <string.h>



/** Template used to represent an abstract state. */
template <class T>
class AbstractState
{
  public:
  /** Constructor.
   * The state is allocated by reserving a certain memory area whose
   * size is proportional to the number of variable used by the program,
   * which is the parameter of the constructor.
   * @param[in]  size        Number of variables that will be used by
   *                         the program
   * @return     A new state
   */
  AbstractState(unsigned int size)
  {
    unsigned int i;
    
    this->state  = (T *) malloc(size * sizeof(T));
    this->lookup_table = (char **) malloc(size * sizeof(char *));
    for(i = 0; i < size; i++){
      this->lookup_table[i] = (char *) malloc(32 * sizeof(char));
    }
    this->size   = size;
    this->cursor = 0;
  }
  
  
  
  /** Destructor. */
  ~AbstractState(void)
  {
    unsigned int i;
    
    for(i = 0; i < this->size; i++){
      free(this->lookup_table[i]);
    }
    free(this->state);
    free(this->lookup_table);
  }
  
  
  
  /** A new variable is inserted into the state.
   * If the variable already exists, its value is overwritten. If the
   * state is full, nothing happens and an error message is shown.
   * @param[in]  var         Name of the variable to be inserted
   * @param[in]  value       Value of the variable to be inserted
   */
  void insert(const char var[], T value){
    unsigned int address;
    
    address = this->lookup(var);
    if(address < this->cursor && address < this->size){
      this->state[address] = value;
    }
    else if(address == this->size && this->cursor < this->size){
      strcpy(this->lookup_table[this->cursor], var);
      this->state[this->cursor] = value;
      this->cursor++;
    }
    else{
      fprintf(stderr, "[AbstractState::insert] Abstract state is full.\n");
    }
  }
  
  
  
  /** A new variable is inserted into the state.
   * If the variable already exists, its value is overwritten. If the
   * state is full, nothing happens and an error message is shown.
   * @param[in]  var         Name of the variable to be inserted
   */
  void insert(const char var[])
  {
    this->insert(var, (T) 0);
  }
  
  
  
  /** The value associated to a variable is returned.
   * If the variable does not exist in the state, nothing happens and
   * an error message is shown.
   * @param[in]  var         Name of the variable to be accessed
   * @return     Value associated to the variable
   */
  T read(const char var[])
  {
    unsigned int address;
    
    address = this->lookup(var);
    // If the variable was not found, an error message is print.
    if(address >= this->size){
      fprintf(stderr, "[AbstractState::read] Variable %s not found.\n",
              var);
      return (T) 0;
    }
    
    return this->state[address];
  }
  
  
  
  /** The value associated to a variable is overwritten.
   * If the variable does not exist in the stat, nothing happens and
   * an error message is shown.
   * @param[in]  var         Variable to be overwritten
   * @param[in]  value       New value of the variable
   */
  void write(const char var[], T value)
  {
   unsigned int address;
   
   address = this->lookup(var);
    // If the variable was not found, an error message is print.
    if(address >= this->size){
      fprintf(stderr, "[AbstractState::write] Variable %s not found.\n",
              var);
      return;
    }
    
    this->state[address] = value;
  }
  
  
  
  /** Anything in the state is print.
   * @note This is a debug function!
   */
  void print_all(void)
  {
    unsigned int i, bound;
    
    bound = (this->cursor < this->size) ? this->cursor : this->size;
    for(i = 0; i < bound; i++){
      printf("s[%s] -> %d\n", this->lookup_table[i], this->state[i]);
    }
  }
  
  
  
  private:
  char **lookup_table;  /**< Array containing the name of the variables.
                             Their position within the array correspond
                             to their position in the state. */
  T *state;             /**< Array containing the vaue of any used
                             variable (the actual state). */
  unsigned int cursor;  /**< Cursor used when inserting variables. */
  unsigned int size;    /**< Size of the state. */
  
  
  
  /** The address of a variable is returned.
   * The position of a variable within the abstract state is returned,
   * given its name. If the variable does not belong to the state, an
   * out of bound index is returned.
   * @param[in]  var    Name of the variable
   * @return     Address of the variable in the abstract state
   */
  unsigned int lookup(const char var[])
  {
    unsigned int i;
    bool found;
    
    i = 0; found = false;
    while(i < this->size && !found){
      if(strcmp(var, this->lookup_table[i]) == 0) found = true;
      else i++;
    }
    
    return i;
  }
};



#endif

