/*  ckinit.c
 *
 *  This file provides a template for the clock device driver initialization.
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
/*
 *  Clock_isrs is the number of clock ISRs until the next invocation of
 *  the RTEMS clock tick routine.  The clock tick device driver
 *  gets an interrupt once a millisecond and counts down until the
 *  length of time between the user configured microseconds per tick
 *  has passed.
 */

//uint32_t         Clock_isrs;              /* ISRs until next tick */
//uint32_t  Clock_isrs_const;

/*
 * These are set by clock driver during its init
 */

//rtems_device_major_number rtems_clock_major = ~0;
//rtems_device_minor_number rtems_clock_minor;


/*
 *  Isr Handler
 */

//void Clock_isr(
//    void
//)
//{
///*
// * bump the number of clock driver ticks since initialization
// *
// * determine if it is time to announce the passing of tick as configured
// * to RTEMS through the rtems_clock_tick directive
// *
// * perform any timer dependent tasks
// */
//
//  Clock_driver_ticks++;
//  rtems_clock_tick();
//  _BSP_Virtual_Char_write( "CLOCK ISR");
//}

/*
 *  Install_clock
 *
 *  Install a clock tick handler and reprograms the chip.  This
 *  is used to initially establish the clock tick.
 */
//void rtems_clock_tick_update(uint32_t ticks_u32);
//void Install_clock(
//  void(*clock_handler)(void)
//)
//{
//
//  /*
//   * install the notification of ticks missed due to a partition switch on POK
//   */
//
//
///*
//  Clock_isrs_const = rtems_configuration_get_microseconds_per_tick() / 1000;
//  Clock_isrs = Clock_isrs_const;
//*/
//  /*
//   *  Schedule the clock cleanup routine to execute if the application exits.
//   */
//
//}

bool Clock_isr_enabled = false;
static void Clock_isr_handler(void *param)
{
  if ( Clock_isr_enabled )
    Clock_isr( param );
}

static void Clock_driver_support_at_tick_empty(void)
{
}

static void clockOn(void)
{
  pc386_isrs_per_tick        = 1;
  pc386_microseconds_per_isr = rtems_configuration_get_microseconds_per_tick();

  _CPU_Virtual_Irq_request( CLOCK_VECTOR );
}

static void clockOff(void)
{
  _CPU_Virtual_Irq_detach( CLOCK_VECTOR );
} /* Clock_exit */

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
}
uint32_t (*Clock_driver_nanoseconds_since_last_tick)(void) = NULL;

void Clock_driver_support_initialize_hardware(void);
void Clock_driver_support_initialize_hardware(void)
{
    Clock_driver_support_at_tick = Clock_driver_support_at_tick_empty;
    Clock_driver_install_handler();

    Clock_isr_enabled = true;
  /* Shell installs nanosecond handler before calling
   * Clock_driver_support_initialize_hardware() :-(
   * so we do it again now that we're ready.
   */
  /*rtems_clock_set_nanoseconds_extension(
    Clock_driver_nanoseconds_since_last_tick
  );
  */
}

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

/*
 *  Clock_initialize
 *
 *  Device driver entry point for clock tick driver initialization.
 */

/*rtems_device_driver Clock_initialize(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void *arg
)
{
  _BSP_Virtual_Char_write("clock init start\n");
  Clock_driver_ticks = 0;

  // First register the interrupt handler with RTEMS, then attach to the
  // interrupt source in POK

  rtems_status_code status = rtems_interrupt_handler_install(
    BSP_PERIODIC_TIMER,
    "ckinit",
    RTEMS_INTERRUPT_UNIQUE,
    Clock_isr,
    NULL
  );
  
  if( status != RTEMS_SUCCESSFUL )
    printf( "ERROR: During clock interrupt handler install: %i\n", status);

  _CPU_Virtual_Irq_request( CLOCK_VECTOR );

  // make major/minor avail to others such as shared memory driver

  rtems_clock_major = major;
  rtems_clock_minor = minor;

  atexit( Clock_exit );

  return RTEMS_SUCCESSFUL;
}*/

  /* 
   * updating the system with a number of clock ticks at once
   */
//void rtems_clock_tick_update(uint32_t ticks_u32)
//{
//  /* _TOD_Tickle_ticks(); */
//  Timestamp_Control tick;
//  uint32_t  nanoseconds_per_tick;
//  int i;
//  int sec;
//  unsigned long ticks = ticks_u32;
//
//  nanoseconds_per_tick = rtems_configuration_get_nanoseconds_per_tick();
//
//  _Timestamp_Set( &tick, 0, nanoseconds_per_tick * ticks);
//
//  _Watchdog_Ticks_since_boot += ticks;
//
//  _Timestamp_Add_to( &_TOD.uptime, &tick );
//  _Timestamp_Add_to( &_TOD.now, &tick );
//
//  _TOD.seconds_trigger += nanoseconds_per_tick;
//  if ( _TOD.seconds_trigger >= 1000000000UL ) {
//    /* more than one second may have elapsed since the last partition switch */
//    sec = _TOD.seconds_trigger / 1000000000UL;
//    for (i = 0; i < sec; i++){
//      _TOD.seconds_trigger -= 1000000000UL;
//    }
//  }
//
//  /* _Watchdog_Tickle_ticks();  */
//  sec = (ticks * nanoseconds_per_tick)/1000000000UL;
//  
//  _Watchdog_Adjust(&_Watchdog_Ticks_chain, WATCHDOG_FORWARD, ticks);
//  _Watchdog_Adjust(&_Watchdog_Seconds_chain, WATCHDOG_FORWARD, sec);
//
//  /* _Scheduler_Tick is an alias to an entry in a jump table, the implementation
//   * of which depends on the scheduler used. The workaround is to call it
//   * from a for(;;) loop as many times as ticks have elapsed (might be expensive),
//   * or just leave the scheduling to follow its own time, unsynchronized with
//   * other partitions or the hypervisor's real time passage.
//   */
//  /* 
//   * _Scheduler_Tick();
//   *
//   * if ( _Thread_Is_context_switch_necessary() &&
//   *   _Thread_Is_dispatching_enabled() )
//   *   _Thread_Dispatch();
//   */
//}

#include "../../../shared/clockdrv_shell.h"
