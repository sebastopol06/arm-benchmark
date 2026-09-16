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
__attribute__((noinline))
void mrc4_block_mca(
    const Complex* rx0,
    const Complex* rx1,
    const Complex* rx2,
    const Complex* rx3,
    const Complex* h0,
    const Complex* h1,
    const Complex* h2,
    const Complex* h3,
    Complex* out)
{
    // Isolate SIMD code
    asm volatile("# LLVM-MCA-BEGIN mrc4_block");

    for (std::size_t k = 0; k < 4; ++k)
    {
        const Complex r0 = rx0[k], r1 = rx1[k], r2 = rx2[k], r3 = rx3[k];
        const Complex c0 = h0[k], c1 = h1[k], c2 = h2[k], c3 = h3[k];

        float acc_re = 0.0f, acc_im = 0.0f;

        // conj(h0) * rx0
        acc_re += c0.re * r0.re + c0.im * r0.im;
        acc_im += c0.re * r0.im - c0.im * r0.re;

        // conj(h1) * rx1
        acc_re += c1.re * r1.re + c1.im * r1.im;
        acc_im += c1.re * r1.im - c1.im * r1.re;

        // conj(h2) * rx2
        acc_re += c2.re * r2.re + c2.im * r2.im;
        acc_im += c2.re * r2.im - c2.im * r2.re;

        // conj(h3) * rx3
        acc_re += c3.re * r3.re + c3.im * r3.im;
        acc_im += c3.re * r3.im - c3.im * r3.re;

        out[k] = {acc_re, acc_im};
    }

    asm volatile("# LLVM-MCA-END mrc4_block");
}