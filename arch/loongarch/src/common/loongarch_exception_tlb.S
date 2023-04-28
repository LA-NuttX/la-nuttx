/****************************************************************************
 * arch/loongarch/src/common/loongarch_exception_tlb.c
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

#include <arch/arch.h>
#include <arch/irq.h>
#include <arch/mode.h>

#include <sys/types.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


 /****************************************************************************
 * Public Symbols
 ****************************************************************************/

/****************************************************************************
 * Name: exception_tlb
 *
 * Description:
 *   Handles tlb refill.
 *
 ****************************************************************************/

  .section exception_tlb_refill_section
  .global tlb_refill_entry
  .align  8

tlb_refill_entry:
  /* save t0 in TLBRSAVE */
  csrwr	$t0, LOONGARCH_CSR_TLBRSAVE
  csrwr $t1, LOONGARCH_CSR_KS8
  csrwr $t2, LOONGARCH_CSR_KS7
  csrwr $t3, LOONGARCH_CSR_KS6
  csrwr $t4, LOONGARCH_CSR_KS5
  csrwr $t5, LOONGARCH_CSR_KS4

  csrrd $t5, LOONGARCH_CSR_TLBRBADV

  /* get the addr of root page table */
  csrrd $t0, LOONGARCH_CSR_PGD

  lddir $t0, $t0, 3
  lddir $t0, $t0, 1

  ldpte	$t0, 0
  csrrd $t1, LOONGARCH_CSR_TLBRELO0
  ldpte	$t0, 1
  csrrd $t2, LOONGARCH_CSR_TLBRELO1

  csrrd $t3, LOONGARCH_CSR_TLBREHI
  tlbfill

  //csrrd $t4, LOONGARCH_CSR_TLBRERA

  //csrrd $t5, LOONGARCH_CSR_STLBPGSIZE

  //csrrd $t6, LOONGARCH_CSR_TLBIDX

  /* restore t0 from TLBRSAVE */
  csrwr	$t0, LOONGARCH_CSR_TLBRSAVE

  csrwr $t1, LOONGARCH_CSR_KS8
  csrwr $t2, LOONGARCH_CSR_KS7
  csrwr $t3, LOONGARCH_CSR_KS6
  csrwr $t4, LOONGARCH_CSR_KS5
  csrwr $t5, LOONGARCH_CSR_KS4
  ertn