#pragma once
#include <iostream>
#include "../MathObject/CMathObject.h"
#include "../MathObject/CNumber.h"

/// Mathematical operator
class COperator : public CMathObject
{
public:
  /// COperator constructor
  COperator ();
  /// COperator destructor
  virtual ~COperator ();

  /// Gets the operator character
  /// @return character of the operator
  char operatorChar () const;

  /// Gets the operator precedence
  /// @return precedence of the mathematical operator
  int precedence () const;

  /// Calculates the top two numbers from the stack using the operator
  /// from the queue and saves the resut to the stack
  /// @param queue reference to the queue
  /// @param stack reference to the stack
  virtual void pushToStack (std::queue<std::shared_ptr<CMathObject>> & queue,
                            std::stack<CNumber> & stack) const override;

protected:
  /// operator character
  char m_OperatorChar;
  /// precedence of the operator - 2 for * and /, 1 for + and -
  int m_Precedence;

  /// Print the operator to output stream
  /// @param os output stream
  virtual void print (std::ostream & os) const override;

  /// Performs the corresponding mathematical operation on two numbers
  /// @param lhs first number
  /// @param rhs second number
  virtual CNumber useOperator (const CNumber & lhs, const CNumber & rhs) const = 0;
};
