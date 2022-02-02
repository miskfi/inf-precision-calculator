#pragma once
#include <string>
#include <vector>
#include <memory>
#include "CCalculator.h"
#include "../MathObject/CNumber.h"
#include "../Variable/CVariable.h"

/// Calculator with unlimited precision
class CApplication
{
public:
  /// Default constructor for CCalculator
  CApplication ();

  /// Runs the program
  void run ();

  /// Prints currently saved variable(s)
  void showVariables ();

  /// Saves a new variable to the calculator
  void addVariable ();

  /// Loads the expression history and saves variables from a file
  /// @param path string with the path to the file
  void loadCalculatorState (const std::string & path = "");

  /// Saves the expression history and current variables to a file
  void saveCalculatorState () const;

private:
  CCalculator calculator;
};
