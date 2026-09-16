#include <arm_sve.h>
#include <cstddef>

struct Complex {
    float re;
    float im;
};

__attribute__((noinline))
void mrc4_sve(
    const Complex* __restrict rx0,
    const Complex* __restrict rx1,
    const Complex* __restrict rx2,
    const Complex* __restrict rx3,
    const Complex* __restrict h0,
    const Complex* __restrict h1,
    const Complex* __restrict h2,
    const Complex* __restrict h3,
    Complex* __restrict out)
{
    asm volatile("# LLVM-MCA-BEGIN mrc4_sve");

    const svbool_t pg = svwhilelt_b32(static_cast<std::size_t>(0), static_cast<std::size_t>(4));
    const svuint32_t offsets = svindex_u32(0, sizeof(Complex));

    svfloat32_t acc_re = svdup_f32(0.0f);
    svfloat32_t acc_im = svdup_f32(0.0f);

    const Complex* rx[4] = {rx0, rx1, rx2, rx3};
    const Complex* h[4]  = {h0, h1, h2, h3};

    for (int a = 0; a < 4; ++a)
    {
        const float* rp = reinterpret_cast<const float*>(rx[a]);
        const float* hp = reinterpret_cast<const float*>(h[a]);

        const svfloat32_t rr = svld1_gather_u32offset_f32(pg, rp    , offsets);
        const svfloat32_t ri = svld1_gather_u32offset_f32(pg, rp + 1, offsets);

        const svfloat32_t hr = svld1_gather_u32offset_f32(pg, hp, offsets);
        const svfloat32_t hi = svld1_gather_u32offset_f32(pg, hp + 1, offsets);

        acc_re = svmla_f32_m(pg, acc_re, hr, rr);
        acc_re = svmla_f32_m(pg, acc_re, hi, ri);

        acc_im = svmla_f32_m(pg, acc_im, hr, ri);
        acc_im = svmls_f32_m(pg, acc_im, hi, rr);
    }

    float* yp = reinterpret_cast<float*>(out);

    svst1_scatter_u32offset_f32(pg, yp    , offsets, acc_re);
    svst1_scatter_u32offset_f32(pg, yp + 1, offsets, acc_im);

    asm volatile("# LLVM-MCA-END mrc4_sve");
}