/****************************************************************************
 * arch/risc-v/src/common/supervisor/loongarch_perform_syscall.c
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

#include <stdint.h>

#include "loongarch_internal.h"
#include "group/group.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void *loongarch_perform_syscall(uintptr_t *regs)
{
  /* Set up the interrupt register set needed by swint() */

  CURRENT_REGS = regs;

  /* Run the system call handler (swint) */

  loongarch_swint(0, regs, NULL);

#ifdef CONFIG_ARCH_ADDRENV
  if (regs != CURRENT_REGS)
    {
      /* Make sure that the address environment for the previously
       * running task is closed down gracefully (data caches dump,
       * MMU flushed) and set up the address environment for the new
       * thread at the head of the ready-to-run list.
       */

      group_addrenv(NULL);
    }
#endif

  if (regs != CURRENT_REGS)
    {
      /* Restore the cpu lock */

      restore_critical_section();

      /* If a context switch occurred while processing the interrupt then
       * CURRENT_REGS may have change value.  If we return any value
       * different from the input regs, then the lower level will know
       * that a context switch occurred during interrupt processing.
       */

      regs = (uintptr_t *)CURRENT_REGS;
    }

  CURRENT_REGS = NULL;

  return regs;
}
