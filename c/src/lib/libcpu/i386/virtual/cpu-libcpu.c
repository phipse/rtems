/**
 *  @file
 *
 *  @brief Virtualization Sensitive Intel i386 Dependent Source
 *
 *  Part of cpu.c that must be replaced with a virtualization acceptable way to
 *  idle. On i386 "hlt" is used, which is priviledged and causes a GPF.
 */

// TODO add includes
#include <rtems/score/types.h>



/**
 * @brief Idle thread calls virtualized idle function
 *
 *
 */

void *_CPU_Thread_Idle_body( uintptr_t ignored )
{
  while(1)
  {
  // replace with call to virtualization layer  
    __asm__ volatile ("hlt");
  }
  return NULL;
}
