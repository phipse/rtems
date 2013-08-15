/**
 *  @file
 *
 *  @brief Virtualization Sensitive i386 Dependent Source
 *
 *  Part of cpu.c that must be replaced with a virtualization acceptable way to
 *  idle. On i386 "hlt" is used, which is priviledged and causes a GPF.
 */

/*
 *  COPYRIGHT (c) Philipp Eppelt.
 *    philipp.eppelt@mailbox.tu-dresden.de
 */

#include <rtems/score/cpu.h>	// function definition
#include <virtualizationlayercpu.h>

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
    _CPU_Virtual_idle_thread();
  }
  return NULL;
}
