#include <vector>
#include <cmath>
#include <iomanip>
#include "CNumber.h"

CNumber::CNumber () {}

void CNumber::convertString (const std::string & str)
{
  str.find_first_of("-") == std::string::npos ? m_Negative = false : m_Negative = true;
  auto decimalDot = str.find_first_of("."); // position of the decimal dot
  if (decimalDot == std::string::npos)
    decimalDot = str.size();

  // position of the last non-zero decimal digit (skipping trailing zeroes)
  auto lastDigit = str.find_last_of("123456789");
  lastDigit < decimalDot ? m_DecimalPlaces = 0 : m_DecimalPlaces = lastDigit - decimalDot;
  // position of the first non-zero digit (skipping leading zeroes)
  auto firstDigit = str.find_first_of("123456789");

  // no digit was found 
  if (lastDigit == std::string::npos || firstDigit == std::string::npos)
  {
    if (!str.empty()) // == 0
    {
      m_DecimalPlaces = 0;
      return;
    }
    else
      throw std::invalid_argument ("not a number");
  }

  int i;
  // convert decimal digits
  for (i = (int) decimalDot+1; i + (BLOCK_SIZE -1) <= (int) lastDigit; i += BLOCK_SIZE)
  {
    m_Digits.insert(m_Digits.begin(), stoi(str.substr(i, BLOCK_SIZE)));
    m_DecimalBlocks++;
  }
  
  // add last decimal group in case it wasn't yet pushed
  if ((lastDigit > decimalDot) && ((lastDigit-i+1) % BLOCK_SIZE != 0))
  {
    std::string substr = str.substr(i, (lastDigit-i+1) % BLOCK_SIZE);
    // multiply the substring by a power of 10 to always have 4 digits in the last blockS
    m_Digits.insert(m_Digits.begin(), stoi(substr) * pow(10, BLOCK_SIZE - substr.size()) );
    m_DecimalBlocks++;
  }

  // convert integer digits
  for (i = (int) decimalDot; i - BLOCK_SIZE >= (int) firstDigit; i -= BLOCK_SIZE)
    m_Digits.push_back(stoi(str.substr(i-BLOCK_SIZE, BLOCK_SIZE)));

  // subtract the offset of the first position to calculate the size of the last, unfinished block
  i -= firstDigit; 
  if ((firstDigit < decimalDot) && (i % BLOCK_SIZE != 0))  
    m_Digits.push_back(stoi(str.substr(firstDigit, i % BLOCK_SIZE)));
}

CNumber::CNumber (int num)
{
  std::string val = std::to_string(num);
  convertString(val);
}

CNumber::CNumber (double num)
{
  std::string val = std::to_string(num);
  convertString(val);
}

CNumber::CNumber (const char * val)
{
  convertString(val);
}

CNumber::CNumber (const std::string & val)
{
  convertString(val);
}

CNumber::CNumber (const std::vector<int> & vec)
{
  m_Digits = vec;
}

CNumber::CNumber (const CNumber & src)
{
  m_Negative = src.m_Negative;
  m_Digits = src.m_Digits;
  m_DecimalPlaces = src.m_DecimalPlaces;
  m_DecimalBlocks = src.m_DecimalBlocks;
}

CNumber CNumber::operator = (const CNumber & src)
{
  if (&src == this) return *this;
  m_Digits.clear();

  m_Negative = src.m_Negative;
  m_Digits = src.m_Digits;
  m_DecimalPlaces = src.m_DecimalPlaces;
  m_DecimalBlocks = src.m_DecimalBlocks;
  return * this;
}

int CNumber::countTrailing (int num) const
{
  int trailing = 0;
  while (num != 0)
  {
    if (num & 1)
      break;
    else
    {
      trailing++;
      num >>= 1;
    }
  }
  return trailing;
}

void CNumber::removeLeadingTrailing ()
{
  // remove leading
  for (int i = m_Digits.size()-1; i >= m_DecimalBlocks; i--)
  {
    if (m_Digits[i] == 0)
      m_Digits.erase(m_Digits.begin()+i);
    else // found the first block with digits
      break;
  }

  // remove trailing
  int i = 0;
  while (i < m_DecimalBlocks)
  {
    if (m_Digits[i] == 0)
    {
      m_Digits.erase (m_Digits.begin()+i);
      m_DecimalBlocks--;
    }   
    else // found the first block with digits
      break;
  }

  int trailing;
  m_DecimalBlocks > 0 ? trailing = countTrailing(m_Digits[i]) : trailing = 0;
  m_DecimalPlaces = m_DecimalBlocks * BLOCK_SIZE - trailing;
}

