#pragma once
#include <stack>
#include <queue>
#include <memory>

class CNumber;

/// Token in a mathematical expression - either a number or an operator
class CMathObject
{
public:
  /// CMathObject constructor
  CMathObject ();

  
/// CMathObject destructor
  virtual ~CMathObject ();

  /// Obtains elements from queue, performs corresponding action and
  /// pushes them to the stack during calculation of a postfix expression
  /// @param queue reference to the queue
  /// @param stack reference to the stack
  virtual void pushToStack (std::queue<std::shared_ptr<CMathObject>> & queue,
                            std::stack<CNumber> & stack) const = 0;

  /// Prints the mathematical object to ostream
/// @param os output stream
/// @param o object to print
/// @return reference to the output stream
  friend std::ostream & operator << (std::ostream & os, const CMathObject & o);

protected:
  /// Prints the mathematical object to ostream
  /// @param os output stream
  virtual void print (std::ostream & os) const = 0;
};
