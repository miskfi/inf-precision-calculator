#include "COperator.h"

/// Operator for multiplication
class CMultiply : public COperator
{
public:
  /// CMultiply default constructor
  CMultiply ();

protected:
  /// Calculates lhs * rhs
  /// @param lhs first number
  /// @param rhs second number
  /// @return CNumber with the result
  virtual CNumber useOperator (const CNumber & lhs, const CNumber & rhs) const override;
};
