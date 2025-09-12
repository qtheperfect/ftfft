#include "FFT_C64.hpp"
#include <fstream>
#include <sstream>

void load_test() {
  using namespace std;
  string filename = "project/resources/input_complex.txt";
  ifstream reader(filename);
  if (reader.is_open()) {
    FFT<c64>::testInput.clear();
    double real, im;
    try {
      while (reader >> real && reader >> im) {
	FFT<c64>::testInput.push_back({real, im});
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
  load_test();
  FFT<c64>::test();
  return 0;
}
