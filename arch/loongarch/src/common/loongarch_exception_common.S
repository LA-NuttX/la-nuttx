/****************************************************************************
 * arch/loongarch/src/common/loongarch_exception_common.S
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <arch/arch.h>
#include <arch/irq.h>
#include <arch/mode.h>

#include <sys/types.h>

#include "chip.h"

#include "loongarch_macros.S"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Using address environments currently require that a common interrupt stack
 * is in place. This is needed because during context switch the procedure
 * that swaps the active address environment is dependent on a stack, which
 * must be a 'neutral' stack.
 *
 * Another option would be to use a per-process kernel stack, but full
 * support for this is not yet in place, so use the common IRQ stack instead.
 */

#ifdef CONFIG_ARCH_ADDRENV
#  if CONFIG_ARCH_INTERRUPTSTACK == 0 && !defined(CONFIG_ARCH_KERNEL_STACK)
#    error "IRQ or kernel stack is needed for swapping address environments"
#  endif
#endif

/* Provide a default section for the exeception handler. */

#ifndef EXCEPTION_SECTION
#  define EXCEPTION_SECTION .text
#endif

/****************************************************************************
 * Public Symbols
 ****************************************************************************/

/****************************************************************************
 * Name: exception_common
 *
 * Description:
 *   Handles interrupts. If kernel is in S-mode, handles delegated interrupts
 *   in S-mode interrupt handler.
 *
 ****************************************************************************/

  .section EXCEPTION_SECTION
  .global exception_common
  .align  8

exception_common:

  addi.d      $sp, $sp, -XCPTCONTEXT_SIZE
  save_ctx    $sp

  addi.d      $s0, $sp, XCPTCONTEXT_SIZE
  REGSTORE    $s0, $sp, REG_SP          /* original SP */

  csrrd       $s0, LOONGARCH_CSR_EUEN
  REGSTORE    $s0, $sp, REG_CSR_EUEN    /* csr: store euen */

  csrrd       $s0, LOONGARCH_CSR_ECFG
  REGSTORE    $s0, $sp, REG_CSR_ECFG    /* csr: store ecfg */

  csrrd       $s0, LOONGARCH_CSR_PRMD
  REGSTORE    $s0, $sp, REG_CSR_PRMD    /* csr: store prmd */

  csrrd       $s0, LOONGARCH_CSR_ERA
  REGSTORE    $s0, $sp, REG_EPC         /* exception PC */

  loongarch_savefpu   $sp

  /* Setup arg0(with exception or irq number info), arg1(context) */

  csrrd       $a0, LOONGARCH_CSR_ESTAT  /* exception or irq number info */
  move        $a1, $sp                  /* context = sp */


#if CONFIG_ARCH_INTERRUPTSTACK > 15

  /* Switch to interrupt stack */

  setintstack $t0, $t1

  /* Call interrupt handler in C */

  bl          loongarch_dispatch_irq

#else
  /* Reserve some space for CURRENT_REGS if interrupt stack disabled */

  addi.d      $sp, $sp, -XCPTCONTEXT_SIZE

  /* Call interrupt handler in C */

  bl          loongarch_dispatch_irq

  /* Restore sp */

  addi.d      $sp, $sp, XCPTCONTEXT_SIZE
#endif

  /* If context switch is needed, return a new sp */

  move        $sp, $a0

  loongarch_loadfpu   $sp

  REGLOAD     $s0, $sp, REG_EPC         /* restore exception PC */
  csrwr       $s0, LOONGARCH_CSR_ERA

  REGLOAD     $s0, $sp, REG_CSR_PRMD    /* csr: restore prmd */
  csrwr       $s0, LOONGARCH_CSR_PRMD

  REGLOAD     $s0, $sp, REG_CSR_ECFG    /* csr: restore ecfg */
  csrwr       $s0, LOONGARCH_CSR_ECFG

  REGLOAD     $s0, $sp, REG_CSR_EUEN    /* csr: restore euen */
  csrwr       $s0, LOONGARCH_CSR_EUEN

  load_ctx    $sp

  REGLOAD     $sp, $sp, REG_SP          /* restore original sp */

  /* Return from exception */
  ertn

/*****************************************************************************
 *  Name: g_intstackalloc and g_intstacktop
 ****************************************************************************/

/* Total required interrupt stack size */

#define STACK_ALLOC_SIZE (CONFIG_ARCH_INTERRUPTSTACK * CONFIG_SMP_NCPUS)

#if CONFIG_ARCH_INTERRUPTSTACK > 15
  .bss
  .balign 16
  .global g_intstackalloc
  .global g_intstacktop
  .type   g_intstackalloc, object
  .type   g_intstacktop, object
g_intstackalloc:
  .skip  STACK_ALIGN_UP(STACK_ALLOC_SIZE)
g_intstacktop:
  .size  g_intstacktop, 0
  .size  g_intstackalloc, STACK_ALIGN_DOWN(STACK_ALLOC_SIZE)
#endif
