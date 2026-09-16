# ARM Pipeline Exploration on Toy Example

Consider different ARM implementations of a 4-Rx Maximum Ratio Combining (MRC) on the CPU pipeline. Call it a kernel.

Consider Neoverse V2, modern ARMv9 core.

Consider Godbolt framework for fast prototyping.

Consider compilation target: AArch64 / Armv8-A.  

Consider uarchitecture model Arm Neoverse V2.

Consider compiler: Clang 23.1 (most recent available) and `-O3` optimization level, unless specified otherwise.

The present goal is to provide a genuine benchmark of the MRC implementation over the ARM uarchitecture extensions. Focus in particular on the SIMD, NEON, SVE models.

For benchmarking purpose, consider LLVM-MCA after isolation of the relevant piece of code. Based on that, produce some top level metrics for benchmarking purpose:
- Cycles per processed sample 
- Pipeline Usage Efficiency (PUE)
- Execution Density (ED)

## Kernel

For each complex input sample:
$$
y[k] = \sum_{a=0}^{3} \mathrm{conj}(h_a[k]) \cdot r_a[k]
$$

This is typical usecase for LTE-A MIMO receiver. This operation is performed for each RE, that could be (20MHz, FDD Transmission Scheme), 14 OFDM symbols, 1200 subcarriers per subframe (1ms), thus 16,800 MRC per ms, ~17e6 MRC per second. Definitely a candidate for massively repeated execution on a DSP.

## Methodology

To make LLVM-MCA results comparable, each benchmark processes exactly 4 complex output samples.

LLVM-MCA regions isolate the kernel:

```cpp
asm volatile("# LLVM-MCA-BEGIN mrc4_block");

// kernel

asm volatile("# LLVM-MCA-END mrc4_block");
```

Two initial builds are compared:

Naive Implementation aka Scalar
```text
-O3 -std=c++17 -mcpu=neoverse-v2 -fno-vectorize -fno-slp-vectorize 
```

SIMD (automatically enabled by compiler)
```text
-O3 -std=c++17 -mcpu=neoverse-v2
```

A first attempt was made leaving the complete variable-size MRC loop. However, the compiler-generated code contained both a vectorized main loop and a scalar remainder loop. Then LLVM-MCA analyzed both paths as part of the same code region. This made direct comparison misleading: the reported instruction count, total cycles and block throughput did not represent the same amount of useful work between the scalar and SIMD implementations. The benchmark was therefore reduced to a fixed block of 4 complex samples to match the width of a 128-bit NEON vector (`4 × float32`).

## Top-level Results

| Metric | v1 Scalar | v2 Auto-SIMD | v3 NEON | v4 SVE | v5 SME |
|---|---:|---:|---:|---:|---:|
| Instructions / 4 samples | 134 | 75 | 26 | TBD | TBD |
| µOps / 4 samples | 170 | 93 | 55 | TBD | TBD |
| Block RThroughput | 28.3 cycles | 16.0 cycles | 9.2 cycles | TBD | TBD |
| Cycles / sample | 7.08 | 4.00 | 2.30 | TBD | TBD |
| Speedup vs Scalar | 1.00× | 1.77× | 3.08× | TBD | TBD |
| IPC | 4.59 | 4.48 | 2.54 | TBD | TBD |
| PUE | TBD | TBD | TBD | TBD | TBD |
| ED | TBD | TBD | TBD | TBD | TBD |

TODO: Provide script for PUE, ED, based on log

### Top-Level Observation / Discussion

TBD

## Going More into the Details (Inside the Pipeline)

LLVM-MCA timeline helps in going beyond the above averaged metrics. See v*.log and consider notations:
```text
`D`  Dispatch
`=`  Wait before Execution
`e`  Execution Slot
`E`  Execution Completion
`-`  Wait before Retirement
`R`  Retired
```
Overview
| Timeline metric | v1 Scalar | v2 Auto-SIMD | v3 NEON | v4 SVE | v5 SME |
|---|---:|---:|---:|---:|---:|
| `e` | 492 | 206 | 134 | TBD | TBD |
| `=` | 562 | 443 | 187 | TBD | TBD |
| `-` | 482 | 225 | 45 | TBD | TBD |
| `=/e` | 53.3% | 68.3% | 58.3% | TBD | TBD |

### Pipeline comparison: Scalar (v1) vs Auto-SIMD (v2)

