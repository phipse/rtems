---
layout: post
title: "Midterm explanation"
date: 2013-07-30 11:42
comments: true
categories: 
---

It is midterm evaluation time, so half the time is up and I want to write about
the changes I bring into the RTEMS project. This post will explain the patch I
created for midterm.


<!--break-->


## Overview

I brought one major change to the project, the split of the i386 architecture
dependent code into a part in score and another part in libcpu.
Compared to this the virtualization layer consisting of two header files, one
for CPU dependent functionality and on for board dependent, is rather small.
The introduction of the new BSP called virtPOK is a bigger change, but still,
it only affects this project and not all building upon the i386 architecture. 


## i386 split

i386 has several instructions (hlt, cli, sti) which are not allowed in a 
virtualized environment, as they affect other virtual machines. Functions in 
cpukit/score/cpu/i386/ are using these instruction and therefore need to be 
moved. However, these functions must remain in the native version of an RTEMS
i386 binary, but must be replaced with different implementations in a virtual
compilation.
RTEMS is providing with libcpu a place where CPUs with special features of the
same architecture can be specified. That is the place where the native and
virtual implementations of the mentioned functions need to go.
I introduced two new CPU models for the i386 architecture - native and virtual.
Native is used by the pc386-BSPs and should work like before. Virtual is the
new kid in the block and is only used by the virtPok BSP.
Configure.ac is controlling the choice of the bsp. As the config file for a BSP
specifies the CPU model, the virtPok.cfg is specifying ***virt-pok*** as CPU.
Configure.ac checks for this CPU model and sets a conditional if this model is
used. The conditional controls the path of execution in the corresponding 
Makefile.am, which in turn chooses the virtual or native directory.


## Virtualization layer

The virtualization layer consists of two parts: One for the CPU and one for the
BSP. My intention for the layer is to provide on BSP using the functionality of
the layer and then the layer must be implemented by the host/hypervisor and
provided as a library to RTEMS.
The CPU part needs to be implemented in RTEMS once for each architecture. The
BSP currently developed for i386 might be reusable on other architectures, as
the host cares for architecture dependent parts.
Both header files virtLayerBSP.h and virtLayerCPU.h can be found in
c/src/lib/libbsp/i386/virtPok/include/ .


## Virtual BSP

The virtual BSP for i386 is called virtPok and is currently able to run the
hello world sample virtualized on POK. The BSP mimics the interface between
RTEMS and the host/hypervisor, by forwarding the RTEMS function calls to the
virtualization layer, which is implemented by the host and provided as a
library to the BSP. Currently implemented is a console driver to run the hello
world sample. A clock driver will be the next step but this needs changes in 
POK first. 


## Putting it all together

To rebuild the current work, you can either checkout my virt-bsp branch from:
github: https://github.com/phipse/rtems
Or you can apply the patches from the rtems-devel mailing list to the current
RTEMS git head. 

Then you need to follow my explanations from the [Hello
World](http://phipse.github.io/rtems/blog/2013/07/08/HelloWorld/ "Hello World") 
blog post.
Unfortunately, you need to build RTEMS with **make -j1** as parallel
compilation can lead to undefined reference errors.
