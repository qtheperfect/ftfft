#ifndef GF2nFT_HPP
#define GF2nFT_HPP

#include "FT.hpp"
#include "Field.hpp"
#include "GF2nArithm.hpp"

template <> const GP256 Field<GP256>::one = GP256(1);
template <> const GP256 Field<GP256>::zero= GP256(0);
template <> const Int Field<GP256>::Len_Limit = 255;

template <> GP256 Field<GP256>::get_phi(Int n) {
  assert((n>1) && (255%n==0)); // 255 = 3 * 5 * 17
  return GP256::gen.power(255 / n);
}

void test_g2ft() {
  
  std::vector<GP256> xs = {
    12, 7, 1, 3, 13
  };

  FT<GP256> ft0(xs, false);
  FT<GP256> ft1(ft0.trans(), false);
  FT<GP256> ft10(ft1.trans(true), false);

  assert(ft0.phi.power(ft0.len).plnm == ft0.one.plnm);
  assert((ft1.phi.reci().power(ft1.len) + ft0.one).plnm == 0);
  
  ft0.print("Original FT input");
  ft1.print("GF2n  Transformed");
  ft10.print("GF2n Recovered");
}


#endif
