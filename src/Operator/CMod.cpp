#include "CMod.h"

CMod::CMod ()
{
  m_OperatorChar = '%';
  m_Precedence = 2;
}

CNumber CMod::useOperator (const CNumber & lhs, const CNumber & rhs) const
{
  return lhs % rhs;
}