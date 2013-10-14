/* Author:    Philipp Eppelt - philipp.eppelt@mailbox.tu-dresden.de
 *
 * COPYRIGHT (c) 2013 Philipp Eppelt.
 *
 * Purpose:   CPU part of the virtualization layer.
 * Licencse:  see RTEMS License.
 */


#ifndef RTEMS_VIRT_LAYER_CPU_H
#define RTEMS_VIRT_LAYER_CPU_H

#ifndef ASM

/* Interrupts */

/**
 * \brief Requests an interrupt vector.
 */
int
_CPU_Virtual_Irq_request( int vector );

/**
 * \brief Releases an interrupt vector.
 */
void
_CPU_Virtual_Irq_detach( int vector );

/**
 * \brief Enables interrupt delivery or sets it to the specified level.
 * 
 * Use this function in collaboration with _CPU_Virtual_Interrupts_disable and
 * use its returned _level as argument to this function to assure proper
 * behaviour.
 */
void
_CPU_Virtual_Interrupts_enable( int _level );

/**
 * \brief Disables interrupt delivery and returns the previous level.
 *
 */
void
_CPU_Virtual_Interrupts_disable( int _level );

/**
 * \brief Enables and directly disables interrupt delivery.
 */
void 
_CPU_Virtual_Interrupts_flash( int _level );

/**
 * \brief Requests the current interrupt level.
 */
int
_CPU_Virtual_Interrupts_get_level( int _level );


void
_CPU_Virtual_Interrupts_open(void);
void
_CPU_Virtual_Interrupts_close( void );

/* Idle Thread */

/**
 * \brief Lowest priority thread, doing nothing, never returns;
 */

void
_CPU_Virtual_idle_thread( void );


/* Error handling */

/**
 * \brief Handlers execution errors.
 */
void
_CPU_Virtual_exec_stop_error( int _error );

#endif /* ASM */

#endif /* RTEMS_VIRT_LAYER_CPU_H */