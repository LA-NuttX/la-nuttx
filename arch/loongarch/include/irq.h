/****************************************************************************
 * arch/loongarch/include/irq.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/* This file should never be included directly but, rather, only indirectly
 * through nuttx/irq.h
 */

#ifndef __ARCH_LOONGARCH_INCLUDE_IRQ_H
#define __ARCH_LOONGARCH_INCLUDE_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/* Include chip-specific IRQ definitions (including IRQ numbers) */

#include <nuttx/config.h>

#include <sys/types.h>

#include <arch/csr.h>
#include <arch/chip/irq.h>
#include <arch/mode.h>

#include <assert.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifdef __ASSEMBLY__
#  define __STR(s)  s
#else
#  define __STR(s)  #s
#endif
#define __XSTR(s)   __STR(s)

/* Map LoongArch exception code to NuttX IRQ */

// /* IRQ 0-24 : exceptions */

#define LOONGARCH_XCPT_INT  (0)   /* Only when CSR.ECFG.VS=0, it means it is an INTerrupt */
#define LOONGARCH_XCPT_PIL  (1)   /* Page Invalid exception for Load operation */
#define LOONGARCH_XCPT_PIS  (2)   /* Page Invalid exception for Store operation */
#define LOONGARCH_XCPT_PIF  (3)   /* Page Invalid exception for Fetch operation */
#define LOONGARCH_XCPT_PME  (4)   /* Page Modification Exception */
#define LOONGARCH_XCPT_PNR  (5)   /* Page Non-Readable exception */
#define LOONGARCH_XCPT_PNX  (6)   /* Page Non-eXecutable exception */
#define LOONGARCH_XCPT_PPI  (7)   /* Page Privilege level Illegal exception */
#define LOONGARCH_XCPT_ADE  (8)   /* ADdress error Exception for Fetching/Memory access instructions */
#define LOONGARCH_XCPT_ALE  (9)   /* Address aLignment fault Exception */
#define LOONGARCH_XCPT_BCE  (10)  /* Bound Check Exception */
#define LOONGARCH_XCPT_SYS  (11)  /* SYStem call exception */
#define LOONGARCH_XCPT_BRK  (12)  /* BReaKpoint exception */
#define LOONGARCH_XCPT_INE  (13)  /* Instruction Non-defined Exception */
#define LOONGARCH_XCPT_IPE  (14)  /* Instruction Privilege error Exception */
#define LOONGARCH_XCPT_FPD  (15)  /* Floating-Point instruction Disable exception */
#define LOONGARCH_XCPT_SXD  (16)  /* 128-bit vector (SIMD instructions) eXpansion instruction Disable exception */
#define LOONGARCH_XCPT_ASXD (17)  /* 256-bit vector (Advanced SIMD instructions) eXpansion instruction Disable exception */
#define LOONGARCH_XCPT_FPE  (18)  /* (Vector) Floating-Point error Exception */
#define LOONGARCH_XCPT_WPE  (19)  /* WatchPoint Exception for Fetch/Memory load/Memory store watchpoint */
#define LOONGARCH_XCPT_BTD  (20)  /* Binary Translation expansion instruction Disable exception */
#define LOONGARCH_XCPT_BTE  (21)  /* Binary Translation related exceptions */
#define LOONGARCH_XCPT_GSPR (22)  /* Guest Sensitive Privileged Resource exception */
#define LOONGARCH_XCPT_HVC  (23)  /* HyperVisor Call exception */
#define LOONGARCH_XCPT_GCC  (24)  /* Guest CSR Software/Hardware Change exception */

#define LOONGARCH_MAX_EXCEPTION     (24)


