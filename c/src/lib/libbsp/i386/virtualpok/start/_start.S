/*
 *  COPYRIGHT (c) 2013/
 *  Philipp Eppelt.
 *
 *  Contact:  philipp.eppelt@mailbox.tu-dresden.de
 *
 *  Purpose:  Provides GNU entry point and directly go to bootcard.
 */

#include <rtems/asm.h>
#include <rtems/score/cpu.h>


#ifndef CPU_STACK_ALIGNMENT
#error  "Missing header ? CPU_STACK_ALIGNMENT NOT DEFINED"
#endif

.set STACK_SIZE, 0x1000

/*----------------------------------------------------------------------------+
| CODE section
+----------------------------------------------------------------------------*/

BEGIN_CODE

	PUBLIC (start)		# GNU default entry point
	
	EXTERN (boot_card)
	EXTERN (bsp_reset)

	
SYM (start):

	call	SYM (boot_card)

	# TODO when this returns there should be some shut down handling
	call	SYM (bsp_reset)
