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

rtems_status_code bsp_interrupt_vector_enable(rtems_vector_number vector)
{
  _CPU_Virtual_Irq_request( vector );

  return RTEMS_SUCCESSFUL;
}

rtems_status_code bsp_interrupt_vector_disable(rtems_vector_number vector)
{
  _CPU_Virtual_Irq_detach( vector );

  return RTEMS_SUCCESSFUL;
}


rtems_status_code bsp_interrupt_facility_initialize(void)
{
  return RTEMS_SUCCESSFUL;
}

void bsp_interrupt_handler_default(rtems_vector_number vector)
{
  printk( "WARNING: Somebodey forgot th register a handler for this interrupt: %u \n", vector );
}

void C_dispatch_isr(int vector)
{
  irq_count[vector]++;
  bsp_interrupt_handler_dispatch(vector);
}


void  rtems_irq_mngt_init(void)
{
   // rtems_interrupt_level       level;
    
   // rtems_interrupt_disable(level);
    
    /*
     * Init initial Interrupt management config
     */
    bsp_interrupt_initialize();
    printf("bsp_interrupt_initialize successful\n");
}
