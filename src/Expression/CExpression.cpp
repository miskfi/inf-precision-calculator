#include <iostream>
#include <sstream>
#include <stack>
#include <queue>
#include <exception>
#include <algorithm>
#include "CExpression.h"
#include "../Operator/COperator.h"
#include "../Operator/CAdd.h"
#include "../Operator/CSubtract.h"
#include "../Operator/CMultiply.h"
#include "../Operator/CDivide.h"
#include "../Operator/CMod.h"
#include "../Operator/CBracket.h"
#include "../MathObject/CNumber.h"

CExpression::CExpression (const std::string & expr, const std::vector<CVariable> & vars)
{
  parse(expr, vars);
}

void CExpression::parse (const std::string & expr, const std::vector<CVariable> & vars)
{
  std::stack<std::shared_ptr<COperator>> opStack;
  std::istringstream iss(expr);
  std::string token;

  iss >> std::ws; // skip leading whitespaces
  while (std::getline(iss, token, ' '))
  {
    iss >> std::ws; // skip whitespaces
    if (token.empty()) break;

    if (isNumber(token))
      m_outputQueue.emplace(std::make_shared<CNumber>(token));
    else if (isOperator(token))
      parseOperator(opStack, token);
    else if (token == "(")
      opStack.emplace(std::make_shared<CBracket>());
    else if (token == ")")
      parseRBracket(opStack);
    // add variable
    else if (token.find_first_not_of("123456789+-*/%") != std::string::npos)
      parseVar(opStack, token, vars);
    else
      throw std::invalid_argument("invalid character");
  }

  // push remaining operators to the queue
  while (!opStack.empty())
  {
    if (opStack.top()->operatorChar() == '(' || opStack.top()->operatorChar() == ')')
      throw std::invalid_argument("parenthesis mismatch");
    m_outputQueue.push(opStack.top());
    opStack.pop();
  }

  m_Infix = expr;
}

void CExpression::parseRBracket (std::stack<std::shared_ptr<COperator>> & opStack)
{
  while (opStack.top()->operatorChar() != '(')
  {
    m_outputQueue.push(opStack.top());
    opStack.pop();
    if (opStack.empty())
      throw std::invalid_argument("parenthesis mismatch");
  }
  opStack.pop(); // discard left parenthesis
}

void CExpression::parseVar (std::stack<std::shared_ptr<COperator>> & opStack, std::string & variable,
                            const std::vector<CVariable> & vars)
{
  // find if the variable is saved in the vars vector
  auto pos = find_if(vars.begin(), vars.end(), 
             [&variable](const CVariable & var) {return var.name() == variable;});

  if (pos != vars.end())
  {
    std::queue<std::shared_ptr<CMathObject>> q = pos->queue();
    // push all the elements from parsed variable to the queue
    while (!q.empty())
    {
      m_outputQueue.push(q.front());
      q.pop();
    }
  }
  else
    throw std::invalid_argument("unknown variable");
}

void CExpression::parseOperator (std::stack<std::shared_ptr<COperator>> & opStack, std::string & op)
{
  while (!opStack.empty() && opStack.top()->operatorChar() != '(')
  {
    if (opStack.top()->precedence() >= opPrecedence(op))
    {
      m_outputQueue.push(opStack.top());
      opStack.pop();
    }
    else 
      break;
  } 
  switch (op.front())
  {
    case '+': opStack.emplace(std::make_shared<CAdd>()); break;
    case '-': opStack.emplace(std::make_shared<CSubtract>()); break;
    case '*': opStack.emplace(std::make_shared<CMultiply>()); break;
    case '/': opStack.emplace(std::make_shared<CDivide>()); break;
    case '%': opStack.emplace(std::make_shared<CMod>()); break;
  }
}

bool CExpression::isNumber (const std::string & str) const
{
  // check if string contains two dots or dashes
  if (str.find_first_of("-") != str.find_last_of("-") ||
      str.find_first_of(".") != str.find_last_of("."))
    return false;
  return !str.empty() && str.find_first_not_of("-. 0123456789") == std::string::npos
          && str.find_first_of("0123456789") != std::string::npos;
}

bool CExpression::isOperator (const std::string & str) const
{
  return (str == "+" || str == "-" || str == "*" || str == "/" || str == "%");
}

int CExpression::opPrecedence (const std::string & op) const
{
  if (op == "+" || op == "-")
    return 1;
  else if (op == "*" || op == "/" || op == "%")
    return 2;
  return -1;
}

std::queue<std::shared_ptr<CMathObject>> CExpression::getQueue () const
{
  return m_outputQueue;
}

std::ostream & operator << (std::ostream & os, const CExpression & expr)
{
  return os << expr.m_Infix;
}