/* IRQ 64- : interrupts(when CSR.ECFG.VS=0, the ecode for interrupts= 64+interrupt number) */
#define LOONGARCH_IRQ_BASE        (64)
#define LOONGARCH_IRQ_SOFT0       (LOONGARCH_IRQ_BASE + 0)    /* SoftWare Interrupt 0 */
#define LOONGARCH_IRQ_SOFT1       (LOONGARCH_IRQ_BASE + 1)    /* SoftWare Interrupt 1 */
#define LOONGARCH_IRQ_HWI0        (LOONGARCH_IRQ_BASE + 2)    /* HardWare Interrupt 0 */
#define LOONGARCH_IRQ_HWI1        (LOONGARCH_IRQ_BASE + 3)    /* HardWare Interrupt 1 */
#define LOONGARCH_IRQ_HWI2        (LOONGARCH_IRQ_BASE + 4)    /* HardWare Interrupt 2 */
#define LOONGARCH_IRQ_HWI3        (LOONGARCH_IRQ_BASE + 5)    /* HardWare Interrupt 3 */
#define LOONGARCH_IRQ_HWI4        (LOONGARCH_IRQ_BASE + 6)    /* HardWare Interrupt 4 */
#define LOONGARCH_IRQ_HWI5        (LOONGARCH_IRQ_BASE + 7)    /* HardWare Interrupt 5 */
#define LOONGARCH_IRQ_HWI6        (LOONGARCH_IRQ_BASE + 8)    /* HardWare Interrupt 6 */
#define LOONGARCH_IRQ_HWI7        (LOONGARCH_IRQ_BASE + 9)    /* HardWare Interrupt 7 */
#define LOONGARCH_IRQ_PMC         (LOONGARCH_IRQ_BASE + 10)   /* Performance Monitor Counter Overflow Interrupt */
#define LOONGARCH_IRQ_TIMER       (LOONGARCH_IRQ_BASE + 11)   /* Timer Interrupt */
#define LOONGARCH_IRQ_IPI         (LOONGARCH_IRQ_BASE + 12)   /* Inter-Processor Interrupt */

#define LOONGARCH_MAX_INTERRUPT   (LOONGARCH_IRQ_IPI)
/* Note that NR_IRQS = (QEMU_LA_IRQ_UART0 + 1) = 80 > 76 = LOONGARCH_MAX_INTERRUPT */

/* IRQ bit and IRQ mask */

#ifdef CONFIG_ARCH_LA32
#  define LOONGARCH_IRQ_BIT           (UINT32_C(1) << 31)
#else
#  define LOONGARCH_IRQ_BIT           (UINT64_C(1) << 63)
#endif

#define LOONGARCH_IRQ_MASK            (~LOONGARCH_IRQ_BIT)

/* Configuration ************************************************************/

/* If this is a kernel build, how many nested system calls should we
 * support?
 */

#ifndef CONFIG_SYS_NNEST
#  define CONFIG_SYS_NNEST  2
#endif

/* Processor PC */

#define REG_ERA_NDX         0

/* General pupose registers
 * $r0: Zero register does not need to be saved
 * $r1: ra (return address)
 */

#define REG_R1_NDX          1

/* $2: Thread Pointer
 * $3: Stack Pointer
 */

#define REG_R2_NDX          2
#define REG_R3_NDX          3

/* $4-$11 = a0-a7: Argument registers */

#define REG_R4_NDX          4
#define REG_R5_NDX          5
#define REG_R6_NDX          6
#define REG_R7_NDX          7
#define REG_R8_NDX          8
#define REG_R9_NDX          9
#define REG_R10_NDX         10
#define REG_R11_NDX         11

/* $12-$20 = t0-t8: Temporary registers */

#define REG_R12_NDX         12
#define REG_R13_NDX         13
#define REG_R14_NDX         14
#define REG_R15_NDX         15
#define REG_R16_NDX         16
#define REG_R17_NDX         17
#define REG_R18_NDX         18
#define REG_R19_NDX         19
#define REG_R20_NDX         20

/* $21: reserved (Non-allocatable) */

#define REG_R21_NDX         21

/* $22: s9 / fp Frame pointer */

#define REG_R22_NDX         22

/* $23-$31 = s0-s8: Saved registers */

#define REG_R23_NDX         23
#define REG_R24_NDX         24
#define REG_R25_NDX         25
#define REG_R26_NDX         26
#define REG_R27_NDX         27
#define REG_R28_NDX         28
#define REG_R29_NDX         29
#define REG_R30_NDX         30
#define REG_R31_NDX         31

/* Other CSR holding context information, note: era is at 0 position REG_ERA_NDX */

#define REG_CSR_PRMD_NDX    32
#define REG_CSR_ECFG_NDX    33
#define REG_CSR_EUEN_NDX    34

