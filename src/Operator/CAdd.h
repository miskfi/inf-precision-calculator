#pragma once
#include "COperator.h"

/// Operator for addition
class CAdd : public COperator
{
public:
  /// CAdd constructor
  CAdd ();

protected:
  /// Calculates lhs + rhs
  /// @param lhs first number
  /// @param rhs second number
  /// @return CNumber with the result
  virtual CNumber useOperator (const CNumber & lhs, const CNumber & rhs) const override;
};
