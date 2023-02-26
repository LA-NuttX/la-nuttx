/****************************************************************************
 * arch/risc-v/src/qemu-rv/qemu_rv_irq.c
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
#include <stdio.h>
#include <assert.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/irq.h>

#include "loongarch_internal.h"
#include "chip.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_irqinitialize
 ****************************************************************************/

void up_irqinitialize(void)
{

  /* Disable all the interrupts*/

  up_irq_save();

  /* ====LS3A5000 extend io interrupt controller initialization */

  // // /*    Enable the UART0_PIC_IRQ extend io interrupt */
  // iocsr_write64(0x1 << UART0_PIC_IRQ, LOONGARCH_IOCSR_EXTIOI_EN_BASE);

  /*    Map extioi[31:0] to cpu irq pin INT1, other to INT0*/
  iocsr_write64(0x2, LOONGARCH_IOCSR_EXTIOI_MAP_BASE);

  /*    Map extioi IRQ 0-7 route to core 0, node type 0 */
  iocsr_write64(0x0, LOONGARCH_IOCSR_EXTIOI_ROUTE_BASE);

  /*    Set nodetype0=1, always trigger at node 0 */
  iocsr_write64(0x1, LOONGARCH_IOCSR_EXRIOI_NODETYPE_BASE);
  /* ====LS3A5000 extend io interrupt initialization Complete*/

  /* ====LS7A1000 interrupt controller initialization */

  // // /*    Enable uart0 */
  // putreg64(~(0x1 << UART0_PIC_IRQ), LS7A_INT_MASK_REG);

  /*    Set trigger mode to level trigger*/
  putreg64(0x0 << UART0_PIC_IRQ, LS7A_INT_EDGE_REG);

  /*    Set high level trigger*/
  putreg64(0x0, LS7A_INT_POL_REG);

  /*    Route to the same irq in extioi */
  putreg8(UART0_PIC_IRQ, LS7A_INT_HTMSI_VEC_REG + UART0_PIC_IRQ);

  /* ====LS7A1000 interrupt controller initialization Complete*/

  /* Colorize the interrupt stack for debug purposes */

#if defined(CONFIG_STACK_COLORATION) && CONFIG_ARCH_INTERRUPTSTACK > 15
  size_t intstack_size = (CONFIG_ARCH_INTERRUPTSTACK & ~15);
  loongarch_stack_color(g_intstackalloc, intstack_size);
#endif

  /* Attach the common interrupt handler */

  loongarch_exception_attach();

#ifdef CONFIG_SMP
  /* Clear Loongarch_IPI for CPU0 */

  putreg32(0, RISCV_IPI);

  up_enable_irq(RISCV_IRQ_SOFT);
#endif

#ifndef CONFIG_SUPPRESS_INTERRUPTS

  /* And finally, enable interrupts */

  up_irq_enable();
#endif
}

/****************************************************************************
 * Name: up_disable_irq
 *
 * Description:
 *   Disable the IRQ specified by 'irq'
 *
 ****************************************************************************/

void up_disable_irq(int irq)
{
  assert(0);
  //uart的irq号应该如何确定？riscv的37的意义是什么？
  // int extirq;

  // if (irq == RISCV_IRQ_SOFT)
  //   {
  //     /* Read m/sstatus & clear machine software interrupt enable in m/sie */

  //     CLEAR_CSR(CSR_IE, IE_SIE);
  //   }
  // else if (irq == RISCV_IRQ_TIMER)
  //   {
  //     /* Read m/sstatus & clear timer interrupt enable in m/sie */

  //     CLEAR_CSR(CSR_IE, IE_TIE);
  //   }
  // else if (irq > RISCV_IRQ_EXT)
  //   {//此处应当是核内硬中断，再查到有外部中断
  //     extirq = irq - RISCV_IRQ_EXT;

  //     /* Clear enable bit for the irq */

  //     if (0 <= extirq && extirq <= 63)
  //       {
  //         modifyreg32(QEMU_RV_PLIC_ENABLE1 + (4 * (extirq / 32)),
  //                     1 << (extirq % 32), 0);
  //       }
  //     else
  //       {
  //         ASSERT(false);
  //       }
  //   }
}

/****************************************************************************
 * Name: up_enable_irq
 *
 * Description:
 *   Enable the IRQ specified by 'irq'
 *
 ****************************************************************************/

void up_enable_irq(int irq)
{
  int extirq;

  if (irq >=LOONGARCH_IRQ_SOFT0 && irq<= LOONGARCH_IRQ_IPI)
    {
      /* Set interrupt enable in ECFG */

      SET_CSR(LOONGARCH_CSR_ECFG, 1<<(irq-LOONGARCH_IRQ_BASE));

    }else if (irq > LOONGARCH_MAX_INTERRUPT && irq < NR_IRQS){

      /* external interrupts are mapped to LOONGARCH_IRQ_HWI1*/
      
      SET_CSR(LOONGARCH_CSR_ECFG, 1<<(LOONGARCH_IRQ_HWI1-LOONGARCH_IRQ_BASE));     

      /* Set enable bit for the extirq on LS3A5000 and LS7A1000*/
      extirq = irq - LOONGARCH_IRQ_HWI1 - QEMU_LA_EXTIRQ_GAP;

      if(extirq==UART0_PIC_IRQ){

          /* LS3A5000: Enable the UART0_PIC_IRQ extend io interrupt */
          modifyreg64(LOONGARCH_IOCSR_EXTIOI_EN_BASE, 0, 0x1 << UART0_PIC_IRQ);

          /* LS7A1000: Enable uart0 */
          modifyreg64(LS7A_INT_MASK_REG, 0x1 << UART0_PIC_IRQ, 0);

      }else{
          ASSERT(false);
      }

    }else{
      ASSERT(false);
    }
}

irqstate_t up_irq_enable(void)
{
  /* Clear estat, since enabling external interrupts might cause irq pending */
  CLEAR_CSR(LOONGARCH_CSR_ESTAT, CSR_ESTAT_IS);

  /* Set ecfg.vs=0 */
  CLEAR_CSR(LOONGARCH_CSR_ECFG, CSR_ECFG_VS);

  // /* Enable interrupts in csr.ecfg */
  // SET_CSR(LOONGARCH_CSR_ECFG, CSR_ECFG_IM);

  /* Read and enable global interrupts (IE) in csr.crmd */
  irqstate_t oldstat;

  oldstat = READ_AND_SET_CSR(LOONGARCH_CSR_CRMD, CSR_CRMD_IE);

  return oldstat;
}
