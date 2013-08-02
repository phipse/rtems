/**
 * @file
 * 
 * @brief Virtualized Sensitive Intel I386 CPU Dependent Source
 * 
 * This include file contains information for the virtualized i386
 * architecture. 
 */

#ifndef _RTEMS_LIBCPU_CPU_H
#define _RTEMS_LIBCPU_CPU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/score/i386.h>



#ifndef ASM
/*
 *  ISR handler macros
 *
 *  These macros perform the following functions:
 *     + set a particular level
 */


#define _CPU_ISR_Set_level( _new_level ) \
  { \
    if ( _new_level ) __asm__ volatile ( "cli" ); \
    else              __asm__ volatile ( "sti" ); \
  }



/*
 *  Fatal Error manager macros
 *
 *  These macros perform the following functions:
 *    + disable interrupts and halt the CPU
 */

#define _CPU_Fatal_halt( _error ) \
  { \
    uint32_t _error_lvalue = ( _error ); \
    __asm__ volatile ( "cli ; \
                    movl %0,%%eax ; \
                    hlt" \
                    : "=r" ((_error_lvalue)) : "0" ((_error_lvalue)) \
    ); \
  }

#endif /* ASM */  


#ifdef __cplusplus
}
#endif


#endif /* _RTEMS_LIBCPU_CPU_H */
