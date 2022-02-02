#include <cassert>
#include <sstream>
#include "../Calculator/CApplication.h"
#include "../Expression/CExpression.h"
#include "../Operator/CAdd.h"
#include "../Operator/CMultiply.h"
#include "CTest.h"

void CTest::runTests () const
{
  testNumberCalculations();
  testNumberPrinting();
  testCalculator();
  testVariables();
  testExceptions();
  std::cout << "All tests were successful" << std::endl << std::endl;
}

void CTest::testNumberCalculations () const
{
  // CNumber constructor, assingment and comparison tests
  CNumber n1 ("6374.23045");
  CNumber n2 (6374.23045);
  CNumber n3 = 87604;
  CNumber n4 = -78;
  CNumber n5 = n2;
  CNumber n6 = 78;
  CNumber n7 = -250;
  CNumber n8 = 9;
  CNumber n9 = -543.241;
  CNumber n10 = "7848989.2";
  CNumber n11 = 2546.0;
  CNumber n12 (".738");
  CNumber n13 ("-.738");
  CNumber n14 ("527.0227");
  CNumber n15 = 874;
  CNumber n16 ("1.2566548965456");

  // comparison
  assert (n1 == 6374.23045);
  assert (n1 == n2);
  assert (n1 != n3);
  assert (n1 < n3);
  assert (! (n1 > n3));
  assert (n4 == -78);
  assert (n4 != 78);
  assert (n1 > n4);
  assert (n1 == n5);
  assert (n4 < n6);
  assert (n4 != n6);
  assert (n11 == 2546);
  assert (n9 < n7);
  assert (n12 != n13);
  assert (n13 == -0.738);
  assert (n8 == CNumber("9.0000000"));
  assert (n8 == CNumber("0000000009"));
  assert (n5 <= n2);
  assert (CNumber("233.6") > CNumber ("233.42385"));

  // addition
  assert (n1 + n6 == CNumber("6452.23045"));
  assert (n6 + n8 == 87.0);
  assert (n2 + n10 == CNumber("7855363.43045"));
  assert (n3 + n9 == CNumber("87060.759"));
  assert (n7 + n6 == -172);
  assert (n12 + n13 == 0);
  assert (n9 + n4 == -621.241);
  assert (n8 + n13 == 8.262);
  assert (n8 + CNumber("0.00000000001") == CNumber("9.00000000001"));
  assert (CNumber("5165.65546549846") + CNumber ("5151345564651233.3384") == CNumber ("5151345564656398.99386549846"));
  assert (CNumber("100000000000000000000000000000000") + CNumber ("4.00000000000000000007872156156") 
          == CNumber ("100000000000000000000000000000004.00000000000000000007872156156"));
  assert (CNumber("21546541598794899765468454564") + CNumber ("-7897897986489416549865.56465") 
          == CNumber ("21546533700896913276051904698.43535"));
  assert (CNumber("23156465489465165498651894513.323213548946513") + CNumber ("1658489651564984654985641.0000000000000000189415689456") 
          == CNumber ("23158123979116730483306880154.3232135489465130189415689456"));
  assert (CNumber("0000025") + CNumber (".38") == CNumber ("25.38"));  

  // subtraction
  assert (n2 - n14 == CNumber("5847.20775"));
  assert (n6 - n8 == 69);
  assert (n3 - n9 == 88147.241);
  assert (n7 - n4 == -172);
  assert (n7 - n6 == -328);
  assert (n13 - n10 == CNumber("-7848989.938"));
  assert (CNumber("3213564135465165.233213213221484") - CNumber ("564897487987484984651.321564132651") 
          == CNumber ("-564894274423349519486.088350919429516"));
  assert (CNumber("500000000000") - CNumber ("0.000000000004") == CNumber ("499999999999.999999999996"));
  assert (CNumber("0") - CNumber ("0.00005") == CNumber ("-0.00005"));

  // multiplication
  assert (n8 * n6 == 702);
  assert (n7 * n4 == 19500);
  assert (n14 * n3 == CNumber("46169296.6108"));
  assert (n9 * n11 == CNumber("-1383091.586"));
  assert (n8 * n13 == -6.642);
  assert (CNumber("156465165.32156") * CNumber ("5189489796.2561564566") == CNumber ("811974378905768241.131864009184296"));
  assert (CNumber("21651.2") * CNumber ("134.062564651864556133200003215") == CNumber ("2902615.399790449877751139909608608"));
  assert (CNumber("3.023407") * CNumber ("5.1247") == CNumber ("15.4940538529"));

  // division
  assert (n3 / n6 == 1123);
  assert (n8 / n6 == 0);
  assert (n7 / n8 == -27);
  assert (n7 / n4 == 3);
  assert (n6 / n6 == 1);
  assert (CNumber("561561005") / CNumber ("3232165") == CNumber ("173"));
  assert (CNumber("20000000000") / CNumber ("132112") == CNumber ("151386"));
  assert (CNumber("5156156131561231864513168451865651") / CNumber ("589456") == CNumber ("8747312999717081282594745751"));
  assert (CNumber("8785551545646467884112246564894") / CNumber ("23546") == CNumber ("373122889053192384443737643"));
  assert (CNumber("797667356756757467946736752") / CNumber ("8789987966") == CNumber ("90747263800833907"));
  assert (CNumber("5156156131561231864513168451865651") / CNumber ("5894156156156156") 
          == CNumber ("874791233037808230"));

  // modulo
  assert (n6 % n8 == 6);
  assert (n3 % n6 == 10);
  assert (n15 % n6 == 16);
  assert (CNumber("879897489654") % CNumber ("54845132") == CNumber ("17036978"));

  n2 += 1278;
  assert (n2 == 7652.23045);
  assert (n2 != n5);
  n9 -= 28.487;
  assert (n9 == -571.728);
  n8 *= 421;
  assert (n8 == 3789);
  n15 /= 25;
  assert (n15 == 34);
}