CNumber CNumber::breakUp () const
{
  CNumber newNum;
  newNum.m_DecimalPlaces = m_DecimalPlaces;
  newNum.m_DecimalPlaces = m_DecimalBlocks * 2;
  newNum.BLOCK_SIZE = 4;
  newNum.BASE = 10000;
  newNum.m_Negative = m_Negative;

  for (auto it = m_Digits.begin(); it != m_Digits.end(); ++it)
  {
    newNum.m_Digits.push_back(*it % 10000);
    newNum.m_Digits.push_back(*it / 10000);
  }

  newNum.removeLeadingTrailing();
  return newNum;
}

void CNumber::merge ()
{
  std::vector<int> newDigits;
  int lower, higher;

  // merge decimal blocks
  for (int i = 0; i < m_DecimalBlocks; i += 2)
  { // check that higher block isn't out of range
    i+1 < m_DecimalBlocks ? higher = m_Digits[i+1] : higher = 0;
    lower = m_Digits[i];
    newDigits.push_back(lower + higher * 10000);
  }

  // merge integer blocks
  for (size_t i = m_DecimalBlocks; i < m_Digits.size(); i += 2)
  {
    i+1 < m_Digits.size() ? higher = m_Digits[i+1] : higher = 0;
    lower = m_Digits[i];
    newDigits.push_back(lower + higher * 10000);
  }
  
  m_DecimalBlocks /= 2;
  m_Digits = newDigits;
  BLOCK_SIZE = 8;
  BASE = 100000000;
}

int CNumber::compare (const CNumber & rhs) const
{
  // adjust return values if comparing two negative nums (1 for comparing positive nums, -1 for negative)
  int cmpNegative = 1, i, j; 
  // sign mismatch
  if (m_Negative && !rhs.m_Negative) return -1;
  if (!m_Negative && rhs.m_Negative) return 1;
  if (m_Negative && rhs.m_Negative) cmpNegative = -1;
  
  // compare number of integer blocks
  if (m_Digits.size()-m_DecimalBlocks > rhs.m_Digits.size()-rhs.m_DecimalBlocks) return 1 * cmpNegative;
  if (m_Digits.size()-m_DecimalBlocks < rhs.m_Digits.size()-rhs.m_DecimalBlocks) return -1 * cmpNegative;

  // same number of integer blocks, compare individual values in the blocks
  for (i = m_Digits.size()-1, j = rhs.m_Digits.size()-1; i >= 0 && j >= 0; i--, j--)
  {
    if (m_Digits[i] > rhs.m_Digits[j])  return 1 * cmpNegative;
    if (m_Digits[i] < rhs.m_Digits[j])  return -1 * cmpNegative;
  }

  // check if one of the numbers has more numbers to compare (i. e. the index is > than the other one)
  if (i > j) return 1 * cmpNegative;
  if (j > i) return -1 * cmpNegative;
  return 0;
}

CNumber CNumber::absolute () const
{
  CNumber num (*this);
  num.m_Negative = false;
  return num;
}

CNumber CNumber::add (const CNumber & rhs) const
{
  const CNumber * moreDec;
  int carry = 0, subRes = 0, lShift = 0, rShift = 0, l, r, maxPower;
  // number of extra decimal blocks in one of the numbers
  int decimalDiffBlocks = abs(rhs.m_DecimalBlocks - m_DecimalBlocks);

  CNumber res;
  res.m_DecimalPlaces = std::max(m_DecimalPlaces, rhs.m_DecimalPlaces);
  res.m_DecimalBlocks = std::max(m_DecimalBlocks, rhs.m_DecimalBlocks);

  // get the offset for each number based on the extra decimal blocks
  // to compare digits at the same position
  if (m_DecimalBlocks > rhs.m_DecimalBlocks)
  {
    lShift = decimalDiffBlocks;
    moreDec = this;
  }
  else if (m_DecimalBlocks < rhs.m_DecimalBlocks)
  {
    rShift = decimalDiffBlocks; 
    moreDec = &rhs;
  }

  m_Digits.size()-m_DecimalBlocks > rhs.m_Digits.size()-rhs.m_DecimalBlocks ?
    maxPower = m_Digits.size() : maxPower = rhs.m_Digits.size();
  
  // "trailing blocks" from number with more deicmals
  for (int i = 0; i < decimalDiffBlocks; i++)
    res.m_Digits.push_back(moreDec->m_Digits[i]);

  for (int i = 0; i < maxPower; i++)
  {
    // check if values aren't out of range
    i+lShift > (int) m_Digits.size()-1 ? l = 0 : l = m_Digits[i+lShift];
    i+rShift > (int) rhs.m_Digits.size()-1 ? r = 0 : r = rhs.m_Digits[i+rShift];

    subRes = r + l + carry;
    carry = subRes / BASE;
    res.m_Digits.push_back(subRes % BASE);
  }

  if (carry)
    res.m_Digits.push_back(carry);
  res.removeLeadingTrailing();
  return res;
}

