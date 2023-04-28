/****************************************************************************
 * libs/libc/machine/loongarch/common/arch_elf.c
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

#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <debug.h>
#include <assert.h>

#include <arch/elf.h>
#include <nuttx/elf.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define OPCODE_SW       0x23
#define OPCODE_LUI      0x37

#define RVI_OPCODE_MASK 0x7F

/* ELF32 and ELF64 definitions */

#ifdef CONFIG_LIBC_ARCH_ELF_64BIT
#  define ARCH_ELF_TYP_STR    "64"
#  define ARCH_ELF_CLASS      ELFCLASS64
#  define ARCH_ELF_RELTYPE    ELF64_R_TYPE
#else /* !CONFIG_LIBC_ARCH_ELF_64BIT */
#  define ARCH_ELF_TYP_STR    "32"
#  define ARCH_ELF_CLASS      ELFCLASS32
#  define ARCH_ELF_RELTYPE    ELF32_R_TYPE
#endif /* CONFIG_LIBC_ARCH_ELF_64BIT */

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

struct rname_code_s
{
  const char *name;
  int type;
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct rname_code_s _rname_table[] =
{
  {"R_LARCH_32", R_LARCH_32},
  {"R_LARCH_64", R_LARCH_64},
  {"SOP_PUSH_PCREL", R_LARCH_SOP_PUSH_PCREL},
  {"SOP_PUSH_ABSOLUTE", R_LARCH_SOP_PUSH_ABSOLUTE},
  {"SOP_PUSH_GPREL", R_LARCH_SOP_PUSH_GPREL},
  {"SOP_PUSH_PLT_PCREL", R_LARCH_SOP_PUSH_PLT_PCREL},
  {"SOP_SUB", R_LARCH_SOP_SUB},
  {"SOP_SL", R_LARCH_SOP_SL},
  {"SOP_SR", R_LARCH_SOP_SR},
  {"SOP_ADD", R_LARCH_SOP_ADD},
  {"SOP_POP_32_S_10_12", R_LARCH_SOP_POP_32_S_10_12},
  {"SOP_POP_32_S_10_16_S2", R_LARCH_SOP_POP_32_S_10_16_S2},
  {"SOP_POP_32_S_5_20", R_LARCH_SOP_POP_32_S_5_20},
  {"SOP_POP_32_S_0_5_10_16_S2", R_LARCH_SOP_POP_32_S_0_5_10_16_S2},
  {"SOP_POP_32_S_0_10_10_16_S2", R_LARCH_SOP_POP_32_S_0_10_10_16_S2},
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static const char *_get_rname(int type)
{
  int i = 0;

  for (i = 0; i < sizeof(_rname_table) / sizeof(struct rname_code_s); i++)
    {
      if (_rname_table[i].type == type)
        {
          return _rname_table[i].name;
        }
    }

  /* Not found in the table */

  return "?????";
}

/****************************************************************************
 * Name: _get_val, set_val, _add_val
 *
 * Description:
 *   These functions are used when relocating an instruction because we can
 *   not assume the instruction is word-aligned.
 *
 ****************************************************************************/

static uint64_t _get_val(uint32_t *addr)
{
  uint64_t ret;
  ret = *addr | (*(addr + 1)) << 32;
  return ret;
}

static void _set_val64(uint64_t *addr, uint64_t val)
{
  *addr       = (val & 0xffffffffffffffffULL);

  /* NOTE: Ensure relocation before execution */

  asm volatile ("dbar 0");
}
static void _set_val32(uint32_t *addr, uint32_t val)
{
  *addr       = (val & 0xffffffff);

  /* NOTE: Ensure relocation before execution */

  asm volatile ("dbar 0");
}
// static void _add_val(uint16_t *addr, uint32_t val)
// {
//   uint32_t cur = _get_val(addr);
//   _set_val(addr, cur + val);
// }

/****************************************************************************
 * Name: _calc_imm
 *
 * Description:
 *   Given offset and obtain imm_hi (20bit) and imm_lo (12bit)
 *
 * Input Parameters:
 *   offset - signed 32bit
 *   imm_hi - signed 20bit
 *   imm_lo - signed 12bit
 *
 * Returned Value:
 *   none
 *
 ****************************************************************************/

// static void _calc_imm(long offset, long *imm_hi, long *imm_lo)
// {
//   long lo;
//   long hi = offset / 4096;
//   long r  = offset % 4096;

//   if (2047 < r)
//     {
//       hi++;
//     }
//   else if (r < -2048)
//     {
//       hi--;
//     }

//   lo = offset - (hi * 4096);

//   binfo("offset=%ld: hi=%ld lo=%ld\n",
//         offset, hi, lo);

//   ASSERT(-2048 <= lo && lo <= 2047);

//   *imm_lo = lo;
//   *imm_hi = hi;
// }

/****************************************************************************
 * Name: rela_stack_push
 *
 * Description:
 *   Push a value into rela_stack, which is used for LoongArch relocation
 *
 * Input Parameters:
 *   stack_value - The value to be pushed
 *   rela_stack - The stack
 *   rela_stack_top - Pointing to the top of the rela_stack
 *
 * Returned Value:
 *   0 on success, other values for failure
 *
 ****************************************************************************/

static int rela_stack_push(int64_t stack_value, int64_t *rela_stack, size_t *rela_stack_top)
{
	if (*rela_stack_top >= CONFIG_LOONGARCH_RELA_STACK_DEPTH)
		return -ENOEXEC;

	rela_stack[(*rela_stack_top)++] = stack_value;
	binfo("%s stack_value = 0x%llx\n", __func__, stack_value);

	return 0;
}

/****************************************************************************
 * Name: rela_stack_pop
 *
 * Description:
 *   Pop a value from rela_stack, which is used for LoongArch relocation
 *
 * Input Parameters:
 *   stack_value - The value poped from rela_stack_pop
 *   rela_stack - The stack
 *   rela_stack_top - Pointing to the top of the rela_stack
 *
 * Returned Value:
 *   0 on success, other values for failure
 *
 ****************************************************************************/
static int rela_stack_pop(int64_t *stack_value, int64_t *rela_stack, size_t *rela_stack_top)
{
	if (*rela_stack_top == 0)
		return -ENOEXEC;

	*stack_value = rela_stack[--(*rela_stack_top)];
	binfo("%s stack_value = 0x%llx\n", __func__, *stack_value);

	return 0;
}
/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_checkarch
 *
 * Description:
 *   Given the ELF header in 'hdr', verify that the ELF file is appropriate
 *   for the current, configured architecture.  Every architecture that uses
 *   the ELF loader must provide this function.
 *
 * Input Parameters:
 *   hdr - The ELF header read from the ELF file.
 *
 * Returned Value:
 *   True if the architecture supports this ELF file.
 *
 ****************************************************************************/

bool up_checkarch(const Elf_Ehdr *ehdr)
{
  /* Make sure it's an LoongArch executable */

  if (ehdr->e_machine != EM_LOONGARCH)
    {
      berr("ERROR: Not for EM_LOONGARCH: e_machine=%04x\n", ehdr->e_machine);
      return false;
    }

  /* Make sure that current objects are supported */

  if (ehdr->e_ident[EI_CLASS] != ARCH_ELF_CLASS)
    {
      berr("ERROR: Need " ARCH_ELF_TYP_STR "-bit "
           "objects: e_ident[EI_CLASS]=%02x\n",
           ehdr->e_ident[EI_CLASS]);
      return false;
    }

  /* Verify endian-ness */

#ifdef CONFIG_ENDIAN_BIG
  if (ehdr->e_ident[EI_DATA] != ELFDATA2MSB)
#else
  if (ehdr->e_ident[EI_DATA] != ELFDATA2LSB)
#endif
    {
      berr("ERROR: Wrong endian-ness: e_ident[EI_DATA]=%02x\n",
           ehdr->e_ident[EI_DATA]);
      return false;
    }

  /* Make sure the entry point address is properly aligned */

  if ((ehdr->e_entry & 1) != 0)
    {
      berr("ERROR: Entry point is not properly aligned: %08lx\n",
           ehdr->e_entry);
    }

  /* TODO:  Check ABI here. */

  return true;
}

/****************************************************************************
 * Name: up_relocate and up_relocateadd
 *
 * Description:
 *   Perform an architecture-specific ELF relocation.  Every architecture
 *   that uses the ELF loader must provide this function.
 *
 * Input Parameters:
 *   rel - The relocation type
 *   sym - The ELF symbol structure containing the fully resolved value.
 *         There are a few relocation types for a few architectures that do
 *         not require symbol information.  For those, this value will be
 *         NULL.  Implementations of these functions must be able to handle
 *         that case.
 *   addr - The address that requires the relocation.
 *
 * Returned Value:
 *   Zero (OK) if the relocation was successful.  Otherwise, a negated errno
 *   value indicating the cause of the relocation failure.
 *
 ****************************************************************************/

int up_relocate(const Elf_Rel *rel, const Elf_Sym *sym, uintptr_t addr)
{
  berr("Not implemented\n");
  return -ENOSYS;
}

int up_relocateadd(const Elf_Rela *rel, const Elf_Sym *sym,
                   uintptr_t addr, int64_t *rela_stack, size_t *rela_stack_top)
{
  unsigned int relotype;

  /* All relocations depend upon having valid symbol information */

  relotype = ARCH_ELF_RELTYPE(rel->r_info);
  binfo("relocation type:%u\n", relotype);

  // if (sym == NULL && relotype != R_LARCH_NONE)
  //   {
  //     sym->st_value = 0;
  //   }

  /* Do relocation based on relocation type */

  switch (relotype)
    {
      case R_LARCH_32:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=%08lx\n",
              _get_rname(relotype),
              addr, _get_val((uint32_t *)addr),
              sym, sym->st_value);
        _set_val32((uint32_t *)addr, (uint32_t)(sym->st_value + rel->r_addend));
      }
      break;

      case R_LARCH_64:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=%08lx\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              sym, sym->st_value);
        _set_val64((uint64_t *)addr, (uint64_t)(sym->st_value + rel->r_addend));
      }
      break;

      case R_LARCH_SOP_PUSH_PCREL:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=%08lx\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              sym, sym->st_value);

        rela_stack_push((long)sym->st_value + (long)rel->r_addend - (long)addr, rela_stack, rela_stack_top);
      }
      break;
      case R_LARCH_SOP_PUSH_ABSOLUTE:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=unknown\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              0);
        
        // rela_stack_push(0 + (long)rel->r_addend, rela_stack, rela_stack_top);
        // rela_stack_push((long)sym->st_value +(long)rel->r_addend, rela_stack, rela_stack_top);
        if(sym){
          rela_stack_push((long)sym->st_value +(long)rel->r_addend, rela_stack, rela_stack_top);
          bwarn("This condition never encountered so far!\n");
        }else{
          rela_stack_push(0 + (long)rel->r_addend, rela_stack, rela_stack_top);          
        }
      }
      break;

      case R_LARCH_SOP_PUSH_GPREL:
      break;

      case R_LARCH_SOP_PUSH_PLT_PCREL:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=%08lx\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              sym, sym->st_value);

        rela_stack_push((long)sym->st_value + (long)rel->r_addend - (long)addr, rela_stack, rela_stack_top);
      }
      break;

      case R_LARCH_SOP_SUB:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=unknown\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              0);

        int err = 0;
        int64_t opr1, opr2;

        err = rela_stack_pop(&opr2, rela_stack, rela_stack_top);
        if (err)
          return err;
        err = rela_stack_pop(&opr1, rela_stack, rela_stack_top);
        if (err)
          return err;
        err = rela_stack_push(opr1 - opr2, rela_stack, rela_stack_top);
        if (err)
          return err;
      }
      break;

      case R_LARCH_SOP_SL:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=unknown\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              0);

        int err = 0;
        int64_t opr1, opr2;

        err = rela_stack_pop(&opr2, rela_stack, rela_stack_top);
        if (err)
          return err;
        err = rela_stack_pop(&opr1, rela_stack, rela_stack_top);
        if (err)
          return err;
        err = rela_stack_push(opr1 << opr2, rela_stack, rela_stack_top);
        if (err)
          return err;
      }
      break;

      case R_LARCH_SOP_SR:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=unknown\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              0);
        int err = 0;
        int64_t opr1, opr2;

        err = rela_stack_pop(&opr2, rela_stack, rela_stack_top);
        if (err)
          return err;
        err = rela_stack_pop(&opr1, rela_stack, rela_stack_top);
        if (err)
          return err;
        err = rela_stack_push(opr1 >> opr2, rela_stack, rela_stack_top);
        if (err)
          return err;
      }
      break;

      case R_LARCH_SOP_ADD:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=unknown\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              0);
        int err = 0;
        int64_t opr1, opr2;

        err = rela_stack_pop(&opr2, rela_stack, rela_stack_top);
        if (err)
          return err;
        err = rela_stack_pop(&opr1, rela_stack, rela_stack_top);
        if (err)
          return err;
        err = rela_stack_push(opr1 + opr2, rela_stack, rela_stack_top);
        if (err)
          return err;
      }
      break;

      case R_LARCH_SOP_POP_32_S_10_12:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=unknown\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              0);

        int err = 0;
        int64_t opr1;

        err = rela_stack_pop(&opr1, rela_stack, rela_stack_top);
        if (err)
          return err;
        
        	/* check 12-bit signed */
        if ((opr1 & ~(uint64_t)0x7ff) &&
            (opr1 & ~(uint64_t)0x7ff) != ~(uint64_t)0x7ff) {
          berr("opr1 = 0x%llx overflow! dangerous %s relocation\n", opr1, __func__);
          return -ENOEXEC;
        }

        /* (*(uint32_t *) PC) [21 ... 10] = opr [11 ... 0] */
        *(uint32_t *)addr = (*(uint32_t *)addr & (~(uint32_t)0x3ffc00)) | ((opr1 & 0xfff) << 10);
      }
      break;

      case R_LARCH_SOP_POP_32_S_10_16_S2:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=unknown\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              0);
        
        int err = 0;
        int64_t opr1;

        err = rela_stack_pop(&opr1, rela_stack, rela_stack_top);
        if (err)
          return err;

        /* check 4-aligned */
        if (opr1 % 4) {
          berr("opr1 = 0x%llx unaligned! dangerous %s relocation\n",
            opr1, __func__);
          return -ENOEXEC;
        }

        opr1 >>= 2;
        /* check 18-bit signed */
        if ((opr1 & ~(uint64_t)0x7fff) &&
            (opr1 & ~(uint64_t)0x7fff) != ~(uint64_t)0x7fff) {
          berr("opr1 = 0x%llx overflow! dangerous %s relocation\n",
            opr1, __func__);
          return -ENOEXEC;
        }

        /* (*(uint32_t *) PC) [25 ... 10] = opr [17 ... 2] */
        *(uint32_t *)addr = (*(uint32_t *)addr & 0xfc0003ff) | ((opr1 & 0xffff) << 10);

      }
      break;

      case R_LARCH_SOP_POP_32_S_5_20:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=unknown\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              0);
        int err = 0;
        int64_t opr1;

        err = rela_stack_pop(&opr1, rela_stack, rela_stack_top);
        if (err)
          return err;

        /* check 20-bit signed */
        if ((opr1 & ~(uint64_t)0x7ffff) &&
            (opr1 & ~(uint64_t)0x7ffff) != ~(uint64_t)0x7ffff) {
          berr("opr1 = 0x%llx overflow! dangerous %s relocation\n",
            opr1, __func__);
          return -ENOEXEC;
        }

        /* (*(uint32_t *) PC) [24 ... 5] = opr [19 ... 0] */
        *(uint32_t *)addr = (*(uint32_t *)addr & (~(uint32_t)0x1ffffe0)) | ((opr1 & 0xfffff) << 5);
      }
      break;

      case R_LARCH_SOP_POP_32_S_0_5_10_16_S2:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=unknown\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              0);
        int err = 0;
        int64_t opr1;

        err = rela_stack_pop(&opr1, rela_stack, rela_stack_top);
        if (err)
          return err;

        /* check 4-aligned */
        if (opr1 % 4) {
          berr("opr1 = 0x%llx unaligned! dangerous %s relocation\n",
            opr1, __func__);
          return -ENOEXEC;
        }

        opr1 >>= 2;
        /* check 23-bit signed */
        if ((opr1 & ~(uint64_t)0xfffff) &&
            (opr1 & ~(uint64_t)0xfffff) != ~(uint64_t)0xfffff) {
          berr("opr1 = 0x%llx overflow! dangerous %s relocation\n",
            opr1, __func__);
          return -ENOEXEC;
        }

        /*
        * (*(uint32_t *) PC) [4 ... 0] = opr [22 ... 18]
        * (*(uint32_t *) PC) [25 ... 10] = opr [17 ... 2]
        */
        *(uint32_t *)addr = (*(uint32_t *)addr & 0xfc0003e0)
            | ((opr1 & 0x1f0000) >> 16) | ((opr1 & 0xffff) << 10);
      }
      break;

      case R_LARCH_SOP_POP_32_S_0_10_10_16_S2:
      {
        binfo("%s at %08" PRIxPTR " [%08" PRIx32 "] "
              "to sym=%p st_value=unknown\n",
              _get_rname(relotype),
              addr, _get_val((uint64_t *)addr),
              0);

        int err = 0;
        int64_t opr1;

        err = rela_stack_pop(&opr1, rela_stack, rela_stack_top);
        if (err)
          return err;

        /* check 4-aligned */
        if (opr1 % 4) {
          berr("opr1 = 0x%llx unaligned! dangerous %s relocation\n",
            opr1, __func__);
          return -ENOEXEC;
        }

        opr1 >>= 2;
        /* check 28-bit signed */
        if ((opr1 & ~(uint64_t)0x1ffffff) &&
            (opr1 & ~(uint64_t)0x1ffffff) != ~(uint64_t)0x1ffffff) {
          berr("opr1 = 0x%llx overflow! dangerous %s relocation\n",
            opr1, __func__);
          return -ENOEXEC;
        }

        /*
        * (*(uint32_t *) PC) [9 ... 0] = opr [27 ... 18]
        * (*(uint32_t *) PC) [25 ... 10] = opr [17 ... 2]
        */
        *(uint32_t *)addr = (*(uint32_t *)addr & 0xfc000000)
            | ((opr1 & 0x3ff0000) >> 16) | ((opr1 & 0xffff) << 10);
      }
      break;
      default:
        berr("ERROR: Unsupported relocation: %ld\n",
             ARCH_ELF_RELTYPE(rel->r_info));
        ASSERT(false);
        return -EINVAL;
    }

  return OK;
}
