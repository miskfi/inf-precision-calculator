#include "CSubtract.h"

CSubtract::CSubtract ()
{
  m_OperatorChar = '-';
  m_Precedence = 1;
}

CNumber CSubtract::useOperator (const CNumber & lhs, const CNumber & rhs) const
{ 
  return lhs - rhs;
}