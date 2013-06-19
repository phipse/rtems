/**
 * @file
 * 
 * @brief Virtualized Sensitive Intel I386 CPU Dependent Source
 * 
 * This include file contains information for the virtualized i386
 * architecture. 
 *
 * Author:  Philipp Eppelt
 * Date:    06/19/2013
 */

#ifndef _RTEMS_LIBCPU_CPU_H
#define _RTEMS_LIBCPU_CPU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/score/i386.h>
#include <virtLayerCPU.h>



#ifndef ASM
/*
 *  ISR handler macros
 *
 *  These macros perform the following functions:
 *     + set a particular level
 */


#define _CPU_ISR_Set_level( _new_level ) \
  { \
    if ( _new_level ) virt_closeInterrupts();  \
    else              virt_openInterrupts(); \
  }



/*
 *  Fatal Error manager macros
 *
 *  These macros perform the following functions:
 *    + disable interrupts and halt the CPU
 */

#define _CPU_Fatal_halt( _error ) \
  { \
    virt_closeInterrupts(); \
    virt_execStopError( _error ); \
  }

#endif /* ASM */  


#ifdef __cplusplus
}
#endif


#endif /* _RTEMS_LIBCPU_CPU_H */
