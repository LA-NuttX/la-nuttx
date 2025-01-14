/****************************************************************************
 * arch/loongarch/include/qemu-la/irq.h
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

#ifndef __ARCH_LOONGARCH_INCLUDE_QEMU_LA_IRQ_H
#define __ARCH_LOONGARCH_INCLUDE_QEMU_LA_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Map LOONGARCH exception code to NuttX IRQ */
#define QEMU_LA_EXTIRQ_GAP  (10)
#define UART0_PIC_IRQ       (2)
#define QEMU_LA_IRQ_UART0   (LOONGARCH_IRQ_HWI1 + QEMU_LA_EXTIRQ_GAP + UART0_PIC_IRQ) /* 79 */

#define NR_IRQS (QEMU_LA_IRQ_UART0 + 1)

#endif /* __ARCH_LOONGARCH_INCLUDE_QEMU_LA_IRQ_H */
