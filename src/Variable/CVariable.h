#pragma once
#include <string>
#include <ostream>
#include <queue>
#include "../MathObject/CMathObject.h"

/// Variable storing a mathematical expression or a number
class CVariable
{
public:

  /// CVariable constructor
  /// @param name name of the variable
  /// @param expr expression of the variable
  CVariable (const std::string & name, const std::string & expr, const std::vector<CVariable> & vars = std::vector<CVariable>());

  /// Compares if the variables have the same name
  /// @param rhs variable to compare
  /// @return 1 if the names are the same, 0 otherwise
  bool operator == (const CVariable & rhs) const;

  /// Gets the name of a variable
  /// @return variable name
  std::string name () const;

  /// Gets the expression of the variable
  /// @return string with the expression
  std::string expression () const;

  /// Gets the queue with parsed expression
  /// @return queue with parsed expression
  std::queue<std::shared_ptr<CMathObject>> queue () const;

  /// Prints the variable and its expression to the ostream
  /// @param os output stream
  /// @param var variable to print
  friend std::ostream & operator << (std::ostream & os, const CVariable & var);

private:
  /// name of the variable
  std::string m_Name;
  /// value (mathematical expression) of the variable
  std::string m_Expression;
  /// queue with expression in postfix notation
  std::queue<std::shared_ptr<CMathObject>> m_Queue;
};
