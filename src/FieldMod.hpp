#ifndef FIELDMOD_HPP
#define FIELDMOD_HPP

#include "Field.hpp"
#include "ModArithm.hpp"

template<> const Mod25 Field<Mod25>::one = Mod25(1);
template<> const Mod25 Field<Mod25>::zero= Mod25(0);

template<> Mod25 Field<Mod25>::get_phi(Int len) {
  Int expon = (1LL << Mod25::gen_exp) / len;
  Int result = 1, base = Mod25::gen; 
  while (expon) {
    if (expon % 2) {
      result = result * base % Mod25::m;
    }
    expon /= 2;
    base = base * base % Mod25::m;
  }
  return result;
}

template<> Mod25 Field<Mod25>::lenSqrt(Int len) {
  Int result = 1;
  while (len > 1) {
    len >>= 2;
    result <<= 1;
  }
  return Mod25(result);
}




#endif
