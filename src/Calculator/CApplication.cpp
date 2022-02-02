#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "CApplication.h"
#include "CCalculator.h"

CApplication::CApplication ()
{}

void CApplication::run ()
{
  std::string str;
  std::cout << "Welcome to the infinite precision calculator!\n"
               "Enter expression to calculate\n"
               "Enter \"save\" or \"load\" to save/load calculator state\n"
               "Enter \"new variable\" to add a new variable or change value of an existing one\n"
               "Enter \"show history\" to show previously calculated expressions\n"
               "Enter \"show variable\" to show currently saved variable(s)\n"
               "EOF to quit" << std::endl << std::endl;

  while (std::getline(std::cin, str))
  {
    try
    {
      if (str.empty()) break;
      if (str == "save")
        saveCalculatorState();
      else if (str == "load")
        loadCalculatorState();
      else if (str == "new variable")
        addVariable();
      else if (str == "show history")
        calculator.printHistory(std::cout);
      else if (str == "show variable")
        showVariables();
      else
      {
        CNumber res = calculator.calculate(str);
        std::cout << "== " << res << std::endl << std::endl;
      }
    }
    catch(const std::exception & e)
    {
      std::cout << "Error: " << e.what() << std::endl << std::endl;
    }
  }
}

void CApplication::showVariables ()
{
  std::string str;
  std::cout << "Enter variable name or enter \"all\" to show all saved variables:" << std::endl;
  std::getline(std::cin, str);
  
  if (str.empty())
    throw std::invalid_argument("no name was entered");
  else if (str == "all")
    calculator.printVariables(std::cout);
  else
    std::cout << calculator.findVariable(str) << std::endl << std::endl;
}

void CApplication::addVariable ()
{
  std::string name, expression;

  std::cout << "Enter variable name:" << std::endl;
  std::getline(std::cin, name);
  if (name.empty())
    throw std::invalid_argument("no name was entered");
  if (name.find_first_not_of("123456789+-*/%") == std::string::npos)
    throw std::invalid_argument("invalid variable name");
  
  std::cout << "Enter expression or value you want to save to the variable:" << std::endl;
  std::getline(std::cin, expression);
  if (name.empty())
    throw std::invalid_argument("no expression was entered");

  calculator.saveVariable(name, expression);
  std::cout << std::endl;
}

void CApplication::loadCalculatorState (const std::string & path)
{
  int failed = 0;
  std::string filename, str, varName, varNum, eq;
  std::vector<std::string> history;

  if (path.empty())
  {
    std::cout << "Enter file path to load from:" << std::endl;
    std::getline(std::cin, filename);
    if (filename.empty())
      throw std::invalid_argument("no file path specified");
  }
  else
    filename = path;

  std::ifstream file(filename);
  if (!file)
    throw std::invalid_argument("file doesn't exist");

  // load expression history
  std::getline(file, str);
  if (str != "Expressions:")
    throw std::invalid_argument("couldn't read savefile");
  while (std::getline(file, str))
  {
    if (str.empty()) break;
    history.push_back(str);
  }

  std::getline(file, str);
  if (str != "Variables:")
    throw std::invalid_argument("couldn't read savefile");

  calculator.clear();
  for (auto it : history)
    calculator.saveToHistory(it);

  // load variables
  while (std::getline(file, str))
  {
    if (str.empty()) break;
    try
    {
      std::istringstream iss(str);
      std::getline (iss, varName, ' ');
      std::getline (iss, eq, ' ');
      std::getline (iss, varNum);

      if (varName.empty() || varNum.empty() || eq != "==")
        throw std::invalid_argument("invalid variable or expression");
      calculator.saveVariable(varName, varNum);
    }
    catch (const std::exception & e)
    {
      std::cout << "Error loading variable " << varName << std::endl;
      failed++;
    }
    varName = ""; varNum = ""; eq = "";
  }

  failed == 0 ? std::cout << "Calculator state successfully loaded" << std::endl << std::endl :
    std::cout << "Calculator state loaded, " << failed << " variables failed and weren't loaded" << std::endl << std::endl;
  file.close();
}

void CApplication::saveCalculatorState () const
{
  std::string filename;
  std::cout << "Enter file path to save to:" << std::endl;
  std::getline(std::cin, filename);
    if (filename.empty())
      throw std::invalid_argument("no file path specified");

  std::ofstream file(filename);
  if (!file)
    throw std::invalid_argument("invalid file path");

  file << "Expressions:" << std::endl;
  calculator.printHistory(file);
  file << "Variables:" << std::endl;
  calculator.printVariables(file);

  std::cout << "Calculator state successfully saved" << std::endl << std::endl;
  file.close();
}
