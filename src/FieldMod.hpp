#ifndef FIELDMOD_HPP
#define FIELDMOD_HPP

#include "Field.hpp"
#include "ModArithm.hpp"

// 2^25 * 5 + 1
const Int Prime2power = 167772161LL; 

// Field operations for Prime Modular 2^expon * time + 1
typedef PrimeMod<Prime2power> Mod25; 

template<> const Mod25 Mod25::gen = 17;
template<> const Int Mod25::gen_exp = 25;
template<> const Int Mod25::gen_time = 5;
template<> const Int Field<Mod25>::Len_Limit = 1 << 25;


template<> const Mod25 Field<Mod25>::one = Mod25(1);
template<> const Mod25 Field<Mod25>::zero= Mod25(0);


//template<Int Prime2power>
template<>
PrimeMod<Prime2power> Field<PrimeMod<Prime2power>>::get_phi(Int len) {
  assert(len < Len_Limit);
  typedef PrimeMod<Prime2power> ModNum;
  Int expon = (1LL << ModNum::gen_exp) / len;
  ModNum result = ModNum::gen ^ expon; 
  //std::cout<<" phi = "<<result<<std::endl;
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
