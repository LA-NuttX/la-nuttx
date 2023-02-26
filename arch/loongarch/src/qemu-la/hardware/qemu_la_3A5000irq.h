/****************************************************************************
 * arch/loongarch/src/qemu-la/hardware/qemu_la_3A5000irq.h
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

#ifndef __ARCH_LOONGARCH_SRC_QEMU_LA_HARDWARE_QEMU_LA_3A5000IRQ_H
#define __ARCH_LOONGARCH_SRC_QEMU_LA_HARDWARE_QEMU_LA_3A5000IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

// #include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* LS3A5000 extend io interrupt controller registers */
#define LOONGARCH_IOCSR_EXTIOI_EN_BASE          0x1600
#define LOONGARCH_IOCSR_EXTIOI_ISR_BASE         0x1800
#define LOONGARCH_IOCSR_EXTIOI_MAP_BASE         0x14c0
#define LOONGARCH_IOCSR_EXTIOI_ROUTE_BASE       0x1c00
#define LOONGARCH_IOCSR_EXRIOI_NODETYPE_BASE    0x14a0

// #define QEMU_RV_PLIC_PRIORITY    (QEMU_RV_PLIC_BASE + 0x000000)
// #define QEMU_RV_PLIC_PENDING1    (QEMU_RV_PLIC_BASE + 0x001000)

// #ifdef CONFIG_ARCH_USE_S_MODE
// #  define QEMU_RV_PLIC_ENABLE1   (QEMU_RV_PLIC_BASE + 0x002080)
// #  define QEMU_RV_PLIC_ENABLE2   (QEMU_RV_PLIC_BASE + 0x002084)
// #  define QEMU_RV_PLIC_THRESHOLD (QEMU_RV_PLIC_BASE + 0x201000)
// #  define QEMU_RV_PLIC_CLAIM     (QEMU_RV_PLIC_BASE + 0x201004)
// #else
// #  define QEMU_RV_PLIC_ENABLE1   (QEMU_RV_PLIC_BASE + 0x002000)
// #  define QEMU_RV_PLIC_ENABLE2   (QEMU_RV_PLIC_BASE + 0x002004)
// #  define QEMU_RV_PLIC_THRESHOLD (QEMU_RV_PLIC_BASE + 0x200000)
// #  define QEMU_RV_PLIC_CLAIM     (QEMU_RV_PLIC_BASE + 0x200004)
// #endif

#endif /* __ARCH_LOONGARCH_SRC_QEMU_LA_HARDWARE_QEMU_LA_3A5000IRQ_H */
