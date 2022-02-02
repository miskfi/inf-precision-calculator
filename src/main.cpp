#include <string>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Calculator/CApplication.h"
#include "Test/CTest.h"

int main ()
{
  /// CTest t;
  /// t.runTests();

  CApplication app;
  app.run();

  if (!std::cin.eof())
  {
    std::cout << "Invalid input" << std::endl;
    return 1;
  }

  return 0;
}