CNumber CNumber::subtract (const CNumber & rhs) const
{
  const CNumber * moreDec;
  int borrow = 0, lShift = 0, rShift = 0, l, r;
  // number of extra decimal blocks in one of the numbers
  int decimalDiffBlocks = abs(rhs.m_DecimalBlocks - m_DecimalBlocks);

  CNumber res;
  res.m_DecimalPlaces = std::max(m_DecimalPlaces, rhs.m_DecimalPlaces);
  res.m_DecimalBlocks = std::max(m_DecimalBlocks, rhs.m_DecimalBlocks);

  // get the offset for each number based on the extra decimal blocks
  // to compare digits at the same position
  if (m_DecimalBlocks > rhs.m_DecimalBlocks)
  {
    lShift = decimalDiffBlocks;
    moreDec = this;
  }
  else if (m_DecimalBlocks < rhs.m_DecimalBlocks)
  {
    rShift = decimalDiffBlocks;
    moreDec = &rhs;
  }

  // "trailing blocks" from number with more deicmals
  for (int i = 0; i < decimalDiffBlocks; i++)
  {
    if (moreDec == this)
      res.m_Digits.push_back(moreDec->m_Digits[i]);
    else
    { // subtract rhs from BASE, since all digit blocks have fixed length of BLOCK_SIZE
      // i. e. 2.0 - 3.45 --> 10000-4500 for base 10000
      res.m_Digits.push_back(BASE - (moreDec->m_Digits[i]+borrow));
      borrow = 1;
    }
  }
  
  for (size_t i = 0; i+lShift < m_Digits.size(); i++)
  {
    l = m_Digits[i+lShift];
    // check if rhs isn't out of range
    i+rShift > rhs.m_Digits.size()-1 ? r = 0 + borrow : r = rhs.m_Digits[i+rShift] + borrow;

    if (l < r) {l += BASE; borrow = 1;}
    else borrow = false;
    res.m_Digits.push_back(l-r);
  }

  res.removeLeadingTrailing();
  return res;
}

CNumber CNumber::multiply (const CNumber & rhs) const
{
  int carry = 0;
  CNumber res;
  res.m_DecimalPlaces = m_DecimalPlaces+rhs.m_DecimalPlaces;
  res.m_DecimalBlocks = m_DecimalBlocks+rhs.m_DecimalBlocks;
  std::vector<long long> subRes (m_Digits.size()+rhs.m_Digits.size(), 0);

  // multiply all digits from lhs with all digits from rhs
  // the products will be on position i+j in the new number
  for (size_t i = 0; i < m_Digits.size(); i++)
    for (size_t j = 0; j < rhs.m_Digits.size(); j++)
      subRes[i+j] += ((long long) m_Digits[i] * (long long) rhs.m_Digits[j]);

  // sort out the carry between the sub-results
  for (size_t i = 0; i < subRes.size(); i++)
  {
    subRes[i] += carry;
    carry = subRes[i] / BASE;
    res.m_Digits.push_back(subRes[i] % BASE);
  }

  res.removeLeadingTrailing();
  return res;
}

CNumber CNumber::divide (const CNumber & rhs, CNumber & remainder) const
{
  int multiples = 0;
  std::vector<int> resDigits;
  CNumber l = breakUp(), r = rhs.breakUp();
  remainder.BLOCK_SIZE = 4;
  remainder.BASE = 10000;

  for (int i = l.m_Digits.size()-1; i >= 0; i--)
  {
    remainder.m_Digits.insert(remainder.m_Digits.begin(), l.m_Digits[i]);
    // subtract rhs until it's larger than the remainder, then move to another digit
    if (remainder >= r.absolute())
    {
      while (remainder >= r.absolute())
      {
        remainder = remainder.subtract(r);
        multiples++;
      }
      resDigits.insert(resDigits.begin(), multiples);
      multiples = 0;
    }
  }

  CNumber res (resDigits);
  res.merge();
  remainder.merge();
  return res;
}

CNumber CNumber::operator+ (const CNumber & rhs) const
{
  if (m_Negative && rhs.m_Negative) // (-a) + (-b)
    return -add(rhs);
  if (!m_Negative && rhs.m_Negative) //  a + (-b)
  {
    if (rhs.absolute() > *this)
      return -rhs.subtract(*this);
    else
      return subtract(rhs);
  }
  if (m_Negative && !rhs.m_Negative) // (-a) + b
  {
    if (this->absolute() > rhs)
      return -subtract(rhs);
    else
      return rhs.subtract(*this);
  }
  return add(rhs); // a + b
}