#ifdef CONFIG_ARCH_RISCV_INTXCPT_EXTREGS
#  define INT_XCPT_REGS     (34 + CONFIG_ARCH_RISCV_INTXCPT_EXTREGS)
#else
#  define INT_XCPT_REGS     34
#endif

#ifdef CONFIG_ARCH_LA32
#  define INT_REG_SIZE      4
#else
#  define INT_REG_SIZE      8
#endif

#define INT_XCPT_SIZE       (INT_REG_SIZE * INT_XCPT_REGS)

#ifdef CONFIG_ARCH_RV32
#  if defined(CONFIG_ARCH_QPFPU)
#    define FPU_REG_SIZE    4
#  elif defined(CONFIG_ARCH_DPFPU)
#    define FPU_REG_SIZE    2
#  elif defined(CONFIG_ARCH_FPU)
#    define FPU_REG_SIZE    1
#  endif
#else
#  if defined(CONFIG_ARCH_QPFPU)
#    define FPU_REG_SIZE    2
#  else
#    define FPU_REG_SIZE    1
#  endif
#endif

#ifdef CONFIG_ARCH_FPU
#  define REG_F0_NDX        (INT_XCPT_REGS + FPU_REG_SIZE * 0)
#  define REG_F1_NDX        (INT_XCPT_REGS + FPU_REG_SIZE * 1)
#  define REG_F2_NDX        (INT_XCPT_REGS + FPU_REG_SIZE * 2)
#  define REG_F3_NDX        (INT_XCPT_REGS + FPU_REG_SIZE * 3)
#  define REG_F4_NDX        (INT_XCPT_REGS + FPU_REG_SIZE * 4)
#  define REG_F5_NDX        (INT_XCPT_REGS + FPU_REG_SIZE * 5)
#  define REG_F6_NDX        (INT_XCPT_REGS + FPU_REG_SIZE * 6)
#  define REG_F7_NDX        (INT_XCPT_REGS + FPU_REG_SIZE * 7)
#  define REG_F8_NDX        (INT_XCPT_REGS + FPU_REG_SIZE * 8)
#  define REG_F9_NDX        (INT_XCPT_REGS + FPU_REG_SIZE * 9)
#  define REG_F10_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 10)
#  define REG_F11_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 11)
#  define REG_F12_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 12)
#  define REG_F13_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 13)
#  define REG_F14_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 14)
#  define REG_F15_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 15)
#  define REG_F16_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 16)
#  define REG_F17_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 17)
#  define REG_F18_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 18)
#  define REG_F19_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 19)
#  define REG_F20_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 20)
#  define REG_F21_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 21)
#  define REG_F22_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 22)
#  define REG_F23_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 23)
#  define REG_F24_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 24)
#  define REG_F25_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 25)
#  define REG_F26_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 26)
#  define REG_F27_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 27)
#  define REG_F28_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 28)
#  define REG_F29_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 29)
#  define REG_F30_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 30)
#  define REG_F31_NDX       (INT_XCPT_REGS + FPU_REG_SIZE * 31)
#  define REG_FCSR_NDX      (INT_XCPT_REGS + FPU_REG_SIZE * 32)

#  define FPU_XCPT_REGS     (FPU_REG_SIZE * 33)
#  define FPU_REG_FULL_SIZE (INT_REG_SIZE * FPU_REG_SIZE)
#else /* !CONFIG_ARCH_FPU */
#  define FPU_XCPT_REGS     (0)
#  define FPU_REG_FULL_SIZE (0)
#endif /* CONFIG_ARCH_FPU */

#define XCPTCONTEXT_REGS    (INT_XCPT_REGS + FPU_XCPT_REGS)

#define XCPTCONTEXT_SIZE    (INT_REG_SIZE * XCPTCONTEXT_REGS)

/* In assembly language, values have to be referenced as byte address
 * offsets.  But in C, it is more convenient to reference registers as
 * register save table offsets.
 */

