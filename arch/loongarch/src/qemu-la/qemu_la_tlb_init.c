/****************************************************************************
 * arch/loongarch/src/qemu-la/qemu_la_tlb_init.c
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
#include <nuttx/arch.h>

#include <stdint.h>
#include <assert.h>
#include <debug.h>

#include "loongarch_internal.h"
#include "loongarch_mmu.h"

/****************************************************************************
 * Extern Function Declarations
 ****************************************************************************/

extern void tlb_refill_entry(void);

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: qemu_la_tlb_init
 *
 * Description:
 *  Init tlb settings when using CONFIG_BUILD_KERNEL. 
 *
 ****************************************************************************/

void qemu_la_tlb_init(void){
    /* STLB is used for kernel, which only contains tlb entry of fixed page size */

    /* set stlb page size, the pages size that equals to STLB.PS falls in STLB, otherwise MTLB */
    WRITE_CSR64(LOONGARCH_CSR_STLBPGSIZE, LA_MMU_32M_PAGE_SHIFT);

    /* set tlb refill page size, this may be not needed? */
    WRITE_CSR64(LOONGARCH_CSR_TLBREHI,
                (READ_CSR64(LOONGARCH_CSR_TLBREHI) & ~CSR_TLBREHI_PS) | (LA_MMU_32M_PAGE_SHIFT << CSR_TLBIDX_PS_SHIFT));

    // /* set tlb refill page size, this may be not needed? */
    // WRITE_CSR64(LOONGARCH_CSR_TLBIDX,
    //             (READ_CSR64(LOONGARCH_CSR_TLBIDX) & ~CSR_TLBIDX_PS) | (LA_MMU_32M_PAGE_SHIFT << CSR_TLBIDX_PS_SHIFT));

    /* setup tlb refill handler */
    WRITE_CSR64(LOONGARCH_CSR_TLBRENTRY, tlb_refill_entry);
}