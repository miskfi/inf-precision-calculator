#include "CMathObject.h"

CMathObject::CMathObject () {}

CMathObject::~CMathObject () {}

std::ostream & operator << (std::ostream & os, const CMathObject & o)
{
  o.print(os);
  return os;
}