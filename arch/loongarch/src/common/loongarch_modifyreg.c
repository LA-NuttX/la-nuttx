/****************************************************************************
 * arch/loongarch/src/common/loongarch_modifyreg.c
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
#include <debug.h>

#include <nuttx/spinlock.h>

#include "loongarch_internal.h"
#include "chip.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: modifyreg32
 *
 * Description:
 *   Atomically modify the specified bits in a memory mapped register
 *
 ****************************************************************************/

void modifyreg32(uintptr_t addr, uint32_t clearbits, uint32_t setbits)
{
  irqstate_t flags;
  uint32_t   regval;
  flags   = spin_lock_irqsave(NULL);
  regval  = getreg32(addr);
  regval &= ~clearbits;
  regval |= setbits;
  putreg32(regval, addr);
  spin_unlock_irqrestore(NULL, flags);
}

/****************************************************************************
 * Name: modifyreg64
 *
 * Description:
 *   Atomically modify the specified bits in a memory mapped register
 *
 ****************************************************************************/

void modifyreg64(uintptr_t addr, uint64_t clearbits, uint64_t setbits)
{
  irqstate_t flags;
  uint64_t   regval;

  flags   = spin_lock_irqsave(NULL);
  if (addr == LOONGARCH_IOCSR_EXTIOI_EN_BASE){
    regval = iocsr_read64(LOONGARCH_IOCSR_EXTIOI_EN_BASE);
  }else{
    regval  = getreg64(addr);
  }
  
  regval &= ~clearbits;
  regval |= setbits;

  if (addr == LOONGARCH_IOCSR_EXTIOI_EN_BASE){
    iocsr_write64(regval, addr);
  }else{
    putreg64(regval, addr);
  }

  spin_unlock_irqrestore(NULL, flags);
}
