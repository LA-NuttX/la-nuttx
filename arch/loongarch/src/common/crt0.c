/****************************************************************************
 * arch/loongarch/src/common/crt0.c
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

#include <nuttx/arch.h>
#include <nuttx/addrenv.h>
#include <nuttx/compiler.h>
#include <nuttx/config.h>

#include <sys/types.h>
#include <syscall.h>
#include <stdlib.h>

#include "loongarch_internal.h"

#ifdef CONFIG_BUILD_KERNEL

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

int main(int argc, char *argv[]);

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_signal_handler
 *
 * Description:
 *   This function is the user-space, signal handler trampoline function.  It
 *   is called from up_signal_dispatch() in user-mode.
 *
 * Input Parameters:
 *   a0 = sighand
 *     The address user-space signal handling function
 *   a1-a3 = signo, info, and ucontext
 *     Standard arguments to be passed to the signal handling function.
 *
 * Returned Value:
 *   None.  This function does not return in the normal sense.  It returns
 *   via the SYS_signal_handler_return (see syscall.h)
 *
 ****************************************************************************/

static inline void sig_trampoline(void)
{
  assert(0);
  __asm__ __volatile__
  (
    " addi.d $sp, $sp, -" STACK_FRAME_SIZE "\n"   /* Save ra on the stack */
    REGSTORE " $ra, $sp, 0\n"
    " move   $t0, $a0\n"        /* t0=sighand */
    " move   $a0, $a1\n"        /* a0=signo */
    " move   $a1, $a2\n"        /* a1=info */
    " move   $a2, $a3\n"        /* a2=ucontext */
    " jirl   $ra, $t0, 0\n"     /* Call the signal handler (modifies ra) */
    REGLOAD "$ra, $sp, 0\n"     /* Recover ra in sp */
    " addi.d $sp, $sp, " STACK_FRAME_SIZE "\n"
    " li.d   $a0, %0\n"         /* SYS_signal_handler_return */
    " syscall 0\n"              /* Return from the SYSCALL */
    " nop\n"
    :
    : "i" (SYS_signal_handler_return)
    :
  );
}

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* Linker defined symbols to .ctors and .dtors */

extern initializer_t _sctors[];
extern initializer_t _ectors[];
extern initializer_t _sdtors[];
extern initializer_t _edtors[];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

#ifdef CONFIG_HAVE_CXX

/****************************************************************************
 * Name: exec_ctors
 *
 * Description:
 *   Call static constructors
 *
 ****************************************************************************/

static void exec_ctors(void)
{
  for (initializer_t *ctor = _sctors; ctor != _ectors; ctor++)
    {
      (*ctor)();
    }
}

/****************************************************************************
 * Name: exec_dtors
 *
 * Description:
 *   Call static destructors
 *
 ****************************************************************************/

static void exec_dtors(void)
{
  for (initializer_t *dtor = _sdtors; dtor != _edtors; dtor++)
    {
      (*dtor)();
    }
}

#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: _start
 *
 * Description:
 *   This function is the low level entry point into the main thread of
 *   execution of a task.  It receives initial control when the task is
 *   started and calls main entry point of the newly started task.
 *
 * Input Parameters:
 *   argc - The number of parameters being passed.
 *   argv - The parameters being passed. These lie in kernel-space memory
 *     and will have to be reallocated  in user-space memory.
 *
 * Returned Value:
 *   This function should not return.  It should call the user-mode start-up
 *   main() function.  If that function returns, this function will call
 *   exit.
 *
 ****************************************************************************/

void _start(int argc, char *argv[])
{
  int ret;

  /* Initialize the reserved area at the beginning of the .bss/.data region
   * that is visible to the RTOS.
   */

  ARCH_DATA_RESERVE->ar_sigtramp = (addrenv_sigtramp_t)sig_trampoline;

#ifdef CONFIG_HAVE_CXX
  /* Call C++ constructors */

  exec_ctors();

  /* Setup so that C++ destructors called on task exit */

  atexit(exec_dtors);
#endif

  /* Call the main() entry point passing argc and argv. */

  ret = main(argc, argv);

  /* Call exit() if/when the main() returns */

  exit(ret);
}

#endif /* CONFIG_BUILD_KERNEL */
