#ifndef DEFINTEGER_HPP
#define DEFINTEGER_HPP

#include <cassert>

typedef long long Int;
const Int IntMax = (Int(1)<<(8 * sizeof(Int) - 2));
const Int IntMaxExponent = sizeof(Int) * 8 - 1;

Int get_len(Int k) {
  assert(k <= IntMaxExponent);
  return Int(1) << k;
}
  
#endif
