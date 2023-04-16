/****************************************************************************
 * arch/loongarch/src/common/loongarch_getnewintctx.c
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
#include <stdio.h>
#include <assert.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/irq.h>

#include <arch/mode.h>

#include "loongarch_internal.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: loongarch_get_newprmd
 *
 * Description:
 *   Return initial prmd value when a task is created.
 *
 ****************************************************************************/

uintptr_t loongarch_get_newprmd(void)
{
  /* Set machine previous privilege mode to privileged mode. Regardless of
   * how NuttX is configured and of what kind of thread is being started.
   * That is because all threads, even user-mode threads will start in
   * kernel trampoline at nxtask_start() or pthread_start().
   * The thread's privileges will be dropped before transitioning to
   * user code. Also set machine / supervisor previous interrupt enable.
   *
   * Mask the bits which should be preserved (from ISA spec)
   */

  
//   uintptr_t status = READ_CSR(CSR_STATUS);

//   status &= MSTATUS_WPRI;

//   return (status | STATUS_PPP | STATUS_SUM | STATUS_PIE
// #ifdef CONFIG_ARCH_FPU
//                  | MSTATUS_FS_INIT
// #endif
  // );
  assert(0);
  uintptr_t prmd = READ_CSR64(LOONGARCH_CSR_PRMD);

  return (prmd | CSR_PRMD_PIE | 0x00);

  return 0;
}