#ifdef __ASSEMBLY__
#  define REG_EPC           (INT_REG_SIZE*REG_ERA_NDX)
#  define REG_R1            (INT_REG_SIZE*REG_R1_NDX)
#  define REG_R2            (INT_REG_SIZE*REG_R2_NDX)
#  define REG_R3            (INT_REG_SIZE*REG_R3_NDX)
#  define REG_R4            (INT_REG_SIZE*REG_R4_NDX)
#  define REG_R5            (INT_REG_SIZE*REG_R5_NDX)
#  define REG_R6            (INT_REG_SIZE*REG_R6_NDX)
#  define REG_R7            (INT_REG_SIZE*REG_R7_NDX)
#  define REG_R8            (INT_REG_SIZE*REG_R8_NDX)
#  define REG_R9            (INT_REG_SIZE*REG_R9_NDX)
#  define REG_R10           (INT_REG_SIZE*REG_R10_NDX)
#  define REG_R11           (INT_REG_SIZE*REG_R11_NDX)
#  define REG_R12           (INT_REG_SIZE*REG_R12_NDX)
#  define REG_R13           (INT_REG_SIZE*REG_R13_NDX)
#  define REG_R14           (INT_REG_SIZE*REG_R14_NDX)
#  define REG_R15           (INT_REG_SIZE*REG_R15_NDX)
#  define REG_R16           (INT_REG_SIZE*REG_R16_NDX)
#  define REG_R17           (INT_REG_SIZE*REG_R17_NDX)
#  define REG_R18           (INT_REG_SIZE*REG_R18_NDX)
#  define REG_R19           (INT_REG_SIZE*REG_R19_NDX)
#  define REG_R20           (INT_REG_SIZE*REG_R20_NDX)
#  define REG_R21           (INT_REG_SIZE*REG_R21_NDX)
#  define REG_R22           (INT_REG_SIZE*REG_R22_NDX)
#  define REG_R23           (INT_REG_SIZE*REG_R23_NDX)
#  define REG_R24           (INT_REG_SIZE*REG_R24_NDX)
#  define REG_R25           (INT_REG_SIZE*REG_R25_NDX)
#  define REG_R26           (INT_REG_SIZE*REG_R26_NDX)
#  define REG_R27           (INT_REG_SIZE*REG_R27_NDX)
#  define REG_R28           (INT_REG_SIZE*REG_R28_NDX)
#  define REG_R29           (INT_REG_SIZE*REG_R29_NDX)
#  define REG_R30           (INT_REG_SIZE*REG_R30_NDX)
#  define REG_R31           (INT_REG_SIZE*REG_R31_NDX)
#  define REG_CSR_PRMD      (INT_REG_SIZE*REG_CSR_PRMD_NDX)
#  define REG_CSR_ECFG      (INT_REG_SIZE*REG_CSR_ECFG_NDX)
#  define REG_CSR_EUEN      (INT_REG_SIZE*REG_CSR_EUEN_NDX)

#ifdef CONFIG_ARCH_FPU
#  define REG_F0            (INT_REG_SIZE*REG_F0_NDX)
#  define REG_F1            (INT_REG_SIZE*REG_F1_NDX)
#  define REG_F2            (INT_REG_SIZE*REG_F2_NDX)
#  define REG_F3            (INT_REG_SIZE*REG_F3_NDX)
#  define REG_F4            (INT_REG_SIZE*REG_F4_NDX)
#  define REG_F5            (INT_REG_SIZE*REG_F5_NDX)
#  define REG_F6            (INT_REG_SIZE*REG_F6_NDX)
#  define REG_F7            (INT_REG_SIZE*REG_F7_NDX)
#  define REG_F8            (INT_REG_SIZE*REG_F8_NDX)
#  define REG_F9            (INT_REG_SIZE*REG_F9_NDX)
#  define REG_F10           (INT_REG_SIZE*REG_F10_NDX)
#  define REG_F11           (INT_REG_SIZE*REG_F11_NDX)
#  define REG_F12           (INT_REG_SIZE*REG_F12_NDX)
#  define REG_F13           (INT_REG_SIZE*REG_F13_NDX)
#  define REG_F14           (INT_REG_SIZE*REG_F14_NDX)
#  define REG_F15           (INT_REG_SIZE*REG_F15_NDX)
#  define REG_F16           (INT_REG_SIZE*REG_F16_NDX)
#  define REG_F17           (INT_REG_SIZE*REG_F17_NDX)
#  define REG_F18           (INT_REG_SIZE*REG_F18_NDX)
#  define REG_F19           (INT_REG_SIZE*REG_F19_NDX)
#  define REG_F20           (INT_REG_SIZE*REG_F20_NDX)
#  define REG_F21           (INT_REG_SIZE*REG_F21_NDX)
#  define REG_F22           (INT_REG_SIZE*REG_F22_NDX)
#  define REG_F23           (INT_REG_SIZE*REG_F23_NDX)
#  define REG_F24           (INT_REG_SIZE*REG_F24_NDX)
#  define REG_F25           (INT_REG_SIZE*REG_F25_NDX)
#  define REG_F26           (INT_REG_SIZE*REG_F26_NDX)
#  define REG_F27           (INT_REG_SIZE*REG_F27_NDX)
#  define REG_F28           (INT_REG_SIZE*REG_F28_NDX)
#  define REG_F29           (INT_REG_SIZE*REG_F29_NDX)
#  define REG_F30           (INT_REG_SIZE*REG_F30_NDX)
#  define REG_F31           (INT_REG_SIZE*REG_F31_NDX)
#  define REG_FCSR          (INT_REG_SIZE*REG_FCSR_NDX)
#endif

