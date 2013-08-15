/**
 * @file
 * 
 * @brief Virtualized Sensitive I386 CPU Dependent Source
 * 
 * This include file contains information for the virtualized i386
 * architecture. 
 *
 * COPYRIGHT (c) 2013 Philipp Eppelt.
 *  philipp.eppelt@mailbox.tu-dresden.de
 */

#ifndef _RTEMS_LIBCPU_CPU_H
#define _RTEMS_LIBCPU_CPU_H

#include <rtems/score/i386.h>
#include <virtualizationlayercpu.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ASM

/*
 *  ISR handler macros
 *
 *  These macros perform the following functions:
 *     + set a particular level
 */


#define _CPU_ISR_Set_level( _new_level ) \
  { \
    if ( _new_level ) _CPU_Virtual_Interrupts_close();  \
    else              _CPU_Virtual_Interrupts_open(); \
  }

/*
 *  Fatal Error manager macros
 *
 *  These macros perform the following functions:
 *    + disable interrupts and halt the CPU
 */

#define _CPU_Fatal_halt( _error ) \
  { \
    _CPU_Virtual_Interrupts_close(); \
    _CPU_Virtual_exec_stop_error( _error ); \
  }

#endif /* ASM */  

#ifdef __cplusplus
}
#endif

#endif /* _RTEMS_LIBCPU_CPU_H */
