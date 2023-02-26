/****************************************************************************
 * arch/loongarch/src/qemu-la/hardware/qemu_la_7A1000irq.h
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

#ifndef __ARCH_LOONGARCH_SRC_QEMU_LA_HARDWARE_QEMU_LA_7A1000IRQ_H
#define __ARCH_LOONGARCH_SRC_QEMU_LA_HARDWARE_QEMU_LA_7A1000IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

// #include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* LS7A1000 interrupt controller registers */
#define LS7A_PCH_REG_BASE       0x10000000UL
  
#define LS7A_INT_MASK_REG       LS7A_PCH_REG_BASE + 0x020
#define LS7A_INT_EDGE_REG       LS7A_PCH_REG_BASE + 0x060
#define LS7A_INT_CLEAR_REG      LS7A_PCH_REG_BASE + 0x080
#define LS7A_INT_HTMSI_VEC_REG  LS7A_PCH_REG_BASE + 0x200
#define LS7A_INT_STATUS_REG     LS7A_PCH_REG_BASE + 0x3a0
#define LS7A_INT_POL_REG        LS7A_PCH_REG_BASE + 0x3e0

#endif /* __ARCH_LOONGARCH_SRC_QEMU_LA_HARDWARE_QEMU_LA_7A1000IRQ_H */