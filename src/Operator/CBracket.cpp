#include "CBracket.h"

CBracket::CBracket ()
{
  m_OperatorChar = '(';
  m_Precedence = 0;
}

CNumber CBracket::useOperator (const CNumber & lhs, const CNumber & rhs) const
{
  throw std::invalid_argument("Invalid operation");
}