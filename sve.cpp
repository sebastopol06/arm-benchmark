#include <cstddef>
#include <arm_sve.h>

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
    Complex* __restrict out,
    std::size_t n)
{
    asm volatile("# LLVM-MCA-BEGIN mrc4_sve");

    const float* r[4] = { reinterpret_cast<const float*>(rx0), reinterpret_cast<const float*>(rx1), reinterpret_cast<const float*>(rx2), reinterpret_cast<const float*>(rx3) };
    const float* h[4] = { reinterpret_cast<const float*>(h0), reinterpret_cast<const float*>(h1), reinterpret_cast<const float*>(h2), reinterpret_cast<const float*>(h3) };

    float* y = reinterpret_cast<float*>(out);

    // Byte offsets for Complex elements:
    // 0, 8, 16, 24, ...
    const svuint32_t offsets = svindex_u32(0, sizeof(Complex));

    for (std::size_t k = 0; k < n; )
    {
        // Number of complex samples fitting in one SVE vector.
        const std::size_t vl = svcntw();

        // One predicate lane per complex sample.
        const svbool_t pg = svwhilelt_b32(k, n);

        svfloat32_t acc_re = svdup_f32(0.0f);
        svfloat32_t acc_im = svdup_f32(0.0f);

        for (int a = 0; a < 4; ++a)
        {
            const float* rp = r[a] + 2 * k;
            const float* hp = h[a] + 2 * k;

            // Gather:
            // rr = re[k], re[k+1], ...
            // ri = im[k], im[k+1], ...
            const svfloat32_t rr = svld1_gather_u32offset_f32(pg, rp    , offsets);
            const svfloat32_t ri = svld1_gather_u32offset_f32(pg, rp + 1, offsets);
            const svfloat32_t hr = svld1_gather_u32offset_f32(pg, hp    , offsets);
            const svfloat32_t hi = svld1_gather_u32offset_f32(pg, hp + 1, offsets);

            // conj(h) * r
            // real = hr*rr + hi*ri
            // imag = hr*ri - hi*rr
            acc_re = svmla_f32_m(pg, acc_re, hr, rr);
            acc_re = svmla_f32_m(pg, acc_re, hi, ri);
            acc_im = svmla_f32_m(pg, acc_im, hr, ri);
            acc_im = svmls_f32_m(pg, acc_im, hi, rr);
        }

        float* yp = y + 2 * k;
        
        svst1_scatter_u32offset_f32(pg, yp    , offsets, acc_re);
        svst1_scatter_u32offset_f32(pg, yp + 1, offsets, acc_im);

        k += vl;
    }

    asm volatile("# LLVM-MCA-END mrc4_sve");
}