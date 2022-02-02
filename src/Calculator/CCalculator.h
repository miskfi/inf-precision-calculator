#pragma once
#include <vector>
#include <string>
#include "../Variable/CVariable.h"
#include "../MathObject/CNumber.h"

class CCalculator
{
public:
  /// CCalculator default constructor
  CCalculator ();

  /// Calculates a mathematical expression
  /// @param expression string with the mathematical expression
  /// @return result of the expression
  CNumber calculate (const std::string & expression);

  /// Clears the currently saved history and variables
  void clear ();

  /// Saves a calculated expression to calculator history
  /// @param expression expression to save
  void saveToHistory (const std::string & expression);

  /// Saves a new variable or updates and existing variable
  /// @param name variable name
  /// @param expr expression stored in the variable
  void saveVariable (const std::string & name, const std::string & expr);

  /// Checks and finds a variable from the saved variables
  /// @param name name of the variable
  /// @return reference to the variable
  const CVariable & findVariable (const std::string & name) const;

  /// Prints history of calculated expressions to output stream
  /// @param os output stream
  /// @return reference to the output stream
  std::ostream & printHistory (std::ostream & os) const;

  /// Prints currently saved variables to output stream
  /// @param os output stream
  /// @return reference to the output stream
  std::ostream & printVariables (std::ostream & os) const;

private:
  /// vector of calculated expressions
  std::vector<std::string> m_ExprHistory;
  /// currently saved variables
  std::vector<CVariable> m_Variables;
};