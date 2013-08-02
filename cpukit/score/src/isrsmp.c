/**
 *  @file
 *
 *  @brief Initialize, Disable, Enable, Flash, Enter, Exit ISR Implementation
 *  @ingroup ScoreISR
 */

/*
 *  COPYRIGHT (c) 1989-2011.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/isr.h>
#include <rtems/score/thread.h>
#include <rtems/score/threaddispatch.h>
#include <rtems/score/smp.h>

int _ISR_SMP_Enter(void)
{
  uint32_t isr_nest_level;
  ISR_Level level;

  /* FIXME: Where is the corresponding _ISR_Enable()? */
  _ISR_Disable( level );

  isr_nest_level = _ISR_Nest_level++;

  _Thread_Disable_dispatch();

  return isr_nest_level;
}

int _ISR_SMP_Exit(void)
{
  ISR_Level level;
  int       retval;

  retval = 0;

  _ISR_Disable( level );

  _ISR_Nest_level--;

  if ( _ISR_Nest_level == 0 ) {
    if ( _Thread_Dispatch_necessary ) {
      if ( _Thread_Dispatch_get_disable_level() == 1 ) {
        retval = 1;
      }
    } 
  }

  /*
   *  SPARC has special support to avoid some nasty recursive type behaviour.
   *  When dispatching in a thread and we want to return to it then it needs
   *  to finish.
   */
  #if defined(__sparc__)
    if ( _CPU_ISR_Dispatch_disable )
      retval = 0;
  #endif

  _ISR_Enable( level );

  _Thread_Dispatch_decrement_disable_level();

  return retval;
}
