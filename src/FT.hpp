#ifndef FT_HPP
#define FT_HPP

#include "Field.hpp"
#include <iostream>
#include <vector>
#include <cassert>


// Plain Fourier Transformation without Fast Optimizations:
template<typename F>
class FT {
  bool extend_with_zeros = 1;
public:
  const F zero = Field<F>::zero;
  const F one = Field<F>::one;
  F phi;
  Int lenExp = 3;
  Int len = get_len(lenExp);
  std::vector<F> xs = std::vector<F>(len, one);

  FT(Int lenExp): lenExp(lenExp) { }
  FT(std::vector<F> xs, bool extend2n): extend_with_zeros(extend2n) {
    set_xs(xs);
    if (extend_with_zeros) {
      extend_xs();
    }
  }
  FT(std::vector<F> xs ): FT(xs, true) {
  }

  void set_xs(std::vector<F> &_xs) {
    xs = _xs;
    len = xs.size();
    phi = Field<F>::get_phi(len);
  }

  // Length of input xs should be a power of 2 
  void extend_xs() {
    for (lenExp = 0, len = 1; len < xs.size(); len <<= 1 && ++lenExp) {
      assert(lenExp < IntMaxExponent);
    }
    while (xs.size() < len) {
      xs.push_back(zero);
    }
    phi = Field<F>::get_phi(len);
  }

  void print(std::string title = "") {
    using namespace std;
    cout<<"       ==== "<<title<<" ===="<<endl;
    for (auto &e : xs) {
      cout<<e<<"  ";
    }
    cout<<endl;
  }

  virtual std::vector<F> trans(bool rev = false) const {
    using namespace std;
    F phi_s = one;
    F denum = rev ? Field<F>::one2n(len) : one;
    vector<F> result;
    for (Int s = 0; s < len; ++s) {
      F sum = zero;
      F phi_st = one;
      for (Int t = 0; t < len; ++t) {
	sum = sum + phi_st * xs[t];
	phi_st = phi_st * phi_s;
      }
      if (rev) {
	phi_s = phi_s / phi;
      }
      else {
	phi_s = phi_s * phi;
      }
      result.push_back(sum / denum);
    }
    return (result);
  }
};

#endif
