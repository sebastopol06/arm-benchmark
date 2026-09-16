#include <cstddef>

struct Complex {
    float re;
    float im;
};

// 4-Rx Maximum Ratio Combining
//
// out[k] = sum_a conj(h[a][k]) * rx[a][k]
//
// (a - jb)(c + jd)
//   real = ac + bd
//   imag = ad - bc
//
void mrc4_scalar(
    const Complex* __restrict rx0, // No aliasing between rx0, rx1, rx2, rx3, h0, h1, h2, h3, and out to protect data
    const Complex* __restrict rx1,
    const Complex* __restrict rx2,
    const Complex* __restrict rx3,
    const Complex* __restrict h0,
    const Complex* __restrict h1,
    const Complex* __restrict h2,
    const Complex* __restrict h3,
    Complex* __restrict out,
    std::size_t n)
{
    for (std::size_t k = 0; k < n; ++k) {
        float acc_re = 0.0f;
        float acc_im = 0.0f;

        const Complex r0 = rx0[k];
        const Complex r1 = rx1[k];
        const Complex r2 = rx2[k];
        const Complex r3 = rx3[k];

        const Complex c0 = h0[k];
        const Complex c1 = h1[k];
        const Complex c2 = h2[k];
        const Complex c3 = h3[k];

        acc_re += c0.re * r0.re + c0.im * r0.im;
        acc_im += c0.re * r0.im - c0.im * r0.re;

        acc_re += c1.re * r1.re + c1.im * r1.im;
        acc_im += c1.re * r1.im - c1.im * r1.re;

        acc_re += c2.re * r2.re + c2.im * r2.im;
        acc_im += c2.re * r2.im - c2.im * r2.re;

        acc_re += c3.re * r3.re + c3.im * r3.im;
        acc_im += c3.re * r3.im - c3.im * r3.re;

        out[k] = {acc_re, acc_im};
    }
}