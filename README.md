TLVM
====

Tiny Little Virtual Machine.

The start of a simple 8 bit virtual machine, for experimentation

Currently this is an implementation of the Intel 8080 processor, but I intend to extend it to support the z80, as well as potentially the 6502.

TODO:
-----
- Finish the 8080 instructions (56 to go!)
- Write unit tests for every instruction
- DOCUMENTATION!
- Add cpudiag from CP/M to the smoke tests
- Refactor all the unit tests to make more sense with the processor
- Add the z80 extensions
   - Allow variable sized 8 bit register array
   - Allow variable sized 16 bit registers (ie not just SP/PC)
- Add 6502 instuctions
   - Research what these are first!

What I will not do:
-------------------
- Write an assembler for this processor
- 16 bit CPUs
   - 32 bit CPUs
      - 64 bit CPUs
         - 128 bit CPUs
            - ...