#else
#  define REG_EPC           REG_ERA_NDX
#  define REG_R1            REG_R1_NDX
#  define REG_R2            REG_R2_NDX
#  define REG_R3            REG_R3_NDX
#  define REG_R4            REG_R4_NDX
#  define REG_R5            REG_R5_NDX
#  define REG_R6            REG_R6_NDX
#  define REG_R7            REG_R7_NDX
#  define REG_R8            REG_R8_NDX
#  define REG_R9            REG_R9_NDX
#  define REG_R10           REG_R10_NDX
#  define REG_R11           REG_R11_NDX
#  define REG_R12           REG_R12_NDX
#  define REG_R13           REG_R13_NDX
#  define REG_R14           REG_R14_NDX
#  define REG_R15           REG_R15_NDX
#  define REG_R16           REG_R16_NDX
#  define REG_R17           REG_R17_NDX
#  define REG_R18           REG_R18_NDX
#  define REG_R19           REG_R19_NDX
#  define REG_R20           REG_R20_NDX
#  define REG_R21           REG_R21_NDX
#  define REG_R22           REG_R22_NDX
#  define REG_R23           REG_R23_NDX
#  define REG_R24           REG_R24_NDX
#  define REG_R25           REG_R25_NDX
#  define REG_R26           REG_R26_NDX
#  define REG_R27           REG_R27_NDX
#  define REG_R28           REG_R28_NDX
#  define REG_R29           REG_R29_NDX
#  define REG_R30           REG_R30_NDX
#  define REG_R31           REG_R31_NDX
#  define REG_CSR_PRMD      REG_CSR_PRMD_NDX
#  define REG_CSR_ECFG      REG_CSR_ECFG_NDX
#  define REG_CSR_EUEN      REG_CSR_EUEN_NDX

#ifdef CONFIG_ARCH_FPU
#  define REG_F0            REG_F0_NDX
#  define REG_F1            REG_F1_NDX
#  define REG_F2            REG_F2_NDX
#  define REG_F3            REG_F3_NDX
#  define REG_F4            REG_F4_NDX
#  define REG_F5            REG_F5_NDX
#  define REG_F6            REG_F6_NDX
#  define REG_F7            REG_F7_NDX
#  define REG_F8            REG_F8_NDX
#  define REG_F9            REG_F9_NDX
#  define REG_F10           REG_F10_NDX
#  define REG_F11           REG_F11_NDX
#  define REG_F12           REG_F12_NDX
#  define REG_F13           REG_F13_NDX
#  define REG_F14           REG_F14_NDX
#  define REG_F15           REG_F15_NDX
#  define REG_F16           REG_F16_NDX
#  define REG_F17           REG_F17_NDX
#  define REG_F18           REG_F18_NDX
#  define REG_F19           REG_F19_NDX
#  define REG_F20           REG_F20_NDX
#  define REG_F21           REG_F21_NDX
#  define REG_F22           REG_F22_NDX
#  define REG_F23           REG_F23_NDX
#  define REG_F24           REG_F24_NDX
#  define REG_F25           REG_F25_NDX
#  define REG_F26           REG_F26_NDX
#  define REG_F27           REG_F27_NDX
#  define REG_F28           REG_F28_NDX
#  define REG_F29           REG_F29_NDX
#  define REG_F30           REG_F30_NDX
#  define REG_F31           REG_F31_NDX
#  define REG_FCSR          REG_FCSR_NDX
#endif

