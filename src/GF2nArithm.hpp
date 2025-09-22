#ifndef GALOIS2N_HPP
#define GALOIS2N_HPP

#include "definteger.hpp"
#include <iostream>

namespace g2arithm {
// Polynomial on GF2 represented by an integer as 0-1 sequence
// 
// Note: The lower the G2 polynomial's order, the smaller the Int number.
//       if Order(a) > order(b) <=> a>b && a^b > b;  (^ stands for bitwise xor)
//       meanwhile if order(a) == order(b) <=> order(a^b) < order(b);
// Node: Both + and - for GF2 polynomials are bitwise XOR


// Polynomial long divisions on Galois 2 field:
// @target: q, r where a = qb + r, order(r) < order(b)
  void g2longdiv(Int a, Int b, Int &q, Int &r) {
    q = 0;
    r = a;
    if (a < 0 || b <= 0) {
      std::cerr << std::string("What sort of polynomials are given ???\n");
      return;
    }

    Int b1 = b;
    while (b1 < a ) {
      Int b1m = b1 << 1;
      if (b1m > b1)
	b1 = b1m;
      else
	break;
    }

    while ( b1 >= b) {
      q <<= 1;
      // q is even, and a = q * b1 + r,
      //  where order(r) <= order(b1).
      // The above = holds iff. r ^ b1 < r;
      Int r1 = r ^ b1;
      if (r1 < r) {
        r = r1;    // r <<- r + b1
        q = q | 1; // q <<- q - 1
      } 
      // a = q * b1 + r remains true,
      // while r is conditionally shrinked
      // so that order(r) < order(b1) is now satisfied.
      b1 >>= 1;
    }
  }

  Int g2mul(Int a, Int b) {
    Int result = 0;
    // return: a * b + result
    for (; b > 0; (b >>= 1) && (a <<= 1)) {
      if (b & 1)
        result ^= a;
    }
    return result;
  }

  // Polynomials a(x) * b(x) (mod m(x)) in Galois-2 field:
  Int g2modmul(Int a, Int b, Int m) {
    assert(0 <= a && (a ^ m) > a);
    assert(0 <= b && (b ^ m) > b);

    if (a < b) {
      std::swap(a, b);
    }
    
    Int result = 0; // a * b + result (mod m)
    auto modstep= [&](Int &poly) -> bool {
      if ((poly^ m) < poly) {
        poly ^= m;
	return 1;
      }
      return 0;
    };
    while (b) {
      if (b & 1) {
        result ^= a;
	modstep(result);
      }
      (b >>= 1) && (a <<= 1) && modstep(a);
      // $ a * b + result (mod m) $ remains unchanged...
    }
    return result;
  }

  Int g2modpow(Int b, Int e, Int m) {
    Int result = 1;
    while (e) {
      if (e & 1) {
	result = g2modmul(result, b, m);
      }
      e /= 2;
      b = g2modmul(b, b, m);
    }
    return result;
  }

  void exgcd(Int p1, Int p2, Int &r, Int &u1, Int &u2) {
    if (p2 == 0) {
      r = p1;
      u1 = 1;
    }
    else {
      Int k = 0, p1r = p1;
      g2longdiv(p1, p2, k, p1r);
      exgcd(p2, p1r, r, u2, u1);
      // u1 * (p1 - k * p2) + u2 * p2 = r
      u2 ^= g2mul(u1, k);
    }
  }

  template <Int od> struct GF2n {
    static const constexpr Int order = od;
    static const Int modmask;
    static const constexpr Int size = Int(1) << order;
    static const GF2n gen;

    // a polynomial with binary associates represented as an integer:
    Int plnm;
    GF2n(Int n) {
      Int k;
      g2longdiv(n, modmask, k, plnm);
    }
    GF2n() : GF2n(0) {}

    GF2n operator+(const GF2n f1) const {
      return GF2n(plnm ^ f1.plnm);
    }

    GF2n operator-(const GF2n f1) const {
      return GF2n(plnm ^ f1.plnm);
    }

    GF2n operator*(const GF2n f1) const {
      return g2modmul(plnm, f1.plnm, modmask);
    }
    GF2n power(const Int e) const {
      Int result = g2modpow(plnm, e, modmask);
      return GF2n(result);
    }

    GF2n reci() const {
      Int r, u1 = 1, u2 = 0;
      exgcd(plnm, modmask, r, u1, u2);
      return GF2n(u1);
    }

    GF2n operator/(const GF2n f1) const {
      return *this * f1.reci();
    }

    std::string bistr() {
      char outcome[order];
      Int mask = 1;
      char *c = outcome + (order - 1);
      for (; c >= outcome; --c) {
	*c = '0' + bool(plnm & mask);
	mask <<= 1;
      }
      return "P(" + std::string(outcome, order) + ")";
    }

    std::string hdstr() {
      const char hdmarks[17] = "0123456789ABCDEF";
      Int len = (order + 3) / 4 + 1;
      char result[len];
      Int paras = this->plnm;
      result[len - 1] = '\0';
      for (int i = len - 2; i >= 0; i--) {
	result[i] = hdmarks[paras & 15];
	paras >>= 4;
      }
      return std::string(result);
    }

    static void test() {
      using namespace std;

      cout << "  Hello, Field of GF(2^" << order << ")\n";

      cout<<"\n * Test the cyclic multiply group\n";
      for (int i = 0; i <= size; ++i) {
        GF2n p = gen.power(i);
        cout << " i = " << i << " \t gen^i = " << p.plnm << " = \t"
             << p.bistr() << endl;
	if (p.plnm == 1 && i > 0) {
          cout << "cyclic group found with order: " << i << endl;
          break;
	}
      }

      cout<<"\n * Find and verify polynomial reciprocals\n";
      for (int i = 1; i < size; i++) {
        GF2n p1(i), p2 = p1.reci();
        cout << p1.hdstr() << " * " << p2.hdstr() << "  = \t"
             << (p1 * p2).hdstr() << endl;
      }

      cout << "\n * Verify that a^2 + b^2 = (a+b)^2\n";
      cout << "\n    Define Polynomials a and b as integers: ";
      Int a, b;
      cin >> a >> b;
      GF2n pa(a), pb(b);
      auto show = [](GF2n x, string name) {
        cout << " " << name + " = " << x.bistr() << " \n";
      };
      show(pa, "pa");
      show(pb, "pb");
      show(pa.power(2), "pa^2    \t");
      show(pb * pb, "pb^2    \t");
      show(pa + pb, "pa+pb   \t");
      show((pa + pb) * (pa + pb), "(pa + pb)^2\t");
      show(pa * pa + pb * pb, "pa^2 + pb^2 \t");
    }
  };

  std::ostream& operator<<(std::ostream& s, GF2n<8> poly) {
    return s << "[" << poly.hdstr() << "]";
  }

  template <> const Int GF2n<8>::modmask = 319;
  template <> const GF2n<8> GF2n<8>::gen = 47;

 
}

typedef g2arithm::GF2n<8> GP256;

#endif
