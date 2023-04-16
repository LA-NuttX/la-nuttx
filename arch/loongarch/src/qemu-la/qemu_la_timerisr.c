/****************************************************************************
 * arch/loongarch/src/qemu-la/qemu_la_timerisr.c
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

#include <assert.h>
#include <stdint.h>
#include <time.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/clock.h>
#include <nuttx/spinlock.h>
#include <nuttx/timers/arch_alarm.h>
#include <arch/board/board.h>

#include "loongarch_internal.h"
#include "loongarch_timer.h"
#include "loongarch_percpu.h"
#include "hardware/qemu_la_memorymap.h"
#include "hardware/qemu_la_clint.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define TIMER_FREQ 100000000
#define TICK_COUNT (100000000 / TICK_PER_SEC)
/**
 *  Get the frequency by cpucfg instruction:
 *   li.d    $t0, 0x4
 *   cpucfg  $t1, $t0
 *   li.d    $t0, 0x5
 *   cpucfg  $t2, $t0
 * 
 */


#ifdef CONFIG_BUILD_KERNEL

/****************************************************************************
 * Private Data
 ****************************************************************************/

static uint32_t g_mtimer_cnt = 0;
static uint32_t g_stimer_pending = false;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: qemu_rv_ssoft_interrupt
 *
 * Description:
 *   This function is S-mode software interrupt handler to proceed
 *   the OS timer
 *
 ****************************************************************************/

static int qemu_rv_ssoft_interrupt(int irq, void *context, void *arg)
{
  /* Cleaer Supervisor Software Interrupt */
  assert(0);
  // CLEAR_CSR(sip, SIP_SSIP);

  if (g_stimer_pending)
    {
      g_stimer_pending = false;

      /* Proceed the OS timer */

      nxsched_process_timer();
    }
#ifdef CONFIG_SMP
  else
    {
      /* We assume IPI has been issued */

      riscv_pause_handler(irq, context, arg);
    }
#endif

  return 0;
}

/****************************************************************************
 * Name: qemu_rv_reload_mtimecmp
 *
 * Description:
 *   This function is called during start-up to initialize mtimecmp
 *   for CONFIG_BUILD_KERNEL=y
 *
 ****************************************************************************/

static void qemu_rv_reload_mtimecmp(void)
{
  assert(0);
  // uint64_t current;
  // uint64_t next;

  // current = READ_CSR(time);
  // next = current + TICK_COUNT;
  // putreg64(next, QEMU_RV_CLINT_MTIMECMP);
}

#endif /* CONFIG_BUILD_KERNEL */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_timer_initialize
 *
 * Description:
 *   This function is called during start-up to initialize
 *   the timer interrupt.
 *
 ****************************************************************************/

void up_timer_initialize(void)
{
  struct oneshot_lowerhalf_s *lower = loongarch_timer_initialize(LOONGARCH_IRQ_TIMER, TIMER_FREQ);

  DEBUGASSERT(lower);

  up_alarm_set_lowerhalf(lower);
}

#ifdef CONFIG_BUILD_KERNEL

/****************************************************************************
 * Name: up_mtimer_initialize
 *
 * Description:
 *   This function is called during start-up to initialize the M-mode timer
 *
 ****************************************************************************/

void up_mtimer_initialize(void)
{
  assert(0);
  // uintptr_t irqstacktop = riscv_percpu_get_irqstack();

  // /* Set the irq stack base to mscratch */
  // WRITE_CSR(mscratch,
  //           irqstacktop - STACK_ALIGN_DOWN(CONFIG_ARCH_INTERRUPTSTACK));

  // /* NOTE: we do not attach a handler for mtimer,
  //  * because it is handled in the exception_m directly
  //  */

  // up_enable_irq(RISCV_IRQ_MTIMER);
  // qemu_rv_reload_mtimecmp();
}

/****************************************************************************
 * Name: qemu_rv_mtimer_interrupt
 *
 * Description:
 *   In RISC-V with S-mode, M-mode timer must be handled in M-mode
 *   This function is called from exception_m in M-mode directly
 *
 ****************************************************************************/

void qemu_rv_mtimer_interrupt(void)
{
  assert(0);
  // uint64_t current;
  // uint64_t next;

  // /* Update mtimercmp */

  // current = getreg64(QEMU_RV_CLINT_MTIMECMP);
  // next = current + TICK_COUNT;
  // putreg64(next, QEMU_RV_CLINT_MTIMECMP);

  // g_mtimer_cnt++;
  // g_stimer_pending = true;

  // /* Post Supervisor Software Interrupt */

  // SET_CSR(sip, SIP_SSIP);
}

#endif /* CONFIG_BUILD_KERNEL */
