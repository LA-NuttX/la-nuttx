/****************************************************************************
 * arch/loongarch/src/common/vfork.S
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

#include "loongarch_vfork.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Symbols
 ****************************************************************************/

  .file  "vfork.S"
  .globl up_vfork
  .globl vfork

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: vfork
 *
 * Description:
 *   The vfork() function has the same effect as fork(), except that the
 *   behavior is undefined if the process created by vfork() either modifies
 *   any data other than a variable of type pid_t used to store the return
 *   value from vfork(), or returns from the function in which vfork() was
 *   called, or calls any other function before successfully calling _exit()
 *   or one of the exec family of functions.
 *
 *   This thin layer implements vfork by simply calling up_vfork() with the
 *   vfork() context as an argument.  The overall sequence is:
 *
 *   1) User code calls vfork().  vfork() collects context information and
 *      transfers control up up_vfork().
 *   2) up_vfork() and calls nxtask_setup_vfork().
 *   3) nxtask_setup_vfork() allocates and configures the child task's TCB.
 *      This consists of:
 *      - Allocation of the child task's TCB.
 *      - Initialization of file descriptors and streams
 *      - Configuration of environment variables
 *      - Allocate and initialize the stack
 *      - Setup the input parameters for the task.
 *      - Initialization of the TCB (including call to up_initial_state())
 *   4) up_vfork() provides any additional operating context. up_vfork must:
 *      - Initialize special values in any CPU registers that were not
 *        already configured by up_initial_state()
 *   5) up_vfork() then calls nxtask_start_vfork()
 *   6) nxtask_start_vfork() then executes the child thread.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Upon successful completion, vfork() returns 0 to the child process and
 *   returns the process ID of the child process to the parent process.
 *   Otherwise, -1 is returned to the parent, no child process is created,
 *   and errno is set to indicate the error.
 *
 ****************************************************************************/

.type vfork, function

vfork:

    /* Create a stack frame */
    addi.d      $sp, $sp, -VFORK_SIZEOF

    /* CPU registers */
    /* Save the volatile registers */

    REGSTORE    $s0, $sp, VFORK_S0_OFFSET
    REGSTORE    $s1, $sp, VFORK_S1_OFFSET
    REGSTORE    $s2, $sp, VFORK_S2_OFFSET
    REGSTORE    $s3, $sp, VFORK_S3_OFFSET
    REGSTORE    $s4, $sp, VFORK_S4_OFFSET
    REGSTORE    $s5, $sp, VFORK_S5_OFFSET
    REGSTORE    $s6, $sp, VFORK_S6_OFFSET
    REGSTORE    $s7, $sp, VFORK_S7_OFFSET
    REGSTORE    $s8, $sp, VFORK_S8_OFFSET

    /* Save the frame pointer s9/r22, stack pointer, and return address */
    REGSTORE    $r22, $sp, VFORK_S9_OFFSET

    addi.d      $s0, $sp, VFORK_SIZEOF
    REGSTORE    $s0, $sp, VFORK_SP_OFFSET   /* original SP */
    REGSTORE    $r1, $sp, VFORK_RA_OFFSET   /* return address */

  /* Floating point registers */

#ifdef CONFIG_ARCH_FPU
    FSTORE      $fs0, $sp, VFORK_FS0_OFFSET
    FSTORE      $fs1, $sp, VFORK_FS1_OFFSET
    FSTORE      $fs2, $sp, VFORK_FS2_OFFSET
    FSTORE      $fs3, $sp, VFORK_FS3_OFFSET
    FSTORE      $fs4, $sp, VFORK_FS4_OFFSET
    FSTORE      $fs5, $sp, VFORK_FS5_OFFSET
    FSTORE      $fs6, $sp, VFORK_FS6_OFFSET
    FSTORE      $fs7, $sp, VFORK_FS7_OFFSET
#endif

    move        $a0, $sp
    bl          up_vfork

    /* Release the stack frame and return the value returned by up_vfork */

    REGLOAD     $r1, $sp, VFORK_RA_OFFSET
    addi.d      $sp, $sp, VFORK_SIZEOF
    jirl        $r0, $r1, 0

  .size  vfork, .-vfork
  .end
