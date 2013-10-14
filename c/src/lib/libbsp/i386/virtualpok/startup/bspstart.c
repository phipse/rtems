/*
 *  This routine starts the application.  It includes application,
 *  board, and monitor specific initialization and configuration.
 *  The generic CPU dependent initialization has been performed
 *  before this routine is invoked.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 */

#include <string.h>

#include <bsp.h>
#include <rtems.h>
#include <rtems/bspIo.h>
#include <virtualizationlayerbsp.h>


extern void rtems_irq_mngt_init(void);

/*
 *  bsp_start
 *
 *  This routine does the bulk of the system initialization.
 */
void bsp_start( void )
{

  _BSP_Virtual_Char_write( "Hello RTEMS World\n" );

  // Initialize IRQ management 
  rtems_irq_mngt_init();

  // Register clock driver
  Clock_driver_install_handler();
}