void CTest::testNumberPrinting () const
{
  std::ostringstream oss;
  CNumber o1 ("5540000245008");
  CNumber o2 = "-246.00784";
  CNumber o3 ("2100007.0000035");
  CNumber o4 ("0047.027");
  CNumber o5 ("5640000000056056541.887321");
  oss << o1;
  assert (oss.str() == "5540000245008");
  oss.str("");
  oss << o2;
  assert (oss.str() == "-246.00784");
  oss.str("");
  oss << o3;
  assert (oss.str() == "2100007.0000035");
  oss.str("");
  oss << o4;
  assert (oss.str() == "47.027");
  oss.str("");
  oss << o5;
  assert (oss.str() == "5640000000056056541.887321");
  oss.str("");
}

void CTest::testCalculator () const
{
  CApplication a;
  CCalculator calc;
  std::ostringstream oss;
  std::string expr1 = "5 + 8 * ( 2 - 3 ) - 7 + 11 * 4"; // == 1
  std::string expr2 = "12 - ( 2 + 7 - ( 3 * ( 1 + 9 * ( 6 - 2 ) ) ) )"; // == 114
  std::string expr3 = "27     *    4   -   5  +  ( 3    * 15   )  + 2  "; // == 150

  oss.str("");
  oss << calc.calculate(expr1);
  assert (oss.str() == "34");
  oss.str("");
  oss << calc.calculate(expr2);
  assert (oss.str() == "114");
  oss.str("");
  oss << calc.calculate(expr3);
  assert (oss.str() == "150");
  oss.str("");

  a.loadCalculatorState("examples/save.txt");
}

void CTest::testVariables () const
{
  CCalculator c;
  std::ostringstream oss;
  c.saveVariable("y", "254603");
  c.saveVariable("pi", "3.1415");
  oss << c.calculate("y + 200");
  assert (oss.str() == "254803");
  oss.str(""); 
  oss << c.calculate("2 * pi");
  assert (oss.str() == "6.283");
  oss.str("");
  c.printHistory(oss);
  assert (oss.str() == "y + 200\n""2 * pi\n\n");
}

void CTest::testExceptions () const
{
  CApplication a;
  CCalculator c;
  try
  { c.saveVariable("1", "25"); }
  catch (const std::invalid_argument & e)
  {}

  try
  { c.saveVariable("a", "b"); }
  catch (const std::invalid_argument & e)
  {}

  try
  { a.loadCalculatorState("vvvvv"); }
  catch (const std::invalid_argument & e)
  {}

  try
  { CNumber(""); }
  catch (const std::invalid_argument & e)
  {}

  try
  { c.calculate("5 + ijkl - 2"); }
  catch (const std::invalid_argument & e)
  {}

  try
  { c.calculate("2 + ( 8"); }
  catch (const std::invalid_argument & e)
  {}
}

