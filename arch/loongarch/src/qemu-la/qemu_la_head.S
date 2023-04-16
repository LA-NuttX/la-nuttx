/****************************************************************************
 * arch/loongarch/src/qemu-la/qemu_la_head.S
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

#include "chip.h"
#include "loongarch_internal.h"

/****************************************************************************
 * Public Symbols
 ****************************************************************************/

  /* Exported Symbols */

  .section .text
  .global __start

__start:

  /* Load cpuid */

  csrrd   $a0, LOONGARCH_CSR_CPUID
  bstrpick.d  $a0, $a0, 8, 0
  
  /* Set stack pointer to the idle thread stack: QEMU_LA_IDLESTACK_TOP = QEMU_LA_IDLESTACK_BASE + QEMU_LA_IDLESTACK_SIZE */

  bnez    $a0, 1f
  la.abs  $t0, QEMU_LA_IDLESTACK_BASE
  li.d    $t1, QEMU_LA_IDLESTACK_SIZE
  add.d   $sp, $t0, $t1

#ifndef CONFIG_BUILD_KERNEL

	la.pcrel	t0, _sbss		# clear .bss
 	st.d		zero, t0, 0
	la.pcrel	t1, _ebss - 8
4:
 	addi.d		t0, t0, 8
 	st.d		zero, t0, 0
 	bne		t0, t1, 4b
#endif
  b       2f

1:
  /* Load the number of CPUs that the kernel supports */

#ifdef CONFIG_SMP
  li.d   $t1, CONFIG_SMP_NCPUS
#else
  li.d   $t1, 1
#endif

  /* If a0 (mhartid) >= t1 (the number of CPUs), stop here */

  blt  $a0, $t1, 3f
  /* csrw mie, zero*/
  b 1b
  idle 0

3:
  /* To get g_cpu_basestack[mhartid], must get g_cpu_basestack first */

  la   $t0, g_cpu_basestack

  /* Offset = pointer width * hart id */

#ifdef CONFIG_ARCH_LA32
  slli.d $t1, $a0, 2
#else
  slli.d $t1, $a0, 3
#endif
  add.d  $t0, $t0, $t1

  /* Load idle stack base to sp */

  /*REGLOAD sp, 0(t0)*/

  /*
   * sp (stack top) = sp + idle stack size - XCPTCONTEXT_SIZE
   * 
   * Note: Reserve some space used by up_initial_state since we are already
   * running and using the per CPU idle stack.
   */

  li.d   $t0, STACK_ALIGN_UP(CONFIG_IDLETHREAD_STACKSIZE - XCPTCONTEXT_SIZE)
  add.d  $sp, $sp, $t0

2:

  /* Set Direct Mapping Window0: 0x9000 xxxx xxxx xxxx, PLV0 & PLV3, Coherent Cached */
  li.d    $t0, 0x900000000000001b
  csrwr   $t0, LOONGARCH_CSR_DMWIN0

#ifdef CONFIG_BUILD_FLAT
  /* Set Direct Mapping Window1: 0x0000 xxxx xxxx xxxx, PLV0, no cache for devices */
  li.d		$t0, 0x0000000000000001
	csrwr		$t0, LOONGARCH_CSR_DMWIN1

  /* Disable all interrupts and set initial value in LOONGARCH_CSR_CRMD */

	li.w		$t0, 0xb0                   # DATM=0 1, DATF=01, PG=1, DA=0, IE=0, PLV=00
	csrwr		$t0, LOONGARCH_CSR_CRMD
#elif defined CONFIG_BUILD_KERNEL

  /* Disable all interrupts and set initial value in LOONGARCH_CSR_CRMD */

	li.w		$t0, 0xa8                   # DATM=0 1, DATF=01, PG=0, DA=1, IE=0, PLV=00
	csrwr		$t0, LOONGARCH_CSR_CRMD
#endif

  la.abs  $t0, __trap_vec
  csrwr   $t0, LOONGARCH_CSR_EENTRY

  /* Jump to qemu_la_start */
  bl  qemu_la_start

  /* We shouldn't return from _start */

  .global _init
  .global _fini

_init:
_fini:

  /* These don't have to do anything since we use init_array/fini_array. */

  ertn
