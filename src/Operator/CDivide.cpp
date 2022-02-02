#include "CDivide.h"

CDivide::CDivide ()
{
  m_OperatorChar = '/';
  m_Precedence = 1;
}

CNumber CDivide::useOperator (const CNumber & lhs, const CNumber & rhs) const
{
  return lhs / rhs;
}