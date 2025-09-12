#include "FFT_Mod.hpp"
#include <fstream>

// template<> std::vector<Mod25> FFT<Mod25>::testInput = {2, 3, -55, 707, 89, 114, 503, -4, 153, 9, 6};

void load_test() {
  using namespace std;
  string filename = "project/resources/input_mod25.txt";
  ifstream reader(filename);
  if (reader.is_open()) {
    FFT<Mod25>::testInput.clear();
    Int x;
    try {
      while (reader >> x) {
	FFT<Mod25>::testInput.push_back(Mod25(x));
      }
    }
    catch (exception e) {
      cout<<"Error during data reading";
    }
    reader.close();
  }
  else {
    cout<<"No data file is open!"<<endl;
  }
}

int main() {
  std::cout<<"Test of FT and Fast-FT on modular field\n   mod = 167772161 = 2^25 * 5 + 1,\n   phi = 17"<<std::endl;
  load_test();
  FFT<Mod25>::test();
}
