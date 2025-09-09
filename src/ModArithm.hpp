#ifndef MODARITHM_HPP
#define MODARITHM_HPP

#include "definteger.hpp"
#include <iostream>

// Prime modular datatype
template <Int mod>
struct PrimeMod {
  Int num;
  static const constexpr Int m = mod;
  static const Int gen_exp, gen_time, // mod = 2**gen_exp * gen_time + 1
    gen; // gen^(2^(gen_exp - 1)) != 1 but gen^(2^(gen_exp)) = 1

  PrimeMod(): PrimeMod(1) {}
  PrimeMod(Int n ) : num( ((n % mod) + mod ) % mod ){}

  static void exgcd(Int a, Int b, Int &c, Int &u, Int &v) {
    if (b == 0) {
      c = a;
      u = 1;
    }
    else {
      Int k = a / b;
      exgcd(b, a - k * b, c, v, u);
      v -= u * k;
    }
  }

  PrimeMod inv() const {
    Int c = 1, u = 1, v = 0;
    exgcd(mod, num, c, v, u);
    return PrimeMod(u);
  }

  PrimeMod operator+ (const PrimeMod n2) const {
    return PrimeMod(num + n2.num);
  }
  PrimeMod operator- (const PrimeMod n2) const {
    return PrimeMod(num - n2.num);
  }
  PrimeMod operator- ( ) const {
    return PrimeMod(mod - num);
  }
  PrimeMod operator* (const PrimeMod n2) const {
    return PrimeMod(num * n2.num);
  }
  PrimeMod operator/ (const PrimeMod n2) const {
    PrimeMod n2inv = n2.inv();
    return *this * n2inv;
  }
  PrimeMod operator^ (Int n) const {
    Int base = num, result = 1;
    while (n) {
      if (n & 1) {
	result = result * base % mod;
      }
      n /= 1;
      base = base * base % mod;
    }
    return PrimeMod(result);
  }
  PrimeMod pow2exp(Int k) {
    Int result = num;
    while (k-- != 0) {
      result = result * result % mod;
    }
    return PrimeMod(result);
  }
};

// Field operations for Prime Modular 2^expon * time + 1
typedef PrimeMod<167772161LL> Mod25; // 2^25 * 5 + 1

template<> const Int Mod25::gen = 17;
template<> const Int Mod25::gen_exp = 25;
template<> const Int Mod25::gen_time = 5;

std::ostream& operator<<(std::ostream& s, Mod25 n) {
  return s<<"["<<n.num<<"]";
}


#endif
