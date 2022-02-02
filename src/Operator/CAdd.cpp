#include "CAdd.h"

CAdd::CAdd ()
{
  m_OperatorChar = '+';
  m_Precedence = 1;
}

CNumber CAdd::useOperator (const CNumber & lhs, const CNumber & rhs) const
{
  return lhs + rhs;
}