#include <bsp/irq-generic.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h> /* PRIu32 */
#include <virtualizationlayerbsp.h>

uint32_t            irq_count[BSP_IRQ_LINES_NUMBER] = {0};

uint32_t
BSP_irq_count_dump(FILE *f)
{
  uint32_t tot = 0;
  int      i;
  if ( !f )
    f = stdout;
  for ( i=0; i<BSP_IRQ_LINES_NUMBER; i++ ) {
    tot += irq_count[i];
    fprintf(f,"IRQ %2u: %9"PRIu32"\n", i, irq_count[i]);
  }
  return tot;
}

/**
 * @brief Enable vector line at interrupt source. See description!
 *
 * Currently this is only a dummy function, as registering the vector on POK
 * will deliver interrupts before the handler is installed. So the driver
 * needing the interrupt needs to call _CPU_Virtual_Irq_attach().
 */
rtems_status_code bsp_interrupt_vector_enable(rtems_vector_number vector)
{

  return RTEMS_SUCCESSFUL;
}

/**
 * @brief Disabling vector line at interrupt source.
 */
rtems_status_code bsp_interrupt_vector_disable(rtems_vector_number vector)
{
  _CPU_Virtual_Irq_detach( vector );

  return RTEMS_SUCCESSFUL;
}

/**
 * @brief Dummy function; necessary for a normal startup.
 */
rtems_status_code bsp_interrupt_facility_initialize(void)
{
  return RTEMS_SUCCESSFUL;
}

/**
 * @brief If no interrupt handler is installed for a specified vector number,
 * this is called and will output a warning.
 */
void bsp_interrupt_handler_default(rtems_vector_number vector)
{
  printk( "WARNING: Somebody forgot to register a handler for this interrupt: %x \n", vector );
}

/**
 * @brief Forwards the interrupt to bsp_interrupt_handler_dispatch to look for
 * the right handler.
 */
void C_dispatch_isr(int vector)
{
  irq_count[vector]++;
  bsp_interrupt_handler_dispatch(vector);
}

/**
 * @brief Initializes interrupts management.
 *
 * Called by bsp_start(), does all necessary IRQ initialization. 
 */
void  rtems_irq_mngt_init(void)
{
    /*
     * Init initial Interrupt management config
     */
    bsp_interrupt_initialize();
    printf("bsp_interrupt_initialize successful\n");
}
