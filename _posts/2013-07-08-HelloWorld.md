---
title: Hello World
---

The good news first: Hello World runs!


To get there you need five steps:
1. Build the rtems-guest example in POK.
2. Copy libpart.a from rtems-guest/generated-code/cpu/part1/ to
    c/src/lib/libbsp/i386/virtPok/
3. Build virtPok bsp
4. Copy hello binary to POK partition and rebuild kernel binary
5. make run


### 1. Build the rtems-guest example

I assume you have checked out my POK fork and ran make configure.

* Change directory to ${POK}/examples/rtems-guest/
* Run make 
* Change directory to generated-code/cpu/
* Copy the last line in part1/Makefile and change rules-common in rules-libpart
* Execute 'make partitions'


### 2. Copy libpart.a

The last step created a library file called libpart.a in part1/ directory.
This file must be moved to RTEMS.

cp ${POK}/examples/rtems-guest/generated-code/cpu/part1/libpart.a \
  ${RTEMS}/c/src/lib/libbsp/i386/virtPok/


### 3. Build RTEMS

Now you are ready to build RTEMS with the virtPok BSP.

* Create a build directory next to your RTEMS directory, I assume it is called
'b-virtPok'.
* cd b-virtPok
* Configure RTEMS with the following:
  ../rtems/configure --target=i386-rtems4.11 --enable-rtemsbsp=virtPok --enable-cxx --disable-networking --disable-posix --enable-maintainer-mode
* make 

This process will sucessfully build the hello sample, but will fail on the next
one.


### 4. Copy hello sample elf and build the final kernel binary again

The compiled binary is ready to be run as a partition on POK.

Copy the compiled hello.exe ELF binary to replace the partition binary.

cp ${Builddir}/virtPok-i386/c/virtPok/testsuite/samples/hello/hello.exe \
    ${POK}/examples/rtems-guest/generated-code/cpu/part1/part1.elf


Now we need to generate the partition table again and link the kernel binary
again:

* cd ${POK}/examples/rtems-guest/generated-code/cpu/
* make build-kernel


### 5. Run qemu

Change your directory to ${POK}/examples/rtems-guest/ and execute 'make run'.

