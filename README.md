# TLVM

Tiny Little Virtual Machine.

The start of a simple 8 bit virtual machine, for experimentation

Currently this is an implementation of the Intel 8080 processor, but I intend to extend it to support the z80, as well as potentially the 6502.

## Debugger

## Samples
There some samples provided to test a number of the functionalities of the system. They each expect a number of things set up for them to run successfully.

### Hello World
Filename: demo/8080/Hello.bin
Expects stdio port 1 and stdio status port 2, raising 0x01 when ready to output character
Sample tlvm-dbg commands:
	file demo/8080/Hello.bin 0x0000
	memory 0x0100 256
	stdio 1 2
	run

### Fibonacci Generator
Filename: demo/8080/Fibonacci.bin
Expects value watcher port 1 and value watcher status port 2, raising 0x01 when ready to output character
Sample tlvm-dbg commands:
	file demo/8080/Fibonacci.bin 0x0000
	memory 0x0100 256
	watch 1 2
	run

## TODO:
- Make sure it builds and runs on Windows
   - Currently should just be dbg.cpp and time.c that doesn't work
- Finish the 8080 instructions
- Write unit tests for every instruction
- DOCUMENTATION!
- Add cpudiag from CP/M to the smoke tests
   - cpudiag runs cleanly for all 8080 instructions, but I don't think I can add it to the smoke tests, I can't seem to find which license it was provided under. I don't think it's something I can use
- Refactor all the unit tests to make more sense with the processor
- Add the z80 extensions
   - Allow variable sized 8 bit register array
   - Allow variable sized 16 bit registers (ie not just SP/PC)
- Add 6502 instuctions
   - Research what these are first!
- Add 6303 instructions
   - Try and find documentation for this
- Make tlvm threadsafe.
   - This should be safe enough to do by putting a byte in the context and checking it when something changes the state (interrupt, reset, step)

## What I will not do:
- Write an assembler for this processor
- 16 bit CPUs
   - 32 bit CPUs
      - 64 bit CPUs
         - 128 bit CPUs
            - ...