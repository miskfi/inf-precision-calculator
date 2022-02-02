#include "COperator.h"

/// Opening bracket
class CBracket : public COperator
{
public:
  /// CBracket constructor
  CBracket ();

protected:
  /// Throws an exception when trying to use bracket as an operator
  virtual CNumber useOperator (const CNumber & lhs, const CNumber & rhs) const override;
};
