/*
 *  This file contains the template for a console IO package.
 *
 *  COPYRIGHT (c) 2013 Philipp Eppelt.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 */

#define NO_BSP_INIT

#include <bsp.h>
#include <rtems/libio.h>
#include <virtualizationlayerbsp.h>

/**
 * @brief Initializes the console.
 */
rtems_device_driver console_initialize(
  rtems_device_major_number  major,
  rtems_device_minor_number  minor,
  void                      *arg
)
{
  rtems_status_code status;

  status = rtems_io_register_name(
    "/dev/console",
    major,
    (rtems_device_minor_number) 0
  );

  if (status != RTEMS_SUCCESSFUL)
  {
    rtems_fatal_error_occurred(status);
  }

// Virtual console init
  status = _BSP_Virtual_Console_init();

  if( status != 0 )
  {
    rtems_fatal_error_occurred(status);
  }

  return RTEMS_SUCCESSFUL;
}

/**
 * @brief Read a char from the virtual console (if supported).
 */
char inbyte( void )
{
  return _BSP_Virtual_Char_read();
}


/**
 * @brief Write a char to the virtual console.
 */
void outbyte(
  char ch
)
{
  _BSP_Virtual_Char_write(&ch);
}

/* printk support */
BSP_output_char_function_type BSP_output_char = outbyte;
BSP_polling_getchar_function_type BSP_poll_char = inbyte;


/* Console support */

/*
 * It is mostly a translation of termios intended calls to the char by char
 * printk interface.
 */

/**
 * @brief Does nothing.
 */
rtems_device_driver console_open(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void                    * arg
)
{
  return RTEMS_SUCCESSFUL;
}

/**
 * @brief Does nothing.
 */
rtems_device_driver console_close(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void                    * arg
)
{
  return RTEMS_SUCCESSFUL;
}

/*
 * read bytes from the serial port. We only have stdin.
 */

/**
 * @brief Looks like termios, but reads through inbyte() function.
 */
rtems_device_driver console_read(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void                    * arg
)
{
  rtems_libio_rw_args_t *rw_args;
  char *buffer;
  int maximum;
  int count = 0;

  rw_args = (rtems_libio_rw_args_t *) arg;

  buffer = rw_args->buffer;
  maximum = rw_args->count;

  for (count = 0; count < maximum; count++) {
    buffer[ count ] = inbyte();
    if (buffer[ count ] == '\n' || buffer[ count ] == '\r') {
      buffer[ count++ ]  = '\n';
      break;
    }
  }

  rw_args->bytes_moved = count;
  return (count >= 0) ? RTEMS_SUCCESSFUL : RTEMS_UNSATISFIED;
}

/**
 * @brief Looks like termios, but writes through outbyte() function.
 */
rtems_device_driver console_write(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void                    * arg
)
{
  int count;
  int maximum;
  rtems_libio_rw_args_t *rw_args;
  char *buffer;

  rw_args = (rtems_libio_rw_args_t *) arg;

  buffer = rw_args->buffer;
  maximum = rw_args->count;

  for (count = 0; count < maximum; count++) {
    if ( buffer[ count ] == '\n') {
      outbyte('\r');
    }
    outbyte( buffer[ count ] );
  }

  rw_args->bytes_moved = maximum;
  return 0;
}

/**
 * @brief Does nothing!
 */
rtems_device_driver console_control(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void                    * arg
)
{
  return RTEMS_SUCCESSFUL;
}
