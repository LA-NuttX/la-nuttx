/****************************************************************************
 * arch/loongarch/src/common/dispatch_syscall.S
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
#include <loongarch_internal.h>

/****************************************************************************
 * Public Symbols
 ****************************************************************************/

  .file  "dispatch_syscall.S"
  .global sys_call2
  .global dispatch_syscall

/****************************************************************************
 * Name: dispatch_syscall
 *
 * Description:
 *   Call the stub function corresponding to the system call.  NOTE the non-
 *   standard parameter passing:
 *
 *     A0 = SYS_ call number
 *     A1 = parm0
 *     A2 = parm1
 *     A3 = parm2
 *     A4 = parm3
 *     A5 = parm4
 *     A6 = parm5
 *
 ****************************************************************************/

.type dispatch_syscall, function

dispatch_syscall:
  addi.d $sp, $sp, -STACK_FRAME_SIZE            /* Create a stack frame to hold ra */
  REGSTORE $ra, $sp, 0                          /* Save ra in the stack frame, this is the value used before syscall */
  la.abs  $t0, g_stublookup                     /* t0=The base of the stub lookup table */
#ifdef CONFIG_ARCH_LA32 
  slli.d  $a0, $a0, 2                           /* a0=Offset for the stub lookup table */
#else 
  slli.d  $a0, $a0, 3                           /* a0=Offset for the stub lookup table */
#endif 
  add.d   $t0, $t0, $a0                         /* t0=The address in the table */
  REGLOAD $t0, $t0, 0                           /* t0=The address of the stub for this syscall */
  jirl    $ra, $t0, 0                           /* Call the stub (modifies ra) */
  REGLOAD $ra, $sp, 0                           /* Restore ra */
  addi.d  $sp, $sp, STACK_FRAME_SIZE            /* Destroy the stack frame */
  move    $a2, $a0                              /* a2=Save return value in a0 */
  li.d    $a0, 3                                /* a0=SYS_syscall_return (3) */
#ifdef CONFIG_BUILD_KERNEL 
  b    sys_call2                                /* Return from the syscall */
#else 
  syscall 0                                     /* Return from the syscall */
#endif
  .size  dispatch_syscall, .-dispatch_syscall
  .end