/****************************************************************************
 * arch/loongarch/src/qemu-la/qemu_la_start.c
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

#include <nuttx/init.h>
#include <nuttx/arch.h>
#include <arch/board/board.h>

#include "loongarch_internal.h"
#include "chip.h"

#ifdef CONFIG_BUILD_KERNEL
#  include "qemu_la_tlb_init.h"
#  include "qemu_la_mm_init.h"
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifdef CONFIG_DEBUG_FEATURES
#define showprogress(c) up_putc(c)
#else
#define showprogress(c)
#endif

// #if defined (CONFIG_BUILD_KERNEL) && !defined (CONFIG_ARCH_USE_S_MODE)
// #  error "Target requires kernel in S-mode, enable CONFIG_ARCH_USE_S_MODE"
// #endif

/****************************************************************************
 * Extern Function Declarations
 ****************************************************************************/

#ifdef CONFIG_BUILD_KERNEL
extern void __trap_vec(void);
extern void __trap_vec_m(void);
extern void up_mtimer_initialize(void);
#endif

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* NOTE: g_idle_topstack needs to point the top of the idle stack
 * for CPU0 and this value is used in up_initial_state()
 */

uintptr_t g_idle_topstack = QEMU_LA_IDLESTACK_TOP;

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: qemu_la_start
 ****************************************************************************/

#ifdef CONFIG_BUILD_KERNEL
void qemu_la_start_second_stage(int hartid)
#else
void qemu_la_start(int hartid)
#endif
{
  /* Configure FPU */

  loongarch_fpuconfig();

  if (hartid > 0)
  {
    goto cpux;
  }

  showprogress('A');

#ifdef USE_EARLYSERIALINIT
  up_earlyserialinit();
#endif

  showprogress('B');

  /* Do board initialization */

  showprogress('C');

#ifdef CONFIG_BUILD_KERNEL
  /* init tlb */
  qemu_la_tlb_init();

  /* Setup page tables for kernel and enable MMU */
  qemu_la_mm_init();
#endif

  /* Call nx_start() */

  nx_start();

cpux:

#ifdef CONFIG_SMP
  riscv_cpu_boot(mhartid);
#endif

  while (true)
    {
      asm("idle 0");
    }
}

#ifdef CONFIG_BUILD_KERNEL

/****************************************************************************
 * Name: qemu_la_start
 ****************************************************************************/

void qemu_la_start(int hartid)
{
  /* NOTE: still in plv0 */

  if (0 == hartid)
    {
      /* Initialize the per CPU areas */

      loongarch_percpu_add_hart(hartid);
    }
  
  /* TODO: Add memory protection initialization code here later */
  
  qemu_la_start_second_stage(hartid);


  /* Disable MMU and enable PMP */
  
  // WRITE_CSR(satp, 0x0);
  // WRITE_CSR(pmpaddr0, 0x3fffffffffffffull);
  // WRITE_CSR(pmpcfg0, 0xf);

  /* Set exception and interrupt delegation for S-mode */

  // WRITE_CSR(medeleg, 0xffff);
  // WRITE_CSR(mideleg, 0xffff);

  /* Allow to write satp from S-mode */

  // CLEAR_CSR(mstatus, MSTATUS_TVM);

  /* Set mstatus to S-mode and enable SUM */

  // CLEAR_CSR(mstatus, ~MSTATUS_MPP_MASK);
  // SET_CSR(mstatus, MSTATUS_MPPS | SSTATUS_SUM);

  /* Set the trap vector for S-mode */

  // WRITE_CSR(stvec, (uintptr_t)__trap_vec);

  /* Set the trap vector for M-mode */

  // WRITE_CSR(mtvec, (uintptr_t)__trap_vec_m);

  // if (0 == hartid)
  //   {
  //     /* Only the primary CPU needs to initialize mtimer
  //      * before entering to S-mode
  //      */

  //     up_mtimer_initialize();
  //   }

  /* Set mepc to the entry */

  // WRITE_CSR(mepc, (uintptr_t)qemu_rv_start_s);

  /* Set a0 to mhartid explicitly and enter to S-mode */

  // asm volatile (
  //     "mv a0, %0 \n"
  //     "mret \n"
  //     :: "r" (hartid)
  // );
}
#endif

void loongarch_serialinit(void)
{
  up_serialinit();
}
