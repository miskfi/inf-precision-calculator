#pragma once
#include <map>
#include <ostream>
#include <memory>
#include <string>
#include "CMathObject.h"

/// Number of unlimited size, class supports both integers and floats
class CNumber : public CMathObject
{
public:
  /// Default constructor for CNumber
  CNumber ();
  /// CNumber constructor from int
  /// @param num number to convert
  CNumber (double num);
  /// CNumber constructor from double
  /// @param num number to convert
  CNumber (int num);
  /// CNumber constructor from char array
  /// @param val char array with the number
  CNumber (const char * val);
  /// CNumber constructor from string
  /// @param val string with the number
  CNumber (const std::string & val);
  /// CNumber constructor from vector of integers
  /// @param vec vector of integers
  CNumber(const std::vector<int> & vec);
  /// Copy constructor for CNumber
  /// @param src CNumber to copy
  CNumber (const CNumber & src);
  /// Assignment operator for CNumber
  /// @param src CNumber to copy
  /// @return new instance of CNumber
  CNumber operator = (const CNumber & src);

  /// Adds two numbers and sets the correct sign
  /// @param rhs number to add
  /// @return number with the result
  CNumber operator + (const CNumber & rhs) const;
  /// Subtracts two numbers and sets the correct sign
  /// @param rhs number to subtract
  /// @return number with the result
  CNumber operator - (const CNumber & rhs) const;
  /// Multiplies two numbers and sets the correct sign
  /// @param rhs number to multiply by
  /// @return number with the result
  CNumber operator * (const CNumber & rhs) const;
  /// Divides two integer numbers
  /// @param rhs number to add
  /// @return result of the division
  CNumber operator / (const CNumber & rhs) const;
  /// Calculates the modulo of two integers
  /// @param mod modulus
  /// @return result of the modulo
  CNumber operator % (const CNumber & mod) const;
  /// Adds two floating-point numbers and assigns the result to the current object
  /// @param rhs number to add
  /// @return reference to *this with the result
  CNumber & operator += (const CNumber & rhs);
  /// Subtracts two floating-point numbers and assigns the result to the current object
  /// @param rhs number to subtract
  /// @return reference to *this with the result
  CNumber & operator -= (const CNumber & rhs);
  /// Multiplies two floating-point numbers and assigns the result to the current object
  /// @param rhs number to multiply by
  /// @return reference to *this with the result
  CNumber & operator *= (const CNumber & rhs);
  /// Divides two integer number and assigns the result to the current object
  /// @param rhs number to divide by
  /// @return reference to *this with the result
  CNumber & operator /= (const CNumber & rhs);
  /// Calculates the modulo of two integers and assigns the result to the current object
  /// @param mod modulus
  /// @return reference to *this with the result
  CNumber & operator %= (const CNumber & mod);
  /// Unary minus operator
  /// @return object with the inverse value of *this
  CNumber   operator -  () const;

  /// Compares if two numbers are equal
  /// @param rhs number to compare
  /// @return 1 if equal, 0 if not
  bool operator == (const CNumber & rhs) const;
  /// Compares if two numbers are not equal
  /// @param rhs number to compare
  /// @return 1 if not equal, 0 if equal
  bool operator != (const CNumber & rhs) const;
  /// Compares if number is smaller than a different number
  /// @param rhs number to compare
  /// @return 1 if lhs < rhs, 0 otherwise
  bool operator <  (const CNumber & rhs) const;
  /// Compares if number is smaller than or equal to a different number
  /// @param rhs number to compare
  /// @return 1 if lhs <= rhs, 0 otherwise
  bool operator <= (const CNumber & rhs) const;
  /// Compares if number is greater than a different number
  /// @param rhs number to compare
  /// @return 1 if lhs > rhs, 0 otherwise
  bool operator >  (const CNumber & rhs) const;
  /// Compares if number is greater than or equal to a different number
  /// @param rhs number to compare
  /// @return 1 if lhs >= rhs, 0 otherwise
  bool operator >= (const CNumber & rhs) const;

  /// Pushes number to the stack during the calculation of expression
  /// @param queue reference to the queue of MathObjects
  /// @param stack reference to the number stack
  virtual void pushToStack  (std::queue<std::shared_ptr<CMathObject>> & queue, 
                             std::stack<CNumber> & stack) const override;

protected:
  /// sign of the number
  bool m_Negative = false;
  /// vector with digits of the number divided into blocks of BLOCK_SIZE
  std::vector<int> m_Digits;
  /// number of decimal places
  int m_DecimalPlaces = 0;
  /// number of blocks with decimal digits
  int m_DecimalBlocks = 0;
  /// size of the blocks in the digit vectors
  int BLOCK_SIZE = 8;
  /// base of the digits (10**BLOCK_SIZE)
  int BASE = 100000000;

  /// Converts string to a map of digits
  /// @param str string to convert
  void convertString (const std::string & str);
  /// Counts trailing numbers in an integer using bitwise &
  /// @param num number
  /// @return number of trailing zeroes
  int countTrailing (int num) const;
  /// Removes blocks of leading & trailing zeroes from the vector of digits
  void removeLeadingTrailing ();
  /// Breaks individual digit blocks of the number into two
  /// @return new object with smaller blocks
  CNumber breakUp () const;
  /// Merge smaller blocks of size 4 into larger ones of size 8
  void merge ();

  /// Compares two numbers
  /// @param rhs number to compare with
  /// @return -1 if lhs<rhs, 0 if lhs==rhs, 1 lhs>rhs
  int compare (const CNumber & rhs) const;
  /// Adds two floating-point numbers by adding individual digits
  /// @param rhs number to add
  /// @return number with the result
  CNumber add (const CNumber & rhs) const;
  /// Subtracts two numbers, where lhs > rhs
  /// @param rhs number to subtract
  /// @return number with the result
  CNumber subtract (const CNumber & rhs) const;
  /// Multiplies two numbers
  /// @param rhs number to multiply
  /// @return number with the result
  CNumber multiply (const CNumber & rhs) const;
  /// Divides two numbers
  /// @param rhs number to divide by
  /// @param remainder number where the division remainder will be stored
  /// @return division result
  CNumber divide (const CNumber & rhs, CNumber & remainder) const;
  /// Creates an absolute value copy of number
  /// @return absolute value of number
  CNumber absolute () const;

  /// Prints the number to output stream
  /// @param os output stream
  virtual void print (std::ostream & os) const override;
};
