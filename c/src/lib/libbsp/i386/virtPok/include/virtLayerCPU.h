/* Date:      06/19/2013
 * Author:    Philipp Eppelt
 * Purpose:   CPU part of the virtualization layer.
 * Licencse:  see RTEMS License.
 */


#ifndef RTEMS_VIRT_LAYER_CPU_H
#define RTEMS_VIRT_LAYER_CPU_H

/* Startup functions */

int 
virt_getWorkSpaceArea();



/* Interrupts */
int
virt_requestIrq( int vector );

void
virt_detachIrq( int vector );

void
virt_enableInterrupts( int _level );

void
virt_disableInterrupts( int _level );

void 
virt_flashInterrupts( int _level );

void
virt_openInterrupts();

void
virt_closeInterrupts();

int
virt_getInterruptLevel( void );



/* Idle Thread */

/**
 * @brief Lowest priority thread, doing nothing, never returns;
 */

void
virt_idleThread( void );


/* Error handling */

void
virt_execStopError( int _error );



#endif /* RTEMS_VIRT_LAYER_CPU_H */
