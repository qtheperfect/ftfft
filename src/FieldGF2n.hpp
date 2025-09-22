#include "Galois2n.hpp"
#include "Field.hpp"

typedef g2arithm::GF2n<8> GF256;
using g2arithm::operator<<;

template<> const GF256 Field<GF256>::one = GF256(1);
template <> const GF256 Field<GF256>::zero = GF256(0);
template <> const Int Field<GF256>::Len_Limit = 255;

template <> GF256 Field<GF256>::get_phi(Int n) {
  assert(255 % n == 0); // 17 * 5 * 3 = 255
  return GF256::gen.power(255 / n);
}