#endif

/* Now define more user friendly alternative name that can be used either
 * in assembly or C contexts.
 */

/* $1 = ra: Return address */

#define REG_RA              REG_R1

/* $2 = tp:  Thread Pointer */

#define REG_TP              REG_R2

/* $3 = sp:  The value of the stack pointer on return from the exception */

#define REG_SP              REG_R3

/* $4-$11 = a0-a7: Argument registers */

#define REG_A0              REG_R4
#define REG_A1              REG_R5
#define REG_A2              REG_R6
#define REG_A3              REG_R7
#define REG_A4              REG_R8
#define REG_A5              REG_R9
#define REG_A6              REG_R10
#define REG_A7              REG_R11

/* $12-$20 = t0-t8: Caller saved temporary registers */

#define REG_T0              REG_R12
#define REG_T1              REG_R13
#define REG_T2              REG_R14
#define REG_T3              REG_R15
#define REG_T4              REG_R16
#define REG_T5              REG_R17
#define REG_T6              REG_R18
#define REG_T7              REG_R19
#define REG_T8              REG_R20

/* $21: reserved (Non-allocatable) */

#define REG_RESERVED        REG_R21

/* $22 = either s9 or fp:  Depends if a frame pointer is used or not */

#define REG_S9              REG_R22
#define REG_FP              REG_R22

// /* $23-$31 = s2-s11: Callee saved registers */

#define REG_S0              REG_R23
#define REG_S1              REG_R24
#define REG_S2              REG_R25
#define REG_S3              REG_R26
#define REG_S4              REG_R27
#define REG_S5              REG_R28
#define REG_S6              REG_R29
#define REG_S7              REG_R30
#define REG_S8              REG_R31

#ifdef CONFIG_ARCH_FPU
/* $0-$1 = fs0-fs1: Callee saved registers */

#  define REG_FS0           REG_F8
#  define REG_FS1           REG_F9

/* $18-$27 = fs2-fs11: Callee saved registers */

#  define REG_FS2           REG_F18
#  define REG_FS3           REG_F19
#  define REG_FS4           REG_F20
#  define REG_FS5           REG_F21
#  define REG_FS6           REG_F22
#  define REG_FS7           REG_F23
#  define REG_FS8           REG_F24
#  define REG_FS9           REG_F25
#  define REG_FS10          REG_F26
#  define REG_FS11          REG_F27
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/* This structure represents the return state from a system call */

#ifdef CONFIG_LIB_SYSCALL
struct xcpt_syscall_s
{
  uintptr_t sysreturn;   /* The return PC */
#ifndef CONFIG_BUILD_FLAT
  uintptr_t int_ctx;     /* Interrupt context (i.e. m-/sstatus) */
#endif
};
#endif

/* The following structure is included in the TCB and defines the complete
 * state of the thread.
 */

struct xcptcontext
{
  /* The following function pointer is non-NULL if there are pending signals
   * to be processed.
   */

  void *sigdeliver; /* Actual type is sig_deliver_t */

  /* These additional register save locations are used to implement the
   * signal delivery trampoline.
   *
   * REVISIT:  Because there is only a reference of these save areas,
   * only a single signal handler can be active.  This precludes
   * queuing of signal actions.  As a result, signals received while
   * another signal handler is executing will be ignored!
   */

  uintptr_t *saved_regs;

#ifndef CONFIG_BUILD_FLAT
  /* This is the saved address to use when returning from a user-space
   * signal handler.
   */

  uintptr_t sigreturn;
#endif

#ifdef CONFIG_LIB_SYSCALL
  /* The following array holds information needed to return from each nested
   * system call.
   */

