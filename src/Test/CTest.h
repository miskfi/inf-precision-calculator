#pragma once

/// Class tests
class CTest
{
public:
  /// Run all tests
  void runTests () const;

  /// Test comparison and calculations for CNumber
  void testNumberCalculations () const;

  /// Test CNumber printing
  void testNumberPrinting () const;

  /// Test calculation of expressions
  void testCalculator () const;

  /// Test saving and using variables
  void testVariables () const;

  /// Test exceptions
  void testExceptions () const;
};
