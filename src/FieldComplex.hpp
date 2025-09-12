#ifndef FIELDCOMPLEX_HPP
#define FIELDCOMPLEX_HPP

#include "Field.hpp"
#include <complex>

typedef std::complex<double> c64;
//  complex field 
template<> const constexpr c64 Field<c64>::zero(0., 0.);
template<> const constexpr c64 Field<c64>::one(1., 0.);
template<> const constexpr Int Field<c64>::Len_Limit = IntMax;


template<> c64 Field<c64>::get_phi(Int len) {
  assert(len < Len_Limit);
  double ang = -M_PI * 2 / len;
  c64 phi(cos(ang), sin(ang));
  return phi;
}

template<> c64 Field<c64>::lenSqrt(Int len) {
  return c64(sqrt(len));
}




#endif