  uint8_t nsyscalls;
  struct xcpt_syscall_s syscall[CONFIG_SYS_NNEST];

#endif

#ifdef CONFIG_ARCH_ADDRENV
#ifdef CONFIG_ARCH_KERNEL_STACK
  /* In this configuration, all syscalls execute from an internal kernel
   * stack.  Why?  Because when we instantiate and initialize the address
   * environment of the new user process, we will temporarily lose the
   * address environment of the old user process, including its stack
   * contents.  The kernel C logic will crash immediately with no valid
   * stack in place.
   */

  uintptr_t *ustkptr;  /* Saved user stack pointer */
  uintptr_t *kstack;   /* Allocate base of the (aligned) kernel stack */
  uintptr_t *kstkptr;  /* Saved kernel stack pointer */
#endif
#endif

  /* Register save area */

  uintptr_t *regs;
};

#endif /* __ASSEMBLY__ */

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Inline functions
 ****************************************************************************/

/* Return the current value of the stack pointer */

static inline uintptr_t up_getsp(void)
{
  register uintptr_t sp;
  __asm__
  (
    "\tadd.d  %0, $r0, $r3\n"
    : "=r"(sp)
  );
  return sp;
}

/****************************************************************************
 * Public Data
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/* g_current_regs[] holds a references to the current interrupt level
 * register storage structure.  If is non-NULL only during interrupt
 * processing.  Access to g_current_regs[] must be through the macro
 * CURRENT_REGS for portability.
 */

/* For the case of architectures with multiple CPUs, then there must be one
 * such value for each processor that can receive an interrupt.
 */

EXTERN volatile uintptr_t *g_current_regs[CONFIG_SMP_NCPUS];
#define CURRENT_REGS (g_current_regs[up_cpu_index()])

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: up_irq_enable
 *
 * Description:
 *   Return the current interrupt state and enable interrupts
 *
 ****************************************************************************/

irqstate_t up_irq_enable(void);

/****************************************************************************
 * Name: up_cpu_index
 *
 * Description:
 *   Return an index in the range of 0 through (CONFIG_SMP_NCPUS-1) that
 *   corresponds to the currently executing CPU.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   An integer index in the range of 0 through (CONFIG_SMP_NCPUS-1) that
 *   corresponds to the currently executing CPU.
 *
 ****************************************************************************/

#ifdef CONFIG_SMP
int up_cpu_index(void);
#else
#  define up_cpu_index() (0)
#endif

/****************************************************************************
 * Inline Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_irq_save
 *
 * Description:
 *   Disable interrupts and return the previous value of the mstatus register
 *
 ****************************************************************************/

static inline irqstate_t up_irq_save(void)
{
  irqstate_t flags=0;

  /* Read crmd & clear interrupt enable (IE) in crmd */
  __asm__ __volatile__
    (
      "csrxchg %0, %1, " __XSTR(LOONGARCH_CSR_CRMD) "\n"
      :"+r" (flags)
      :"r" (CSR_CRMD_IE)
      :"memory"
    );


  /* Return the previous crmd value so that it can be restored with
   * up_irq_restore().
   */

  return flags;
}

/****************************************************************************
 * Name: up_irq_restore
 *
 * Description:
 *   Restore the value of the mstatus register
 *
 ****************************************************************************/

static inline void up_irq_restore(irqstate_t flags)
{
    __asm__ __volatile__
    (
      "csrxchg %0, %1, " __XSTR(LOONGARCH_CSR_CRMD) "\n"
      : "+r" (flags) 
      : "r" (CSR_CRMD_IE)
      : "memory"
    );
}

/****************************************************************************
 * Name: up_interrupt_context
 *
 * Description:
 *   Return true is we are currently executing in the interrupt
 *   handler context.
 *
 ****************************************************************************/

static inline bool up_interrupt_context(void)
{
#ifdef CONFIG_SMP
  irqstate_t flags = up_irq_save();
#endif

  bool ret = CURRENT_REGS != NULL;

#ifdef CONFIG_SMP
  up_irq_restore(flags);
#endif

  return ret;
}

#undef EXTERN
#if defined(__cplusplus)
}
#endif
#endif /* __ASSEMBLY__ */

#endif /* __ARCH_LOONGARCH_INCLUDE_IRQ_H */
