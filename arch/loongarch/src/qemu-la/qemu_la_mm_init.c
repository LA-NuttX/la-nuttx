/****************************************************************************
 * arch/loongarch/src/qemu-la/qemu_la_mm_init.c
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

#include <arch/board/board_memorymap.h>

#include "qemu_la_memorymap.h"

#include "loongarch_internal.h"
#include "loongarch_mmu.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define KERNEL_ASID (0)

/* PWCTL0 areas */
#define PT_BASE     (14)
#define PT_WIDTH    (11)
#define DIR1_BASE   (PT_BASE + PT_WIDTH) /* 25 */
#define DIR1_WIDTH  (11)
#define DIR2_BASE   (0) /* 5 bit field is not long enough for number 36, thus not used */
#define DIR2_WIDTH  (0) /* 5 bit field is not long enough for number 36, thus not used */
#define PTEWIDTH    (0) /* 64 bit width */

/* PWCTL1 areas */
#define DIR3_BASE   (DIR1_BASE + DIR1_WIDTH) /* 36 */
#define DIR3_WIDTH  (11)
#define DIR4_BASE   (0)
#define DIR4_WIDTH  (0)

/* Map the whole I/O memory with vaddr = paddr mappings */

#define MMU_IO_BASE     (0x10000000)
#define MMU_IO_SIZE     (0x10000000)

/* Physical and virtual addresses to page tables (vaddr = paddr mapping) */

#define PGT_L1_PBASE    (uintptr_t)&m_l1_pgtable
#define PGT_L2_PBASE    (uintptr_t)&m_l2_pgtable

#define PGT_L1_VBASE    PGT_L1_PBASE
#define PGT_L2_VBASE    PGT_L2_PBASE

#define PGT_L1_SIZE     (2048)  /* Enough to map 2048*64 GiB */
#define PGT_L2_SIZE     (2048)  /* Enough to map 64 GiB */

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Kernel mappings simply here, mapping is vaddr=paddr, and PGDL points to m_l1_pgtable */

static uint64_t         m_l1_pgtable[PGT_L1_SIZE] locate_data(".pgtables");
static uint64_t         m_l2_pgtable[PGT_L2_SIZE] locate_data(".pgtables");

/* Kernel mappings (L1 base) */

uintptr_t               g_kernel_mappings  = PGT_L1_VBASE;
uintptr_t               g_kernel_pgt_pbase = PGT_L1_PBASE;


/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: qemu_la_pagewalk_control_init
 *
 * Description:
 *   Initialize pagewalk control CSR
 *
 ****************************************************************************/

static void qemu_la_pagewalk_control_init(void){
  uint64_t pgctl0_val = DIR1_WIDTH<<CSR_PWCTL0_DIR1WIDTH_SHIFT | DIR1_BASE<<CSR_PWCTL0_DIR1BASE_SHIFT| \
                        PT_WIDTH<<CSR_PWCTL0_PTWIDTH_SHIFT | PT_BASE<<CSR_PWCTL0_PTBASE_SHIFT;
  uint64_t pgctl1_val = DIR3_WIDTH<<CSR_PWCTL1_DIR3WIDTH_SHIFT | DIR3_BASE<<CSR_PWCTL1_DIR3BASE_SHIFT;

  WRITE_CSR64(LOONGARCH_CSR_PWCTL0, pgctl0_val);
  WRITE_CSR64(LOONGARCH_CSR_PWCTL1, pgctl1_val);
}


/****************************************************************************
 * Name: map_region
 *
 * Description:
 *   Map a region of physical memory to the L3 page table
 *
 * Input Parameters:
 *   paddr - Beginning of the physical address mapping
 *   vaddr - Beginning of the virtual address mapping
 *   size - Size of the region in bytes
 *   mmuflags - The MMU flags to use in the mapping
 *
 ****************************************************************************/

