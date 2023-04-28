/****************************************************************************
 * arch/loongarch/src/common/supervisor/loongarch_syscall.S
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

.file "loongarch_syscall.S"

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <arch/mode.h>

#include "chip.h"

#include "loongarch_macros.S"
#include "loongarch_internal.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Symbols
 ****************************************************************************/

    .globl  sys_call0
    .globl  sys_call1
    .globl  sys_call2
    .globl  sys_call3
    .globl  sys_call4
    .globl  sys_call5
    .globl  sys_call6

/****************************************************************************
 * Name: sys_callx
 *
 * Description:
 *   Dispatch syscall from kernel
 *
 * C Function Prototype:
 *   uintptr_t sys_callx(unsigned int nbr, ...);
 *
 * Input Parameters:
 *   Assumes the context to return is already set up
 *
 * Returned Value:
 *   Return value of system call is returned into contex
 *
 * Assumptions:
 *   Task is running in privileged mode
 *
 ****************************************************************************/

.type sys_call0, function
.type sys_call1, function
.type sys_call2, function
.type sys_call3, function
.type sys_call4, function
.type sys_call5, function
.type sys_call6, function

sys_call0:
sys_call1:
sys_call2:
sys_call3:
sys_call4:
sys_call5:
sys_call6:

  addi.d    $sp, $sp, -XCPTCONTEXT_SIZE /* make room */
  save_ctx  $sp                         /* save current context */

  /* Mask interrupts and store the status register to context */

  csrrd     $s2, LOONGARCH_CSR_PRMD       /* s2 holds prmd, s0 holds crmd */
  li.d      $s1, CSR_CRMD_IE
  move      $s0, $r0
  csrxchg   $s0, $s1, LOONGARCH_CSR_CRMD  /* disable IE in crmd */

  and       $s1, $s0, $s1                 /* if (CRMD & IE) */
  beqz      $s1, 1f                       

  li.d      $s1, ~CSR_CRMD_IE             /* clear IE of older crmd value in s0*/
  and       $s0, $s0, $s1

  li.d      $s1, CSR_PRMD_PIE             /* set PIE */
  or        $s2, $s2, $s1

1:
  REGSTORE  $s0, $sp, REG_CSR_CRMD        /* store crmd to context */

  li.d      $s1, ~CSR_PRMD_PPLV           /* set previous privilege */
  and       $s2, $s2, $s1
  REGSTORE  $s2, $sp, REG_CSR_PRMD        /* store prmd to context */
  

  REGSTORE  $ra, $sp, REG_EPC             /* save ra to epc */

  addi.d    $s0, $sp, XCPTCONTEXT_SIZE
  REGSTORE  $s0, $sp, REG_SP              /* original SP */

  csrrd     $s0, LOONGARCH_CSR_EUEN
  REGSTORE  $s0, $sp, REG_CSR_EUEN        /* csr: store euen */

  csrrd     $s0, LOONGARCH_CSR_ECFG
  REGSTORE  $s0, $sp, REG_CSR_ECFG        /* csr: store ecfg */

  loongarch_savefpu   $sp

  move      $a0, $sp                      /* a0 holds the sp value, sp will switch to kernel stack */

#if CONFIG_ARCH_INTERRUPTSTACK > 15
  /* Switch to interrupt stack */

  setintstack $t0, $t1
#endif
  bl        loongarch_perform_syscall

  /* Restore (potentially new) context */

  move      $sp, $a0

  loongarch_loadfpu   $sp

  REGLOAD   $s0, $sp, REG_EPC
  csrwr     $s0, LOONGARCH_CSR_ERA

  REGLOAD   $s0, $sp, REG_CSR_ECFG        /* csr: restore ecfg */
  csrwr     $s0, LOONGARCH_CSR_ECFG

  REGLOAD   $s0, $sp, REG_CSR_EUEN        /* csr: restore euen */
  csrwr     $s0, LOONGARCH_CSR_EUEN

  /* Restore prmd, but don't enable interrupts yet */
  REGLOAD   $s2, $sp, REG_CSR_PRMD        /* csr: restore prmd */
  REGLOAD   $s0, $sp, REG_CSR_CRMD        /* csr: restore crmd */

  li.d      $s1, CSR_CRMD_IE
  and       $s1, $s0, $s1                 /* if (CRMD & IE) */
  beqz      $s1, 2f

  li.d      $s1, ~CSR_CRMD_IE             /* clear IE */
  and       $s0, $s0, $s1
  li.d      $s1, CSR_PRMD_PIE             /* set PIE */
  or        $s2, $s2, $s1

2:
  csrwr     $s0, LOONGARCH_CSR_CRMD
  csrwr     $s2, LOONGARCH_CSR_PRMD

  load_ctx  $sp

  REGLOAD   $sp, $sp, REG_SP              /* restore original sp */

  /* return from exception, which updates the status register */
  ertn

  .size sys_call0, .-sys_call0
  .size sys_call1, .-sys_call1
  .size sys_call2, .-sys_call2
  .size sys_call3, .-sys_call3
  .size sys_call4, .-sys_call4
  .size sys_call5, .-sys_call5
  .size sys_call6, .-sys_call6

  .end