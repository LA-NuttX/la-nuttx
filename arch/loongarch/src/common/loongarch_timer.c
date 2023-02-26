/****************************************************************************
 * arch/loongarch/src/common/loongarch_timer.c
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

#include <nuttx/irq.h>
#include <nuttx/kmalloc.h>

#include <arch/barriers.h>

#include "loongarch_timer.h"
#include "loongarch_internal.h"

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* This structure provides the private representation of the "lower-half"
 * driver state structure.  This structure must be cast-compatible with the
 * oneshot_lowerhalf_s structure.
 */

struct loongarch_timer_lowerhalf_s
{
  struct oneshot_lowerhalf_s lower;
  uint64_t                   freq;
  uint64_t                   alarm;
  oneshot_callback_t         callback;
  void                       *arg;
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int loongarch_timer_max_delay(struct oneshot_lowerhalf_s *lower,
                                  struct timespec *ts);
static int loongarch_timer_start(struct oneshot_lowerhalf_s *lower,
                              oneshot_callback_t callback, void *arg,
                              const struct timespec *ts);
static int loongarch_timer_cancel(struct oneshot_lowerhalf_s *lower,
                               struct timespec *ts);
static int loongarch_timer_current(struct oneshot_lowerhalf_s *lower,
                                struct timespec *ts);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct oneshot_operations_s g_loongarch_timer_ops =
{
  .max_delay = loongarch_timer_max_delay,
  .start     = loongarch_timer_start,
  .cancel    = loongarch_timer_cancel,
  .current   = loongarch_timer_current,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static uint64_t loongarch_timer_get_time()
{
#ifdef CONFIG_ARCH_LA64

  int rID = 0;
	uint64_t val = 0;

	__asm__ __volatile__(
		"rdtime.d %0, %1 \n"
		: "=r"(val), "=r"(rID)
		:
		);
	return val;
#else
  assert(0);
#endif
}

static void loongarch_timer_set_tcfg(struct loongarch_timer_lowerhalf_s *priv,
                                      uint64_t value)
{
#ifdef CONFIG_ARCH_LA64

  uint64_t tcfg_init_value = value<<2 | CSR_TCFG_EN;
  // uint64_t tcfg_init_value = value<<2;//for debugging

  WRITE_CSR(LOONGARCH_CSR_TCFG, tcfg_init_value);
    
#else
    
  assert(0);
  putreg32(UINT32_MAX, priv->mtimecmp + 4);
  putreg32(value, priv->mtimecmp);
  putreg32(value >> 32, priv->mtimecmp + 4);
    
  /* Make sure it sticks */
#endif
  __DMB();
}

/****************************************************************************
 * Name: loongarch_timer_max_delay
 *
 * Description:
 *   Determine the maximum delay of the one-shot timer
 *
 * Input Parameters:
 *   lower   An instance of the lower-half oneshot state structure.  This
 *           structure must have been previously initialized via a call to
 *           oneshot_initialize();
 *   ts      The location in which to return the maximum delay.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned
 *   on failure.
 *
 ****************************************************************************/

static int loongarch_timer_max_delay(struct oneshot_lowerhalf_s *lower,
                                  struct timespec *ts)
{
  assert(0);
  ts->tv_sec  = UINT32_MAX;
  ts->tv_nsec = NSEC_PER_SEC - 1;

