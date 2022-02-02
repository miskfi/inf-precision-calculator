#include "CMultiply.h"

CMultiply::CMultiply ()
{
  m_OperatorChar = '*';
  m_Precedence = 2;
}

CNumber CMultiply::useOperator (const CNumber & lhs, const CNumber & rhs) const
{
  return lhs * rhs;
}