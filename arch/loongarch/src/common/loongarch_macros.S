/****************************************************************************
 * arch/loongarch/src/common/loongarch_macros.S
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

.file "loongarch_macros.S"

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <arch/arch.h>
#include <arch/csr.h>
#include <arch/irq.h>

#include <sys/types.h>

#include "loongarch_internal.h"
#include "loongarch_percpu.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Name: save_ctx
 *
 * Parameter:
 *   in - Pointer to where the save is performed (e.g. sp)
 *
 * Description:
 *   Save the common context registers (i.e. work / temp / etc).
 *
 ****************************************************************************/

.macro save_ctx in

  REGSTORE  $r1,  \in, REG_R1     /* ra */
  REGSTORE  $r2,  \in, REG_R2     /* tp */

  REGSTORE  $r4,  \in, REG_R4     /* a0 */
  REGSTORE  $r5,  \in, REG_R5     /* a1 */
  REGSTORE  $r6,  \in, REG_R6     /* a2 */
  REGSTORE  $r7,  \in, REG_R7     /* a3 */
  REGSTORE  $r8,  \in, REG_R8     /* a4 */
  REGSTORE  $r9,  \in, REG_R9     /* a5 */
  REGSTORE  $r10, \in, REG_R10    /* a6 */
  REGSTORE  $r11, \in, REG_R11    /* a7 */
  REGSTORE  $r12, \in, REG_R12    /* t0 */
  REGSTORE  $r13, \in, REG_R13    /* t1 */
  REGSTORE  $r14, \in, REG_R14    /* t2 */
  REGSTORE  $r15, \in, REG_R15    /* t3 */
  REGSTORE  $r16, \in, REG_R16    /* t4 */
  REGSTORE  $r17, \in, REG_R17    /* t5 */
  REGSTORE  $r18, \in, REG_R18    /* t6 */
  REGSTORE  $r19, \in, REG_R19    /* t7 */
  REGSTORE  $r20, \in, REG_R20    /* t8 */

  REGSTORE  $r22, \in, REG_R22    /* fp/s9 */
  REGSTORE  $r23, \in, REG_R23    /* s0 */
  REGSTORE  $r24, \in, REG_R24    /* s1 */
  REGSTORE  $r25, \in, REG_R25    /* s2 */
  REGSTORE  $r26, \in, REG_R26    /* s3 */
  REGSTORE  $r27, \in, REG_R27    /* s4 */
  REGSTORE  $r28, \in, REG_R28    /* s5 */
  REGSTORE  $r29, \in, REG_R29    /* s6 */
  REGSTORE  $r30, \in, REG_R30    /* s7 */
  REGSTORE  $r31, \in, REG_R31    /* s8 */

.endm

/****************************************************************************
 * Name: loongarch_savefpu
 *
 * Parameter:
 *   in - Pointer to where the save is performed (e.g. sp)
 *
 * Description:
 *   Save the FPU context registers (i.e. work / temp / etc).
 *
 ****************************************************************************/

.macro loongarch_savefpu in

#ifdef CONFIG_ARCH_FPU

skip_save_fpu:

#endif

.endm

/****************************************************************************
 * Name: load_ctx
 *
 * Parameter:
 *   out - Pointer to where the load is performed (e.g. sp)
 *
 * Description:
 *   Load the common context registers (i.e. work / temp / etc).
 *
 ****************************************************************************/

.macro load_ctx out

  REGLOAD  $r1,  \out, REG_R1     /* ra */
  REGLOAD  $r2,  \out, REG_R2     /* tp */

  REGLOAD  $r4,  \out, REG_R4     /* a0 */
  REGLOAD  $r5,  \out, REG_R5     /* a1 */
  REGLOAD  $r6,  \out, REG_R6     /* a2 */
  REGLOAD  $r7,  \out, REG_R7     /* a3 */
  REGLOAD  $r8,  \out, REG_R8     /* a4 */
  REGLOAD  $r9,  \out, REG_R9     /* a5 */
  REGLOAD  $r10, \out, REG_R10    /* a6 */
  REGLOAD  $r11, \out, REG_R11    /* a7 */
  REGLOAD  $r12, \out, REG_R12    /* t0 */
  REGLOAD  $r13, \out, REG_R13    /* t1 */
  REGLOAD  $r14, \out, REG_R14    /* t2 */
  REGLOAD  $r15, \out, REG_R15    /* t3 */
  REGLOAD  $r16, \out, REG_R16    /* t4 */
  REGLOAD  $r17, \out, REG_R17    /* t5 */
  REGLOAD  $r18, \out, REG_R18    /* t6 */
  REGLOAD  $r19, \out, REG_R19    /* t7 */
  REGLOAD  $r20, \out, REG_R20    /* t8 */

  REGLOAD  $r22, \out, REG_R22    /* fp/s9 */
  REGLOAD  $r23, \out, REG_R23    /* s0 */
  REGLOAD  $r24, \out, REG_R24    /* s1 */
  REGLOAD  $r25, \out, REG_R25    /* s2 */
  REGLOAD  $r26, \out, REG_R26    /* s3 */
  REGLOAD  $r27, \out, REG_R27    /* s4 */
  REGLOAD  $r28, \out, REG_R28    /* s5 */
  REGLOAD  $r29, \out, REG_R29    /* s6 */
  REGLOAD  $r30, \out, REG_R30    /* s7 */
  REGLOAD  $r31, \out, REG_R31    /* s8 */

.endm

/****************************************************************************
 * Name: loongarch_loadfpu
 *
 * Parameter:
 *   out - Pointer to where the load is performed (e.g. sp)
 *
 * Description:
 *   Load the FPU context registers (i.e. work / temp / etc).
 *
 ****************************************************************************/

.macro loongarch_loadfpu out

#ifdef CONFIG_ARCH_FPU

skip_load_fpu:

#endif

.endm

/****************************************************************************
 * Name: setintstack
 *
 * Description:
 *   Set the current stack pointer to the "top" the interrupt stack. Works
 *   for single CPU case in flat mode.
 *   Must be provided by MCU-specific logic in the SMP case, or the kernel
 *   runs in supervisor mode (S-mode).
 *
 ****************************************************************************/

#if CONFIG_ARCH_INTERRUPTSTACK > 15
#if !defined(CONFIG_SMP)
.macro  setintstack tmp0, tmp1
  la    $sp, g_intstacktop
.endm
#endif /* !defined(CONFIG_SMP)*/
#endif /* CONFIG_ARCH_INTERRUPTSTACK > 15 */

/****************************************************************************
 * Name: riscv_mhartid
 *
 * Description:
 *   Context aware way to query hart id
 *
 * Returned Value:
 *   Hart id
 *
 ****************************************************************************/

.macro  riscv_mhartid out
#ifdef CONFIG_ARCH_USE_S_MODE
  csrr    \out, CSR_SCRATCH
  REGLOAD \out, RISCV_PERCPU_HARTID(\out)
#else
  csrr    \out, mhartid
#endif
.endm
