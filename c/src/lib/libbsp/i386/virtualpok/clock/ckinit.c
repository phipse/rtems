/*  ckinit.c
 *
 *  This file provides a clock device driver to be used with the
 *  virtualizationlayer.
 *
 *  COPYRIGHT (c) 2013.
 *  Philipp Eppelt.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include <bsp.h>
#include <bsp/irq.h>

#include <rtems.h>
#include <rtems/config.h>
#include <rtems/score/tod.h>
#include <rtems/score/watchdog.h>
#include <rtems/score/timestamp.h>
#include <assert.h>
#include <virtualizationlayercpu.h>
#include <virtualizationlayerbsp.h>


void Clock_isr(void *param);
static void Clock_isr_handler(void *param);
/*
 *  The interrupt vector number associated with the clock tick device
 *  driver.
 */

#define CLOCK_VECTOR    0x0

/*
 *  Clock_driver_ticks is a monotonically increasing counter of the
 *  number of clock ticks since the driver was initialized.
 */

volatile uint32_t pc386_microseconds_per_isr;
volatile uint32_t pc386_isrs_per_tick;
volatile uint32_t         Clock_driver_ticks;

void     (*Clock_driver_support_at_tick)(void) = NULL;

#define Clock_driver_support_install_isr( _new, _old ) \
  do { \
    _old = NULL; \
  } while(0)

bool Clock_isr_enabled = false;

static void Clock_isr_handler(void *param)
{
  if ( Clock_isr_enabled )
    Clock_isr( param );
} // Clock_isr_handler

static void Clock_driver_support_at_tick_empty(void)
{
}

/**
 * @brief Enable clock device; start receiving clock interrupts.
 */
static void clockOn(void)
{
  pc386_isrs_per_tick        = 1;
  pc386_microseconds_per_isr = rtems_configuration_get_microseconds_per_tick();

  _CPU_Virtual_Irq_request( CLOCK_VECTOR );
} // clockOn

/**
 * @brief Disable clock device; stop receiving clock interrupts.
 */
static void clockOff(void)
{
  _CPU_Virtual_Irq_detach( CLOCK_VECTOR );
} // clockOff

/**
 * @brief Install the clock ISR in the RTEMS interrupt table.
 */
void Clock_driver_install_handler(void);
void Clock_driver_install_handler(void)
{
  rtems_status_code status;

  status = rtems_interrupt_handler_install(
    BSP_PERIODIC_TIMER,
    "ckinit",
    RTEMS_INTERRUPT_UNIQUE,
    Clock_isr_handler,
    NULL
  );
  if(status != RTEMS_SUCCESSFUL)
    printf( "ERROR: During clock interrupt handler install: %i\n", status);
  else
    printf( "CLOCK DRIVER installed successfully\n");
    
  clockOn();
} // Clock_driver_install_handler

uint32_t (*Clock_driver_nanoseconds_since_last_tick)(void) = NULL;

/**
 * @brief Setup the clock driver.
 */
void Clock_driver_support_initialize_hardware(void);
void Clock_driver_support_initialize_hardware(void)
{
    Clock_driver_support_at_tick = Clock_driver_support_at_tick_empty;

    Clock_isr_enabled = true;
} // Clock_driver_support_initialize_hardware

#define Clock_driver_support_shutdown_hardware() \
  do { \
    rtems_status_code status; \
    clockOff(); \
    status = rtems_interrupt_handler_remove(  \
      BSP_PERIODIC_TIMER, \
      Clock_isr_handler,  \
      NULL  \
    );  \
    assert(status == RTEMS_SUCCESSFUL); \
  } while (0)


#include "../../../shared/clockdrv_shell.h"
