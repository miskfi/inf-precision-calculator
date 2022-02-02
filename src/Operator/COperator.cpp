#include "COperator.h"
#include "../MathObject/CNumber.h"

COperator::COperator () {}

COperator::~COperator () {}

char COperator::operatorChar () const
{
  return m_OperatorChar;
}

int COperator::precedence () const
{
  return m_Precedence;
}

void COperator::pushToStack (std::queue<std::shared_ptr<CMathObject>> & queue,
                             std::stack<CNumber> & stack) const
{
  if (stack.size() < 2)
    throw std::invalid_argument("not enough numbers to calculate");

  CNumber num2 = stack.top(); stack.pop();
  CNumber num1 = stack.top(); stack.pop();
  CNumber res = useOperator(num1, num2);
  stack.push(res);
  queue.pop();
}

void COperator::print (std::ostream & os) const
{
  os << m_OperatorChar;
}