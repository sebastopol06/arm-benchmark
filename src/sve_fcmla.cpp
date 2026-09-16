#include <arm_sve.h>

struct Complex {
    float re;
    float im;
};

__attribute__((noinline))
void mrc4_sve_fcmla(
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
    asm volatile("# LLVM-MCA-BEGIN mrc4_sve_fcmla");

    const svbool_t pg = svptrue_b32();

    // 128-bit SVE = 4 x FP32 = 2 complex samples.
    // Two independent vectors process exactly 4 complex samples.
    svfloat32_t acc0 = svdup_f32(0.0f);
    svfloat32_t acc1 = svdup_f32(0.0f);

    // Antenna 0
    {
        const svfloat32_t r0a = svld1_f32(pg, reinterpret_cast<const float*>(rx0));
        const svfloat32_t h0a = svld1_f32(pg, reinterpret_cast<const float*>( h0));

        const svfloat32_t r0b = svld1_f32(pg, reinterpret_cast<const float*>(rx0 + 2));
        const svfloat32_t h0b = svld1_f32(pg, reinterpret_cast<const float*>( h0 + 2));

        acc0 = svcmla_f32_x(pg, acc0, h0a, r0a,   0);
        acc0 = svcmla_f32_x(pg, acc0, h0a, r0a, 270);

        acc1 = svcmla_f32_x(pg, acc1, h0b, r0b,   0);
        acc1 = svcmla_f32_x(pg, acc1, h0b, r0b, 270);
    }

    // Antenna 1
    {
        const svfloat32_t r1a = svld1_f32(pg, reinterpret_cast<const float*>(rx1));
        const svfloat32_t h1a = svld1_f32(pg, reinterpret_cast<const float*>( h1));

        const svfloat32_t r1b = svld1_f32(pg, reinterpret_cast<const float*>(rx1 + 2));
        const svfloat32_t h1b = svld1_f32(pg, reinterpret_cast<const float*>( h1 + 2));

        acc0 = svcmla_f32_x(pg, acc0, h1a, r1a,   0);
        acc0 = svcmla_f32_x(pg, acc0, h1a, r1a, 270);

        acc1 = svcmla_f32_x(pg, acc1, h1b, r1b,   0);
        acc1 = svcmla_f32_x(pg, acc1, h1b, r1b, 270);
    }

    // Antenna 2
    {
        const svfloat32_t r2a = svld1_f32(pg, reinterpret_cast<const float*>(rx2));
        const svfloat32_t h2a = svld1_f32(pg, reinterpret_cast<const float*>( h2));

        const svfloat32_t r2b = svld1_f32(pg, reinterpret_cast<const float*>(rx2 + 2));
        const svfloat32_t h2b = svld1_f32(pg, reinterpret_cast<const float*>( h2 + 2));

        acc0 = svcmla_f32_x(pg, acc0, h2a, r2a,   0);
        acc0 = svcmla_f32_x(pg, acc0, h2a, r2a, 270);

        acc1 = svcmla_f32_x(pg, acc1, h2b, r2b,   0);
        acc1 = svcmla_f32_x(pg, acc1, h2b, r2b, 270);
    }

    // Antenna 3
    {
        const svfloat32_t r3a = svld1_f32(pg, reinterpret_cast<const float*>(rx3));
        const svfloat32_t h3a = svld1_f32(pg, reinterpret_cast<const float*>( h3));

        const svfloat32_t r3b = svld1_f32(pg, reinterpret_cast<const float*>(rx3 + 2));
        const svfloat32_t h3b = svld1_f32(pg, reinterpret_cast<const float*>( h3 + 2));

        acc0 = svcmla_f32_x(pg, acc0, h3a, r3a,   0);
        acc0 = svcmla_f32_x(pg, acc0, h3a, r3a, 270);

        acc1 = svcmla_f32_x(pg, acc1, h3b, r3b,   0);
        acc1 = svcmla_f32_x(pg, acc1, h3b, r3b, 270);
    }

    svst1_f32(pg, reinterpret_cast<float*>(out    ), acc0);
    svst1_f32(pg, reinterpret_cast<float*>(out + 2), acc1);

    asm volatile("# LLVM-MCA-END mrc4_sve_fcmla");
}