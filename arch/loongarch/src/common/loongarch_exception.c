/****************************************************************************
 * arch/loongarch/src/common/loongarch_exception.c
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
#include <assert.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>

#include "loongarch_internal.h"
#include "chip.h"

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const char *g_reasons_str[LOONGARCH_MAX_EXCEPTION + 1] =
{
  "Only when CSR.ECFG.VS=0, it means it is an INTerrupt",
  "Page Invalid exception for Load operation",
  "Page Invalid exception for Store operation",
  "Page Invalid exception for Fetch operation",
  "Page Modification Exception",
  "Page Non-Readable exception",
  "Page Non-eXecutable exception",
  "Page Privilege level Illegal exception",
  "ADdress error Exception for Fetching/Memory access instructions",
  "Address aLignment fault Exception",
  "Bound Check Exception",
  "SYStem call exception",
  "BReaKpoint exception",
  "Instruction Non-defined Exception",
  "Instruction Privilege error Exception",
  "Floating-Point instruction Disable exception",
  "128-bit vector (SIMD instructions) eXpansion instruction Disable exception",
  "256-bit vector (Advanced SIMD instructions) eXpansion instruction Disable exception",
  "(Vector) Floating-Point error Exception",
  "WatchPoint Exception for Fetch/Memory load/Memory store watchpoint",
  "Binary Translation expansion instruction Disable exception",
  "Binary Translation related exceptions",
  "Guest Sensitive Privileged Resource exception",
  "HyperVisor Call exception",
  "Guest CSR Software/Hardware Change exception"
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: loongarch_exception
 *
 * Description:
 *   This is the exception handler.
 *
 ****************************************************************************/

int loongarch_exception(int ecode, void *regs, void *args)
{
  _alert("EXCEPTION: %s. ECODE: %" PRIxREG ", ESTAT: %" PRIxREG ", BADV: %" PRIxREG "\n",
        ecode > LOONGARCH_MAX_EXCEPTION? "Unknown" : g_reasons_str[ecode],
        ecode, READ_CSR64(LOONGARCH_CSR_ESTAT), READ_CSR64(LOONGARCH_CSR_BADV));

  _alert("PANIC!!! Exception = %" PRIxREG "\n", ecode);
  up_irq_save();
  PANIC();
  return 0;
}

/****************************************************************************
 * Name: loongarch_exception_attach
 *
 * Description:
 *   Attach standard exception with suitable handler
 *
 ****************************************************************************/

void loongarch_exception_attach(void)
{
  irq_attach(LOONGARCH_XCPT_PIL, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_PIS, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_PIF, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_PME, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_PNR, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_PNX, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_PPI, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_ADE, loongarch_exception, NULL);
  
  irq_attach(LOONGARCH_XCPT_BCE, loongarch_exception, NULL);

  irq_attach(LOONGARCH_XCPT_BRK, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_INE, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_IPE, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_FPD, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_SXD, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_ASXD, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_FPE, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_WPE, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_BTD, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_BTE, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_GSPR, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_HVC, loongarch_exception, NULL);
  irq_attach(LOONGARCH_XCPT_GCC, loongarch_exception, NULL);

#ifdef CONFIG_LOONGARCH_MISALIGNED_HANDLER
  assert(0);
#else
  irq_attach(LOONGARCH_XCPT_ALE, loongarch_exception, NULL);
#endif

  /* Attach the syscall interrupt handler */

  irq_attach(LOONGARCH_XCPT_SYS, loongarch_swint, NULL);

#ifdef CONFIG_SMP
  assert(0);
#else
  irq_attach(LOONGARCH_IRQ_SOFT0, loongarch_exception, NULL);
  irq_attach(LOONGARCH_IRQ_SOFT1, loongarch_exception, NULL);
#endif
}