CNumber & CNumber::operator += (const CNumber & rhs)
{
  *this = *this + rhs;
  return *this;
}

CNumber CNumber::operator - (const CNumber & rhs) const
{
  if (!m_Negative && rhs.m_Negative) // a - (-b)
    return add(rhs);
  if (m_Negative && rhs.m_Negative) // (-a) - (-b)
  {
    if (this->absolute() > rhs)
      return -subtract(rhs);
    else
      return rhs.subtract(*this);
  }
  if (m_Negative && !rhs.m_Negative) // (-a) - b == -(a + b)
    return -add(rhs);

  if (rhs.absolute() > *this) // a - b
    return -rhs.subtract(*this);
  return subtract(rhs);
}

CNumber & CNumber::operator -= (const CNumber & rhs)
{
  *this = *this - rhs;
  return *this;
}

CNumber CNumber::operator * (const CNumber & rhs) const
{
  CNumber res = multiply(rhs);
  if (m_Negative && rhs.m_Negative) // (-a) * (-b)
    res.m_Negative = false;
  else if (m_Negative || rhs.m_Negative) // (-a) * b || a * (-b)
    res.m_Negative = true;
  return res;
}

CNumber & CNumber::operator *= (const CNumber & rhs)
{
  *this = *this * rhs;
  return *this;
}

CNumber CNumber::operator / (const CNumber & rhs) const
{
  if (rhs == 0)
    throw std::invalid_argument("division by zero");
  if (m_DecimalPlaces != 0 || rhs.m_DecimalPlaces != 0)
    throw std::domain_error("operation not supported for floats");

  CNumber remainder, res = divide(rhs, remainder);
  if (m_Negative && rhs.m_Negative) // (-a) * (-b)
    res.m_Negative = false;
  else if (m_Negative || rhs.m_Negative) // (-a) * b || a * (-b)
    res.m_Negative = true;
  return res;
}

CNumber & CNumber::operator /= (const CNumber & rhs)
{
  *this = *this / rhs;
  return *this;
}

CNumber CNumber::operator % (const CNumber & mod) const
{
  if (mod == 0)
    throw std::invalid_argument("division by zero");
  if (m_DecimalPlaces != 0 || mod.m_DecimalPlaces != 0)
    throw std::domain_error("operation not supported for floats");

  CNumber remainder;
  divide(mod, remainder);
  remainder.m_Negative = m_Negative;
  return remainder;
}

CNumber & CNumber::operator %= (const CNumber & mod)
{
  *this = *this % mod;
  return *this;
}

CNumber CNumber::operator - () const
{
  CNumber ret = *this;
  ret.m_Negative = !ret.m_Negative;
  return ret;
}

bool CNumber::operator == (const CNumber & rhs) const
{
  if (compare(rhs) == 0) return true;
  return false;
}

bool CNumber::operator != (const CNumber & rhs) const
{
  if (compare(rhs) != 0) return true;
  return false;
}

bool CNumber::operator < (const CNumber & rhs) const
{
  if (compare(rhs) == -1) return true;
  return false;
}

bool CNumber::operator <= (const CNumber & rhs) const
{
  if (compare(rhs) != 1) return true;
  return false;
}

bool CNumber::operator > (const CNumber & rhs) const
{
  if (compare(rhs) == 1) return true;
  return false;
}

bool CNumber::operator >= (const CNumber & rhs) const
{
  if (compare(rhs) != -1) return true;
  return false;
}

void CNumber::pushToStack (std::queue<std::shared_ptr<CMathObject>> & queue,
                             std::stack<CNumber> & stack) const
{
  stack.push(*this);
  queue.pop();
}

void CNumber::print (std::ostream & os) const
{
  if (m_Negative)
    os << "-";

  if ((int) m_Digits.size() != m_DecimalBlocks)
  {
    os << m_Digits.back();
    for (int i = (int) m_Digits.size()-2; i >= m_DecimalBlocks; i--)
      os << std::setw(BLOCK_SIZE) << std::setfill('0') << m_Digits[i];
  }
  else
    os << '0';
  
  if (m_DecimalBlocks > 0)
  {
    os << '.';
    for (int i = m_DecimalBlocks - 1; i > 0; i--)
      os << std::setw(BLOCK_SIZE) << std::setfill('0') << m_Digits[i];

    // number of trailing zeros in the last block, when printing reduce the width
    // of the last block by this coefficient - i.e. block 0350 (stored as 350) will be printed as "035"
    int trailingZeros = (BLOCK_SIZE - m_DecimalPlaces % BLOCK_SIZE) % BLOCK_SIZE;
    int last = m_Digits[0] / pow(10, trailingZeros);
    os << std::setw(BLOCK_SIZE - trailingZeros) << std::setfill('0') << last;
  }
}
