#ifndef FIELD_HPP
#define FIELD_HPP
#include "definteger.hpp"
#include <iostream>

template <class F> class FT;
template <class F> class FFT;


// General Field 
template <typename F>
class Field {
  friend class FT<F>;
  friend class FFT<F>;
public:
  const static F zero;
  const static F one;
  const static Int Len_Limit;

  static F get_phi(Int len); 
  static F lenSqrt(Int len);

  static F one2n(Int n) {
    F base = one, result = zero;
    while (n) {
      if (n % 2 == 1) {
	result = result + base;
      }
      n /= 2;
      base = base + base;
    }
    return result;
  }

  static void testField() {
    using namespace std;
    Int len = 16;
    cout<<"sqrt(len) = \t"<<lenSqrt(len)<<endl;
    F phi = get_phi(len), t = one, sum = zero;
    for (int i = 0; i <= len; ++i) {
      sum = sum + t;
      cout<<"sum = "<<sum<<", \tt = "<<t<<endl;
      t = t * phi;
    }
    cout<<"1/phi = "<<one / phi<<endl;
    cout<<"1/phi * phi = "<<one / phi * phi <<endl;
  }
};
  
#endif