Interestingly, the auto-vectorized implementation is much faster overall, but shows a higher proportion of pre-execution waiting. That suggests some optimization question.

Highlight some LLVM-MCA timeline for discussion.

#### 1. Loads: same latency, more data

```asm
Scalar                           Auto-SIMD

DeeeeeeER  ldp s1, s2, [x0]      DeeeeeeER  ldp q3, q4, [x0]
```

Yet same execution latency (6 cycles), v2 deals with 128-bit vector registers and therefore moves more data per instruction. Thus increase in parallelism with no significant penalty in instruction latency.

#### 2. Scalar dependency chains

Typical sequence v1:

```asm
D====eeeE...       fmul   s25, s2, s18
D======eeeeE...    fmadd  s25, s17, s1, s25
...
D========eeE...    fadd   s25, s25, s0
D==========eeE...  fadd   s2, s25, s2
```

`=` cycles increases and shows instructions being dispatched but waiting before execution. Successive MAC and ADD operations introduce dependency and clip parallelism.

#### 3. SIMD computation introduces data rearrangement

v2 processes 4 `FLP32` with 1 instruction, 4 bytes each so 16 bytes (128 bits):

```asm
D=====eeE...          trn2  v2.4s, v0.4s, v0.4s
D======eeE...         trn1  v0.4s, v0.4s, v0.4s
...
D===========eeeE...   fmul  v1.4s, ...
D===========eeeeE...  fmla  v1.4s, ...
```

The `.4s` vector operations perform 4 FLP operations in a single operation (parallel), excellent. But see `trn2` / `trn1` that rearrange the interleaved real and imaginary components, this is a penalty induced by SIMD when dealing with `struct Complex { float re;  float im; };`. In memory the array of data is then interleaved `re0 im0 | re1 im1 | ...` and the compiler thinks it is mandatory de-interleave. Well, this could be handled differently to save this cost by preparing the data with proper layout or considering `re` and `im` are independent so their order does not matter. This later aspect is a special case and does not scale up.

#### 4. SIMD does not eliminate dependency chains

Towards the end of V2:

```asm
D============eeeeE-R     fmla  v1.4s, ...
D================eeER    fadd  v0.4s, v0.4s, v1.4s
...
D===========eeeeE--R     fmla  v1.4s, ...
D=================eeER   fadd  v0.4s, v0.4s, v1.4s
D====================eeER stp  q2, q0, [x8]
```

The auto-vectorized implementation performs substantially more useful work per instruction, but long pre-execution waits remain visible.

The final accumulation and store are still constrained by preceding results.

#### 5. TBD

TBD

### Scalar to SIMD to NEON to SVE to SME

| | v1 Scalar | v2 Auto-SIMD | v3 NEON | v4 SVE | v5 SME |
|---|---|---|
| Data parallelism | 1 × `FLP32` | 4 × `FLP32` |
| Arithmetic | Scalar FP | Vector FP |
| Instruction count | 134 | 75 |
| Data rearrangement | Minimal | `trn1` / `trn2` |
| Dependency chains | Significant | Still visible |
| Block RThroughput | 28.3 cycles | 16.0 cycles |
| Cycles / sample | 7.08 | 4.00 |

| | v1 Scalar | v2 Auto-SIMD | v3 NEON | v4 SVE | v5 SME |
|---|---|---|---|---|---|
| Data parallelism | 1 × `FLP32` | 4 × `FLP32` | 4 × `FLP32` | TBD | TBD |
| Arithmetic | Scalar | Vector | NEON | TBD | TBD |
| Instruction count | 134 | 75 | 26 | TBD | TBD |
| Data rearrangement | Minimal | `trn1` / `trn2` | `ld2` / `st2` | TBD | TBD |
| Dependency chains | Significant | Still visible | Still visible | TBD | TBD |
| Block RThroughput | 28.3 cycles | 16.0 cycles | 9.2 cycles | TBD | TBD |
| Cycles / sample | 7.08 | 4.00 | 2.30 | TBD | TBD |
| Speedup vs Scalar | 1.00× | 1.77× | 3.08× | TBD | TBD |

v1: many scalar operations and dependency chains.  
v2: parallel computation and fewer instructions, but data rearrangement and remaining dependencies.
v3: explicit NEON removes data rearrangement overhead. Some dependencies remain.
v4: TBD
v5: TBD