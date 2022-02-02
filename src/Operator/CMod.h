#include "COperator.h"

/// Operator for modulo
class CMod : public COperator
{
public:
  /// CMod default constructor
  CMod ();

protected:
  /// Calculates lhs % rhs, assuming both numbers are integers
  /// @param lhs first number
  /// @param rhs second number
  /// @return CNumber with the result
  virtual CNumber useOperator (const CNumber & lhs, const CNumber & rhs) const override;
};