static void map_region(uintptr_t paddr, uintptr_t vaddr, size_t size,
                       uint32_t mmuflags)
{
  assert(0);
  return;
  // uintptr_t endaddr;
  // uintptr_t l3pbase;
  // int npages;
  // int i;
  // int j;

  // /* How many pages */

  // npages = (size + RV_MMU_PAGE_MASK) >> RV_MMU_PAGE_SHIFT;
  // endaddr = vaddr + size;

  // for (i = 0; i < npages; i += RV_MMU_PAGE_ENTRIES)
  //   {
  //     /* See if a L3 mapping exists ? */

  //     l3pbase = mmu_pte_to_paddr(mmu_ln_getentry(2, PGT_L2_VBASE, vaddr));
  //     if (!l3pbase)
  //       {
  //         /* No, allocate 1 page, this must not fail */

  //         // l3pbase = slab_alloc();
  //         DEBUGASSERT(l3pbase);

  //         /* Map it to the L3 table */

  //         mmu_ln_setentry(2, PGT_L2_VBASE, l3pbase, vaddr, MMU_UPGT_FLAGS);
  //       }

  //     /* Then add the L3 mappings */

  //     for (j = 0; j < RV_MMU_PAGE_ENTRIES && vaddr < endaddr; j++)
  //       {
  //         mmu_ln_setentry(3, l3pbase, paddr, vaddr, mmuflags);
  //         paddr += RV_MMU_L3_PAGE_SIZE;
  //         vaddr += RV_MMU_L3_PAGE_SIZE;
  //       }
  //   }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: qemu_la_kernel_mappings
 *
 * Description:
 *  Setup kernel mappings when usinc CONFIG_BUILD_KERNEL. Sets up the kernel
 *  MMU mappings.
 *
 ****************************************************************************/

void qemu_la_kernel_mappings(void)
{

  /* Begin mapping memory to MMU; note that at this point the MMU is not yet
   * active, so the page table virtual addresses are actually physical
   * addresses and so forth.
   */

  /* Map I/O region, use 8 L2 entries (i.e. 8 * 32MB = 256MB address space) */

  binfo("map I/O regions\n");
  mmu_ln_map_region(2, PGT_L2_VBASE, MMU_IO_BASE, MMU_IO_BASE, MMU_IO_SIZE, MMU_IO_FLAGS_HUGE_PLV0);

  /* Map the kernel text and data for L2/L3 */

  binfo("map kernel text\n");
  mmu_ln_map_region(2, PGT_L2_VBASE, KFLASH_START, KFLASH_START, KFLASH_SIZE, MMU_KTEXT_FLAGS);

  binfo("map kernel data\n");
  mmu_ln_map_region(2, PGT_L2_VBASE, KSRAM_START, KSRAM_START, KSRAM_SIZE, MMU_KDATA_FLAGS);

  /* Connect the L1 and L2 page tables for the kernel text and data */
  binfo("connect the L1 and L2 page tables\n");
  mmu_ln_setentry(1, PGT_L1_VBASE, PGT_L2_VBASE, PGT_L2_PBASE, MMU_DIRECTORY_FLAGS);

  /* Map the page pool */

  binfo("map the page pool\n");
  mmu_ln_map_region(2, PGT_L2_VBASE, PGPOOL_START, PGPOOL_START, PGPOOL_SIZE, MMU_KDATA_FLAGS);
}

/****************************************************************************
 * Name: qemu_la_mm_init
 *
 * Description:
 *  Setup kernel mappings when using CONFIG_BUILD_KERNEL. Sets up kernel MMU
 *  mappings. Function also sets the first address environment (satp value).
 *
 ****************************************************************************/

void qemu_la_mm_init(void)
{
  /* set kernel ASID = 0 */
  qemu_la_set_asid(KERNEL_ASID);

  /* set pgd for root page table */
  qemu_la_set_pgdl(g_kernel_pgt_pbase);

  /* set up pwch, pwcl */
  qemu_la_pagewalk_control_init();

  /* map the kernel */
  qemu_la_kernel_mappings();

  /* Enable MMU (note: system is still in plv0) */
  binfo("root page table paddr: pgdl=0x%lx\n", g_kernel_pgt_pbase);

  mmu_enable();
}
