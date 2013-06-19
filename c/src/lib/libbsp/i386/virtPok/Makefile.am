##
## $Id$
##

ACLOCAL_AMFLAGS = -I ../../../../aclocal

include $(top_srcdir)/../../../../automake/compile.am
include $(top_srcdir)/../../bsp.am

include_bspdir = $(includedir)/bsp

dist_project_lib_DATA = bsp_specs

include_HEADERS = include/bsp.h
include_HEADERS += ../../shared/include/tm27.h
include_HEADERS += include/virtLayerBSP.h
include_HEADERS += include/virtLayerCPU.h

nodist_include_HEADERS = include/bspopts.h
nodist_include_bsp_HEADERS = ../../shared/include/bootcard.h
DISTCLEANFILES = include/bspopts.h
noinst_PROGRAMS =

nodist_include_HEADERS += ../../shared/include/coverhd.h

dist_project_lib_DATA += startup/linkcmds

noinst_LIBRARIES = libbsp.a
libbsp_a_SOURCES =

# startup
libbsp_a_SOURCES += ../../shared/bspclean.c
libbsp_a_SOURCES += ../../shared/bsplibc.c 
libbsp_a_SOURCES += ../../shared/bsppretaskinghook.c 
libbsp_a_SOURCES += ../../shared/bsppredriverhook.c 
libbsp_a_SOURCES += start/bspgetworkarea.c
libbsp_a_SOURCES += ../../shared/bsppost.c
libbsp_a_SOURCES += startup/bspstart.c 
libbsp_a_SOURCES += ../../shared/bootcard.c 
libbsp_a_SOURCES += ../../shared/sbrk.c 
libbsp_a_SOURCES += startup/setvec.c 
libbsp_a_SOURCES += ../../shared/gnatinstallhandler.c 
libbsp_a_SOURCES += ../../shared/bspreset.c 
libbsp_a_SOURCES += start/start.c
# TODO I don't really need an IDT, don't I?
libbsp_a_SOURCES += ../../i386/shared/irq/idt.c

# clock
libbsp_a_SOURCES += clock/ckinit.c
# console
libbsp_a_SOURCES += console/console.c
# timer
libbsp_a_SOURCES += timer/timer.c timer/timerisr.c

libbsp_a_LIBADD = ../../../libcpu/@RTEMS_CPU@/cache.rel
libbsp_a_LIBADD += ../../../libcpu/@RTEMS_CPU@/page.rel
libbsp_a_LIBADD += ../../../libcpu/@RTEMS_CPU@/score.rel

noinst_LIBRARIES += libpokpart.a

libpokpart.a : 
	cp -u $(top_srcdir)/libpart.a .
	ar t libpart.a > libpart.list
	sed -e "s/\.lo/\.o/g" libpart.list > libpart.o.list
	ar x libpart.a
	rename .lo .o `cat libpart.list`
	ar cru libpokpart.a `cat libpart.o.list`
# rm `cat libpart.o.list` is optional as all files get overwritten with new
# ones by 'ar x'. But I think it's bad style to remove object files during 
# compilation.


#libpokpart_a_LIBADD = libpart.a


EXTRA_DIST = times

include $(srcdir)/preinstall.am
include $(top_srcdir)/../../../../automake/local.am
