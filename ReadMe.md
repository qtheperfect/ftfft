
# Table of Contents

1.  [Introduction:](#org3189d91)
2.  [About the FFT](#orge31a373)
    1.  [Presumptions:](#org45611f0)
    2.  [The FFT Steps:](#org3a24fb0)
3.  [About the fields](#orgc86dbce)
    1.  [Fields contained in the program:](#orgd525564)
    2.  [Field properties coded in the C++ template singletons](#org5449518)
4.  [About](#org9196387)



<a id="org3189d91"></a>

# Introduction:

A C++ project to illustrate the Fourier Transforms(FT) and the Fast Fourier Transforms(FFT),
participated with the inverse transforms,
primarily on such common numeric fields as complex and prime-modular fields.


<a id="orge31a373"></a>

# About the FFT


<a id="org45611f0"></a>

## Presumptions:

-   Inputs: $ x = x(0), x(1) ... x(N - 1) $ **where $ N = 2^n $**
-   Outputs: $ y = y(0), y(1) ... y(N - 1) $
-   The cyclic generator of order	$ N $: $ \phi: \phi^N = 1 $ where in the complex field: $ \phi = \exp(-2\pi i / N) $. Since **in any field**: $$ 0 = \phi^N - 1 = (\phi^{\frac{N}{2}} + 1)(\phi^{\frac{N}{2}} - 1) $$ which proves that <span class="underline">$ \phi^{\frac{N}{2}} = -1 $</span>
-   Formula of the FT:
    $$ y = \Phi x $$, i.e.
    $$ y(s) = \sum_t \phi^{st} x(t) $$
-   The inverse FT:
    Note that the inverse transform matrice has a succint similar form:
    $$ x = \Phi^{-1}y $$, i.e.
    $$ x(t) = \frac{1}{N} \sum_t ({\phi}^{-1})^{st} y(t) $$.
    So the fast forward Fourior transform also applies to the inverse transform.


<a id="org3a24fb0"></a>

## The FFT Steps:

The original Fourier transform for the input $ x $ can be <span class="underline">split into the sum of the even and odd items</span>:
$$ y(s) = \sum_{\tau} \phi^{2\tau \cdot s}x(2\tau)  + \sum_{\tau} \phi^{(2\tau + 1) \cdot s} x(2\tau + 1)$$

When $ N $ is even, $ (\phi^2)^{N/2} = 1 $.
All the **even** items can make a partial Fourior transform ($ y_0 $), and the cyclic generator is $ \phi^2 $:
$$ y_0(s) = \sum_{\tau} \phi^{2\tau \cdot s} x(2\tau) $$

Likewisely, all the **odd** items makes a partial transform with the cyclic generator $ \phi^2 $:
$$ y_1(s) = \sum_{\tau} \phi^{2\tau \cdot s} x(2\tau + 1)$$

Then, when $ N $ is even, after the above two partial transforms already done, for any $ s < N/2 $:
$$ y(s) = y_0(s) + \phi^s y_1(s) $$
$$ y(s + \frac{N}{2}) = y_0(s) - \phi^s y_1(s)  $$

The complexity for the calculation of $ y $ is $ O(N) $ <span class="underline">rather than $ O(N^2) $</span>.

The partial transforms $ y_0(s) $ and $ y_1(s) $ can be calculated recursively in further steps, given that <span class="underline">$ N/2 $ is still even</span> before reaching $ 1 $.

The next recursive step returns $ y_0 $ and $ y_1 $, soj still should compute $ \frac{N}{2} + \frac{N}{2} = N $ items in total, so should all the further recursions.

Totally $ O(\log_2 N) $ recursive steps are required to get the final transform, so the total calculation is $ N\log_2N $, which still prevails $ O(N^2) $


<a id="orgc86dbce"></a>

# About the fields


<a id="orgd525564"></a>

## Fields contained in the program:

-   Complex field: The cyclic generator is $ \phi = \exp(-2\pi i / N) $.
-   Prime Modular Field: When $ p $ is prime, its modular field is finite and of size $ p - 1 $.
    If $ p = q \cdot 2^k + 1 $, the field will have a cyclic sub-group of size $ 2^k $.
    We set $ p = 5 \cdot 2^{25} + 1 $, for which $ 17 $ is a cyclic generator of order $ 2^{15} $.


<a id="org5449518"></a>

## Field properties coded in the C++ template singletons

Assuming that the field is presented by the C++ datatype `F`, The `Field<F>` privides basic field properties:

    static F Field<F>::one;  // 1+0i, if F is complex field.
    static F Field<F>::zero; // 0+0i, if F is complex field.
    
     // Returns the len-th-order cyclic generator. len should be a power of 2 
    static F Field<F>::get_phi(Int len); 

The data `F` should be applicated with operators: `+, -, *, /, ostream<<`

Transform classes, i/o-puts, test data and functions:

    class FT<F> { // Plain Fourier transformaitons
      vector<F> xs; // Inputs
      vector<F> ys; // Outputs
      void trans(); // Fill the outputs
    };
    
    class FFT<F> : public FT<F> { // Fast FT
      void trans(); // overrides FT::trans
      // which requires the recursive function below, 
      // getting the partial sum of input xs from `start` by `step` to some `length`, transformed with the Fourier parameter `phiPow`.
      // Before writing the result to `result`, the outcome of further recursions are restored in `cache` first. 
      static void branchSum(F* start, Int step, Int length, F phiPow, F* result, F* cache);
      static vector<F> testInput; // Input used by the test()
      static void test();
    }


<a id="org9196387"></a>

# About

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<tbody>
<tr>
<td class="org-left">Author</td>
<td class="org-left">Linghuei Guo</td>
</tr>

<tr>
<td class="org-left">Affiliation</td>
<td class="org-left">Scl. of A.I. Henan Univ.</td>
</tr>

<tr>
<td class="org-left">Email</td>
<td class="org-left">guolh2013@hotmail.com</td>
</tr>

<tr>
<td class="org-left">PGP</td>
<td class="org-left">6819D81B0971C2C4</td>
</tr>

<tr>
<td class="org-left">Permission</td>
<td class="org-left">All Rights Reserved</td>
</tr>
</tbody>
</table>

