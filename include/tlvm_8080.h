/*
Copyright (c) 2015 Philipp Geyer

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Philipp Geyer
nistur@gmail.com
*/

#ifndef __TLVM_8080_H__
#define __TLVM_8080_H__

#ifdef  TLVM_HAS_8080

#ifndef __TLVM_H__
#error Do not #include tlvm_8080.h manually, please use tlvm.h
#endif

typedef void(*tlvm8080IOCallback)(tlvmContext* context, tlvmByte port);

/*********************************************
 * tlvm8080Init
 *     Setup the entire 8080 CPU. This will
 * initialise all the registers and I/O ports 
 * and then setup the instruction set
 * parameters:
 *     context - the CPU context to add 8080 
 * support to
 *********************************************/
TLVM_EXPORT tlvmReturn  tlvm8080Init  (tlvmContext* context);

/*********************************************
 * tlvm8080SetIOCallback
 *     Provides a callback for when any of the
 *   8080's ports have been written to.
 * parameters:
 *     context - the CPU context to add the
 *   callback to
 *     callback - the function pointer of the
 *   callback
 *********************************************/
TLVM_EXPORT tlvmReturn  tlvm8080SetIOCallback(tlvmContext* context, tlvm8080IOCallback callback);

#endif/*TLVM_HAS_8080*/

#endif/*__TLVM_ALU_H__*/