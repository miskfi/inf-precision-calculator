#include "COperator.h"

/// Operator for division
class CDivide : public COperator
{
public:
  /// CDivide default constructor
  CDivide ();

protected:
  /// Calculates lhs / rhs, assuming both numbers are integers
  /// @param lhs first number
  /// @param rhs second number
  /// @return CNumber with the result
  virtual CNumber useOperator (const CNumber & lhs, const CNumber & rhs) const override;
};
