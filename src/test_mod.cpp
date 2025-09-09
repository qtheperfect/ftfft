#include "FFT_Mod.hpp"

template<> std::vector<Mod25> FFT<Mod25>::testInput = {2, 3, -55, 707, 89, 114, 503, -4, 153, 9, 6};

int main() {
  std::cout<<"Test of FT and Fast-FT on modular field\n   mod = 167772161 = 2^25 * 5 + 1,\n   phi = 17"<<std::endl;
  FFT<Mod25>::test();
}