  return 0;
}

/****************************************************************************
 * Name: loongarch_timer_start
 *
 * Description:
 *   Start the oneshot timer
 *
 * Input Parameters:
 *   lower   An instance of the lower-half oneshot state structure.  This
 *           structure must have been previously initialized via a call to
 *           oneshot_initialize();
 *   handler The function to call when when the oneshot timer expires.
 *   arg     An opaque argument that will accompany the callback.
 *   ts      Provides the duration of the one shot timer.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned
 *   on failure.
 *
 ****************************************************************************/

static int loongarch_timer_start(struct oneshot_lowerhalf_s *lower,
                              oneshot_callback_t callback, void *arg,
                              const struct timespec *ts)
{
  struct loongarch_timer_lowerhalf_s *priv =
    (struct loongarch_timer_lowerhalf_s *)lower;

  priv->alarm = ts->tv_sec * priv->freq+
                ts->tv_nsec * priv->freq / NSEC_PER_SEC;

  priv->callback = callback;
  priv->arg      = arg;

  loongarch_timer_set_tcfg(priv, priv->alarm);
  
  return 0;
}

/****************************************************************************
 * Name: loongarch_timer_cancel
 *
 * Description:
 *   Cancel the oneshot timer and return the time remaining on the timer.
 *
 *   NOTE: This function may execute at a high rate with no timer running (as
 *   when pre-emption is enabled and disabled).
 *
 * Input Parameters:
 *   lower   Caller allocated instance of the oneshot state structure.  This
 *           structure must have been previously initialized via a call to
 *           oneshot_initialize();
 *   ts      The location in which to return the time remaining on the
 *           oneshot timer.  A time of zero is returned if the timer is
 *           not running.
 *
 * Returned Value:
 *   Zero (OK) is returned on success.  A call to up_timer_cancel() when
 *   the timer is not active should also return success; a negated errno
 *   value is returned on any failure.
 *
 ****************************************************************************/

static int loongarch_timer_cancel(struct oneshot_lowerhalf_s *lower,
                               struct timespec *ts)
{
  assert(0);
  struct loongarch_timer_lowerhalf_s *priv =
    (struct loongarch_timer_lowerhalf_s *)lower;
  uint64_t mtime;

  // riscv_mtimer_set_mtimecmp(priv, UINT64_MAX);

  mtime = loongarch_timer_get_time();
  if (priv->alarm > mtime)
    {
      uint64_t nsec = (priv->alarm - mtime) *
                      NSEC_PER_SEC / priv->freq;

      ts->tv_sec  = nsec / NSEC_PER_SEC;
      ts->tv_nsec = nsec % NSEC_PER_SEC;
    }
  else
    {
      ts->tv_sec  = 0;
      ts->tv_nsec = 0;
    }

  priv->alarm    = 0;
  priv->callback = NULL;
  priv->arg      = NULL;

  return 0;
}

/****************************************************************************
 * Name: loongarch_timer_current
 *
 * Description:
 *  Get the current time.
 *
 * Input Parameters:
 *   lower   Caller allocated instance of the oneshot state structure.  This
 *           structure must have been previously initialized via a call to
 *           oneshot_initialize();
 *   ts      The location in which to return the current time. A time of zero
 *           is returned for the initialization moment.
 *
 * Returned Value:
 *   Zero (OK) is returned on success, a negated errno value is returned on
 *   any failure.
 *
 ****************************************************************************/

static int loongarch_timer_current(struct oneshot_lowerhalf_s *lower,
                                struct timespec *ts)
{
  struct loongarch_timer_lowerhalf_s *priv =
    (struct loongarch_timer_lowerhalf_s *)lower;
  uint64_t time = loongarch_timer_get_time();
  if (time < 0)
  {
    assert(0);
    // time = 0xffffffffffffffff-(priv->timer_initval - loongarch_timer_get_time());
  }
  uint64_t nsec = time / (priv->freq / USEC_PER_SEC) * NSEC_PER_USEC;

  ts->tv_sec  = nsec / NSEC_PER_SEC;
  ts->tv_nsec = nsec % NSEC_PER_SEC;

  return 0;
}

static int loongarch_timer_interrupt(int irq, void *context, void *arg)
{
  struct loongarch_timer_lowerhalf_s *priv = arg;

  uintptr_t estatval_1 = READ_CSR(LOONGARCH_CSR_ESTAT);
  // printf("%lu", estatval_1);

  /* clear pending timer interrupt */
  WRITE_CSR(LOONGARCH_CSR_TINTCLR, CSR_TINTCLR_TI);
  uintptr_t estatval_2 = READ_CSR(LOONGARCH_CSR_ESTAT);
  // printf("%lu", estatval_2);

  if (priv->callback != NULL)
    {
      priv->callback(&priv->lower, priv->arg);
    }

  return 0;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

struct oneshot_lowerhalf_s *
loongarch_timer_initialize(int irq, uint64_t freq)
{
  struct loongarch_timer_lowerhalf_s *priv;

  priv = kmm_zalloc(sizeof(*priv));
  if(priv==NULL){
    assert(0);
  }
  if (priv != NULL)
    {
      priv->lower.ops = &g_loongarch_timer_ops;
      priv->freq      = freq;
      
      irq_attach(irq,loongarch_timer_interrupt,priv);
      up_enable_irq(irq);

    }

  return (struct oneshot_lowerhalf_s *)priv;
}
