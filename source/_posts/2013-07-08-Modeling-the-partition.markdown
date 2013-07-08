---
layout: post
title: "Memory partition and pointers"
---

I had the issue, that the file POK uses as buffer to tell the kernel what to
print on the screen, was outside of the partition. Well, outside as in the
filepointer was pointing to a memory location, which was outside the memory
slice configured in the AADL model (model.aadl).
So when modelling the partition, that should contain the guest, keep in mind to
define enough memory for the binary. 

As you can see the kernel uses the model.aadl parameters to check the partition,
even if your ELF binary is using different memory sizes. 
