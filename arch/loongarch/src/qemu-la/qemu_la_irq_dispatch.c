/****************************************************************************
 * arch/loongarch/src/qemu-la/qemu_la_irq_dispatch.c
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
#include <larchintrin.h>
#include <nuttx/config.h>

#include <stdint.h>
#include <assert.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <sys/types.h>

#include "loongarch_internal.h"
#include "hardware/qemu_la_memorymap.h"
#include "hardware/qemu_la_3A5000irq.h"
#include "hardware/qemu_la_7A1000irq.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define LA_ESTAT_IS_MASK    0x1fff
#define LA_ESTAT_ECODE_MASK 0x3f

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * loongarch_dispatch_irq
 ****************************************************************************/

void *loongarch_dispatch_irq(uintptr_t estat_val, uintptr_t *regs)
{
  int irq = (estat_val >> CSR_ESTAT_EXC_SHIFT) & LA_ESTAT_ECODE_MASK;

  if(irq==0){
    irq = LOONGARCH_IRQ_BASE;

    int irq_bit = estat_val & LA_ESTAT_IS_MASK;

    while(irq_bit != 1){
      irq_bit >>= 1;
      irq++;
    }
  }

  /* Firstly, check if the irq is hardware interrupt, uart interrupt is mapped to HWI0 */

  if (LOONGARCH_IRQ_HWI1 == irq)
    {
      irq += QEMU_LA_EXTIRQ_GAP;
      
      uintptr_t val = iocsr_read64(LOONGARCH_IOCSR_EXTIOI_ISR_BASE);

      /* Add the value to nuttx irq which is offset to the mext */
      while(val!=1){
        val>>=1;
        irq++;
      }      
    }

  /* LOONGARCH_IRQ_HWI1 means no interrupt */

  if (LOONGARCH_IRQ_HWI1 != irq)
    {
      /* Deliver the IRQ */

      regs = loongarch_doirq(irq, regs);
    }

  if (LOONGARCH_MAX_INTERRUPT < irq)
    {
      /* Then write PLIC_CLAIM to clear pending in PLIC */

      // putreg32(irq - RISCV_IRQ_EXT, QEMU_RV_PLIC_CLAIM);

      /* ack LS3A5000*/
      iocsr_write64(1 << (irq - LOONGARCH_IRQ_HWI1 - QEMU_LA_EXTIRQ_GAP), LOONGARCH_IOCSR_EXTIOI_ISR_BASE);

      /* ack LS7A1000*/
      iocsr_write64(1<<(irq - LOONGARCH_IRQ_HWI1 - QEMU_LA_EXTIRQ_GAP), LS7A_INT_CLEAR_REG);
    }
    // printf("estat: %08x\n",READ_CSR(LOONGARCH_CSR_ESTAT));

  return regs;
}
