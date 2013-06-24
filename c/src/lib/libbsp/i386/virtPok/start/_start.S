/*  Date:     06/24/2013
    Author:   Philipp Eppelt
    Contact:  philipp.eppelt@mailbox.tu-dresden.de

    Purpose:  Provide GNU entry point and directly go to bootcard.


#include <rtems/asm.h>
#include <rtems/score/cpu.h>


/*----------------------------------------------------------------------------+
| CODE section
+----------------------------------------------------------------------------*/

BEGIN_CODE

	PUBLIC (start)		# GNU default entry point
	
	EXTERN (boot_card)

	
SYM (start):

	call	SYM (boot_card)

	# when this returns there should be some shut down handling
