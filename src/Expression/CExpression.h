#pragma once
#include <string>
#include <ostream>
#include <queue>
#include <map>
#include <memory>
#include <vector>
#include "../MathObject/CMathObject.h"
#include "../Variable/CVariable.h"
#include "../Operator/COperator.h"

class COperator;

/// Mathematical expression converted to postfix notation
class CExpression
{
public:
  /// Expression constructor
  /// @param expr string with expression in infix notation
  /// @param vars vector of currently saved variables
  CExpression (const std::string & expr, const std::vector<CVariable> & vars = std::vector<CVariable>());

  /// Getter for the output queue of CMathObjects
  /// @return output queue with shared_ptrs of CMathObject
  std::queue<std::shared_ptr<CMathObject>> getQueue () const;

  /// Displays expression to the output streams
  /// @param os output stream
  /// @param expr expression to display
  /// @return reference to the output stream
  friend std::ostream & operator << (std::ostream & os, const CExpression & expr);

private:
  /// parsed queue with operators and numbers
  std::queue<std::shared_ptr<CMathObject>> m_outputQueue;
  /// string with expression in infix notation
  std::string m_Infix;

  /// Parses a mathematical expression in infix notation using the
  /// shunting-yard algorithm as described here https://en.wikipedia.org/wiki/Shunting-yard_algorithm
  /// and converts it to postfix notation.
  /// @param expr expression to parse
  void parse          (const std::string & expr, const std::vector<CVariable> & vars = std::vector<CVariable>());

  /// Parses an operator in the shunting-yard algorithm
  /// @param opStack stack of operators
  /// @param op operator
  void parseOperator  (std::stack<std::shared_ptr<COperator>> & opStack, std::string & op);

  /// Parse right bracket in the shunting-yard algorithm
  /// @param opStack stack of operators
  void parseRBracket  (std::stack<std::shared_ptr<COperator>> & opStack);

  /// Parses a variable in the shunting-yard algorithm
  /// @param opStack stack of operators
  /// @param variable name of the variable
  /// @param vars vector with currently saved variables
  void parseVar       (std::stack<std::shared_ptr<COperator>> & opStack, std::string & var,
                       const std::vector<CVariable> & vars);

  /// Returns the precedence of a mathematical operator
  /// @param op string with the mathematical operator
  /// @return 1 for operators + and -, 2 for operators * and /
  int opPrecedence    (const std::string & op)     const;

  /// Checks if a string is a math operator.
  /// @param str string to check
  /// @return True if string is an operator.
  bool isOperator     (const std::string & str)    const;

  /// Checks if a string is a number.
  /// @param str string to check
  /// @return True if string is a number.
  bool isNumber       (const std::string & str)    const;
};
