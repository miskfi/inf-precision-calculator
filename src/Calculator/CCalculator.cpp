#include <algorithm>
#include <iostream>
#include "CCalculator.h"
#include "../MathObject/CMathObject.h"
#include "../Expression/CExpression.h"
#include "../Operator/COperator.h"

CCalculator::CCalculator () {}

void CCalculator::clear ()
{
  m_ExprHistory.clear();
  m_Variables.clear();
}

CNumber CCalculator::calculate (const std::string & expression)
{
  if (expression.find_first_of("+-*/%") == std::string::npos)
    throw std::invalid_argument("invalid expression");

  CExpression expr(expression, m_Variables);
  std::stack<CNumber> stack;
  std::queue<std::shared_ptr<CMathObject>> queue = expr.getQueue();
  
  // go through the queue, if there is a number at the front, push it to the stack
  // if there is an operator, calculate operation on top 2 numbers at the stack and push the result
  while (! queue.empty())
    queue.front()->pushToStack(queue, stack);

  // check if expression was successfully parsed and calculated
  if (queue.empty())
    saveToHistory(expression);
  return stack.top();
}

void CCalculator::saveToHistory (const std::string & expression)
{
  m_ExprHistory.push_back(expression);
}

void CCalculator::saveVariable (const std::string & name, const std::string & expr)
{
  if (name.find_first_not_of("123456789+-*/%") == std::string::npos)
    throw std::invalid_argument("invalid variable name");

  // rewrite already existing variable
  auto pos = find_if(m_Variables.begin(), m_Variables.end(), [& name](const CVariable & var) {return var.name() == name;});
  if (pos != m_Variables.end())
    *pos = CVariable(name, expr, m_Variables);
  else
    m_Variables.emplace_back(name, expr, m_Variables);  
}

const CVariable & CCalculator::findVariable (const std::string & name) const
{
  auto pos = find_if(m_Variables.begin(), m_Variables.end(), [&name](const CVariable & var) {return var.name() == name;});
  if (pos == m_Variables.end())
    throw std::invalid_argument("unknown variable");
  return *pos;
}

std::ostream & CCalculator::printHistory (std::ostream & os) const
{
  if (m_ExprHistory.empty())
    std::cout << "Calculator history is empty" << std::endl;
  for (auto it : m_ExprHistory)
    os << it << std::endl;
  os << std::endl;
  return os;
}

std::ostream & CCalculator::printVariables (std::ostream & os) const
{
  if (m_Variables.empty())
    std::cout << "There are no saved variables" << std::endl;
  for (auto it : m_Variables)
    os << it << std::endl;
  os << std::endl;
  return os;
}