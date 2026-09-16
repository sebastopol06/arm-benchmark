#include <arm_neon.h>

struct Complex {
    float re;
    float im;
};

__attribute__((noinline))
void mrc4_neon(
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
    asm volatile("# LLVM-MCA-BEGIN mrc4_neon");

    // Load 4 complex samples from each antenna.
    // vld2q de-interleaves array of structure {re,im} directly into:
    //   val[0] = {re0,re1,re2,re3}
    //   val[1] = {im0,im1,im2,im3}
    const float32x4x2_t r0 = vld2q_f32(reinterpret_cast<const float*>(rx0));
    const float32x4x2_t r1 = vld2q_f32(reinterpret_cast<const float*>(rx1));
    const float32x4x2_t r2 = vld2q_f32(reinterpret_cast<const float*>(rx2));
    const float32x4x2_t r3 = vld2q_f32(reinterpret_cast<const float*>(rx3));

    const float32x4x2_t c0 = vld2q_f32(reinterpret_cast<const float*>(h0));
    const float32x4x2_t c1 = vld2q_f32(reinterpret_cast<const float*>(h1));
    const float32x4x2_t c2 = vld2q_f32(reinterpret_cast<const float*>(h2));
    const float32x4x2_t c3 = vld2q_f32(reinterpret_cast<const float*>(h3));

    // conj(h) * r
    float32x4_t acc_re = vmulq_f32(c0.val[0], r0.val[0]);
    acc_re = vfmaq_f32(acc_re, c0.val[1], r0.val[1]);

    float32x4_t acc_im = vmulq_f32(c0.val[0], r0.val[1]);
    acc_im = vfmsq_f32(acc_im, c0.val[1], r0.val[0]);

    acc_re = vfmaq_f32(acc_re, c1.val[0], r1.val[0]);
    acc_re = vfmaq_f32(acc_re, c1.val[1], r1.val[1]);

    acc_im = vfmaq_f32(acc_im, c1.val[0], r1.val[1]);
    acc_im = vfmsq_f32(acc_im, c1.val[1], r1.val[0]);

    acc_re = vfmaq_f32(acc_re, c2.val[0], r2.val[0]);
    acc_re = vfmaq_f32(acc_re, c2.val[1], r2.val[1]);

    acc_im = vfmaq_f32(acc_im, c2.val[0], r2.val[1]);
    acc_im = vfmsq_f32(acc_im, c2.val[1], r2.val[0]);

    acc_re = vfmaq_f32(acc_re, c3.val[0], r3.val[0]);
    acc_re = vfmaq_f32(acc_re, c3.val[1], r3.val[1]);

    acc_im = vfmaq_f32(acc_im, c3.val[0], r3.val[1]);
    acc_im = vfmsq_f32(acc_im, c3.val[1], r3.val[0]);

    // Re-interleave {re,im} for Complex array of structure output.
    float32x4x2_t result;
    result.val[0] = acc_re;
    result.val[1] = acc_im;

    vst2q_f32(reinterpret_cast<float*>(out), result);

    asm volatile("# LLVM-MCA-END mrc4_neon");
}