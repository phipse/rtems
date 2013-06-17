## Process this file with autoconf to produce a configure script.
##
## $Id$

AC_PREREQ([2.68])
AC_INIT([rtems-c-src-lib-libbsp-i386-virtPok],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([bsp_specs])
RTEMS_TOP(../../../../../..)

RTEMS_CANONICAL_TARGET_CPU
AM_INIT_AUTOMAKE([no-define nostdinc foreign 1.12.2])
RTEMS_BSP_CONFIGURE

RTEMS_PROG_CC_FOR_TARGET
RTEMS_CANONICALIZE_TOOLS
RTEMS_PROG_CCAS

AC_SUBST([RTEMS_ROOT],[${rtems_updir}'$(top_builddir)'])

RTEMS_BSP_CLEANUP_OPTIONS(0, 0)

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
