#include <cstddef>
#include <arm_sme.h>

struct Complex {
    float re;
    float im;
};

__attribute__((noinline))
__arm_locally_streaming
void mrc4_sme(
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
    const float* r[4] = { reinterpret_cast<const float*>(rx0), reinterpret_cast<const float*>(rx1), reinterpret_cast<const float*>(rx2), reinterpret_cast<const float*>(rx3) };
    const float* h[4] = { reinterpret_cast<const float*>(h0), reinterpret_cast<const float*>(h1), reinterpret_cast<const float*>(h2), reinterpret_cast<const float*>(h3) };

    float* y = reinterpret_cast<float*>(out);

    // Number of FP32 elements, two per complex sample.
    const std::size_t nf = 2 * n;

    asm volatile("# LLVM-MCA-BEGIN mrc4_sme");

    for (std::size_t i = 0; i < nf; i += svcntw())
    {
        const svbool_t pg = svwhilelt_b32(i, nf);

        svfloat32_t acc = svdup_f32(0.0f);

        for (int a = 0; a < 4; ++a)
        {
            // Native complex AoS representation:
            //
            // [re0 im0 re1 im1 ...]
            //
            // Streaming SVE vectors are used directly.
            const svfloat32_t rv =
                svld1_f32(pg, r[a] + i);

            const svfloat32_t hv =
                svld1_f32(pg, h[a] + i);

            // acc += conj(h) * r
            acc = svcmla_f32_x(pg, acc, hv, rv, 0);
            acc = svcmla_f32_x(pg, acc, hv, rv, 270);
        }

        svst1_f32(pg, y + i, acc);
    }

    asm volatile("# LLVM-MCA-END mrc4_sme");
}