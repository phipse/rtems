/**
 *  @file
 *
 *  @brief Virtualization Sensitive Intel i386 Dependent Source
 *
 *  Part of cpu.c that must be replaced with a virtualization acceptable way to
 *  idle. On i386 "hlt" is used, which is priviledged and causes a GPF.
 */


#ifdef __cplusplus
extern "C" {
#endif


#include <rtems/score/cpu.h>	// function definition



/**
 * @brief Idle thread executes idle operation
 *
 * If used in a virtualized environment, this executes a call to the
 * virtualization layer.
 */

void *_CPU_Thread_Idle_body( uintptr_t ignored )
{
  while(1)
  {
    __asm__ volatile ("hlt");
  }
  return NULL;
}


#ifdef __cpluplus
}
#endif 
