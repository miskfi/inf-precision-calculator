#include "COperator.h"

/// Operator for subtraction
class CSubtract : public COperator
{
public:
  /// CSubtract default constructor
  CSubtract ();

protected:
  /// Calculates lhs - rhs
  /// @param lhs first number
  /// @param rhs second number
  /// @return CNumber with the result
  virtual CNumber useOperator (const CNumber & lhs, const CNumber & rhs) const override;
};
