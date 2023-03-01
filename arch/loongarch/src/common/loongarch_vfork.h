/****************************************************************************
 * arch/loongarch/src/common/loongarch_vfork.h
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

#ifndef __ARCH_LOONGARCH_SRC_COMMON_LOONGARCH_VFORK_H
#define __ARCH_LOONGARCH_SRC_COMMON_LOONGARCH_VFORK_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <arch/irq.h>

#include "loongarch_internal.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Register s9 is a frame pointer in LoongArch64 ABI. */

#undef VFORK_HAVE_FP

/* Register ABI Name Description                        Saver
 *
 * r0       zero     Hard-wired zero                    —
 * r1       ra       Return address                     Caller
 * r2       tp       Thread pointer                     —
 * r3       sp       Stack pointer                      Callee*
 * r4-5     a0-1     Function arguments/return values   Caller
 * r6-11    a2-7     Function arguments                 Caller
 * r12-20   t0-t8    Temporaries                        Caller
 * r21      —        Reserved                           —
 * r22      s9/fp    Static register/frame pointer      Callee*
 * r23-31   s0-8     Static registers                   Callee*
 * 
 * f0–1     fa0–1    FP arguments/return values         Caller
 * f2–7     fa2–7    FP arguments                       Caller
 * f8–23    ft0–15   FP temporaries                     Caller
 * f24–31   fs0–7    FP saved registers                 Callee*
 */

#define VFORK_S0_OFFSET     (0*INT_REG_SIZE)   /* Saved register s0 */
#define VFORK_S1_OFFSET     (1*INT_REG_SIZE)   /* Saved register s1 */
#define VFORK_S2_OFFSET     (2*INT_REG_SIZE)   /* Saved register s2 */
#define VFORK_S3_OFFSET     (3*INT_REG_SIZE)   /* Saved register s3 */
#define VFORK_S4_OFFSET     (4*INT_REG_SIZE)   /* Saved register s4 */
#define VFORK_S5_OFFSET     (5*INT_REG_SIZE)   /* Saved register s5 */
#define VFORK_S6_OFFSET     (6*INT_REG_SIZE)   /* Saved register s6 */
#define VFORK_S7_OFFSET     (7*INT_REG_SIZE)   /* Saved register s7 */
#define VFORK_S8_OFFSET     (8*INT_REG_SIZE)   /* Saved register s8 */
#define VFORK_S9_OFFSET     (9*INT_REG_SIZE)   /* Saved register s9/frame pointer */

#define VFORK_SP_OFFSET     (10*INT_REG_SIZE)  /* Stack pointer*/
#define VFORK_RA_OFFSET     (11*INT_REG_SIZE)  /* Return address*/

#define VFORK_INT_SIZE      (12*INT_REG_SIZE)

#ifdef CONFIG_ARCH_FPU
#  define VFORK_FS0_OFFSET  (VFORK_INT_SIZE + 0*FPU_REG_FULL_SIZE)
#  define VFORK_FS1_OFFSET  (VFORK_INT_SIZE + 1*FPU_REG_FULL_SIZE)
#  define VFORK_FS2_OFFSET  (VFORK_INT_SIZE + 2*FPU_REG_FULL_SIZE)
#  define VFORK_FS3_OFFSET  (VFORK_INT_SIZE + 3*FPU_REG_FULL_SIZE)
#  define VFORK_FS4_OFFSET  (VFORK_INT_SIZE + 4*FPU_REG_FULL_SIZE)
#  define VFORK_FS5_OFFSET  (VFORK_INT_SIZE + 5*FPU_REG_FULL_SIZE)
#  define VFORK_FS6_OFFSET  (VFORK_INT_SIZE + 6*FPU_REG_FULL_SIZE)
#  define VFORK_FS7_OFFSET  (VFORK_INT_SIZE + 7*FPU_REG_FULL_SIZE)
#  define VFORK_FPU_SIZE    (8*FPU_REG_FULL_SIZE)
#else
#  define VFORK_FPU_SIZE    (0)
#endif

#define VFORK_SIZEOF        STACK_ALIGN_UP(VFORK_INT_SIZE + VFORK_FPU_SIZE)

#ifndef __ASSEMBLY__
struct vfork_s
{
  /* CPU registers */

  uintptr_t s0;   /* Saved register s0 */
  uintptr_t s1;   /* Saved register s1 */
  uintptr_t s2;   /* Saved register s2 */
  uintptr_t s3;   /* Saved register s3 */
  uintptr_t s4;   /* Saved register s4 */
  uintptr_t s5;   /* Saved register s5 */
  uintptr_t s6;   /* Saved register s6 */
  uintptr_t s7;   /* Saved register s7 */
  uintptr_t s8;   /* Saved register s8 */
  uintptr_t fp;   /* Saved register s9  / frame pointer */

  uintptr_t sp;   /* Stack pointer */
  uintptr_t ra;   /* Return address */

  /* Floating point registers */

#ifdef CONFIG_ARCH_FPU
  uintptr_t fs0;   /* Saved register fs0 */
  uintptr_t fs1;   /* Saved register fs1 */
  uintptr_t fs2;   /* Saved register fs2 */
  uintptr_t fs3;   /* Saved register fs3 */
  uintptr_t fs4;   /* Saved register fs4 */
  uintptr_t fs5;   /* Saved register fs5 */
  uintptr_t fs6;   /* Saved register fs6 */
  uintptr_t fs7;   /* Saved register fs7 */
#endif
};
#endif

#endif /* __ARCH_LOONGARCH_SRC_COMMON_LOONGARCH_VFORK_H */
