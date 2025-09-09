#ifndef FFT_HPP
#define FFT_HPP

#include "FT.hpp"

template <typename F>
class FFT : public FT<F> {
public:
  using FT<F>::xs;
  using FT<F>::len;
  using FT<F>::phi;
  using FT<F>::lenExp;
  using FT<F>::print;

  FFT(int lenExp): FT<F>(lenExp){}
  FFT(std::vector<F> xs): FT<F>(xs){};
  FFT(const FT<F>& ft): FFT(ft.xs){};
  static void branchSum(F* start, Int step, Int length, F phiPow, F* result, F* cache) {
    if (length == 1) {
      *result = *start;
      return;
    }
    else if (length == 0) {
      return;
    }
    else {
      F *cache1 = cache, *cache2 = cache + (length / 2);
      branchSum(start, step + step, length/2, phiPow * phiPow, cache1, result);
      branchSum(start + step, step + step, length/2, phiPow * phiPow, cache2, result);
      F phi = Field<F>::one;
      for (Int s = 0; s < length / 2; ++s) {
	result[s] = cache1[s] + phi * cache2[s];
	result[s + length / 2] = cache1[s] - phi * cache2[s];
	phi = phi * phiPow;
      }
    }
  }
  std::vector<F> trans(bool rev = false) const {
    using namespace std;

    F source[len], result[len], cache[len];
    F denom = rev ? len : Field<F>::one;
    copy(xs.begin(), xs.end(), source);
    F phi = rev? Field<F>::one / this->phi : this->phi;
    branchSum(source, 1, len, phi, result, cache);
    std::vector<F> outcome(len);
    for (Int t = 0; t < len; ++t) {
      outcome[t] = (result[t] / denom);
    }
    return outcome;
  }

  static std::vector<F> testInput;
  static void test() {
    using namespace std;

    printf("Hello, fft\n");
    cout<<" Length Limit: "<<IntMax<<endl;

    FT<F> xs(testInput);
    FFT<F> xsf(testInput);
    xs.print("Original Inputs for FT");
    xsf.print("Original Inputs for Fast FT");

    FT<F> ys = xs.trans();
    FFT<F> ysf = xsf.trans();
    ys.print("y[s] from FT");
    ysf.print("y[s] from Fast FT");

    FT<F> xs1 = ys.trans(true);
    FFT<F> xsf1 = ysf.trans(true);
    xs1.print("The original recovered from the FT");
    xsf1.print("The original recovered from the Fast FT");

  }
};


#endif
