#include "CVariable.h"
#include "../Expression/CExpression.h"

CVariable::CVariable (const std::string & name, const std::string & expr, const std::vector<CVariable> & vars)
{
  m_Name = name;
  m_Expression = expr;
  m_Queue = CExpression(m_Expression, vars).getQueue();
}

bool CVariable::operator== (const CVariable & rhs) const
{
  return m_Name == rhs.m_Name;
}

std::string CVariable::expression () const
{
  return m_Expression;
}

std::string CVariable::name () const
{
  return m_Name;
}

std::queue<std::shared_ptr<CMathObject>> CVariable::queue () const
{
  return m_Queue;
}

std::ostream & operator << (std::ostream & os, const CVariable & var)
{
  return os << var.m_Name << " == " << var.m_Expression;
}