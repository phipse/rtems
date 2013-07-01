/* Date:      06/19/2013
 * Author:    Philipp Eppelt
 * Purpose:   CPU part of the virtualization layer.
 * Licencse:  see RTEMS License.
 */


#ifndef RTEMS_VIRT_LAYER_CPU_H
#define RTEMS_VIRT_LAYER_CPU_H

#ifndef ASM

/* Interrupts */
__attribute__((fastcall)) int
virt_requestIrq( int vector );

__attribute__((fastcall)) void
virt_detachIrq( int vector );

__attribute__((fastcall)) void
virt_enableInterrupts( int _level );

__attribute__((fastcall)) void
virt_disableInterrupts( int _level );

__attribute__((fastcall)) void 
virt_flashInterrupts( int _level );

__attribute__((fastcall)) void
virt_openInterrupts( void );

__attribute__((fastcall)) void
virt_closeInterrupts( void );

__attribute__((fastcall)) int
virt_getInterruptLevel( int _level );



/* Idle Thread */

/**
 * @brief Lowest priority thread, doing nothing, never returns;
 */

__attribute__((fastcall)) void
virt_idleThread( void );


/* Error handling */

__attribute__((fastcall)) void
virt_execStopError( int _error );

#endif /* ASM */

#endif /* RTEMS_VIRT_LAYER_CPU_H */
