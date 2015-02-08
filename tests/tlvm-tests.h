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
#ifndef __TLVM_TESTS_H__
#define __TLVM_TESTS_H__

extern "C" {
#include "tlvm_internal.h"
}

#include "testsuite/tests.h"

#define TEST_MOV_REG_REG(to, from) \
TEST(to##from, MOV, 0.0f, \
     { \
      tlvmInitContext(&m_data.context); \
      tlvm8080Init(m_data.context); \
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ); \
      m_data.bootloader[0x00] = TLVM_MOV_##to##from; \
     }, \
     { \
      tlvmTerminateContext(&m_data.context); \
     }, \
     { \
          tlvmReset(m_data.context); \
          tlvmByte cycles = 0; \
          m_data.context->m_Registers[TLVM_REG_##from] = 99; \
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS); \
          ASSERT(m_data.context->m_Registers[TLVM_REG_##to] == 99); \
          ASSERT(cycles == 5); \
     }, \
     { \
      tlvmContext* context; \
      tlvmByte     bootloader[255]; \
     } \
    );

#define TEST_MOV_REG_MEM(to) \
TEST(to##M, MOV, 0.0f, \
     { \
      tlvmInitContext(&m_data.context); \
      tlvm8080Init(m_data.context); \
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ); \
      tlvmSetMemory(m_data.context, m_data.memory, 0x100, 0xFF, TLVM_FLAG_READ|TLVM_FLAG_WRITE); \
      m_data.bootloader[0x00] = TLVM_MOV_##to##M; \
     }, \
     { \
      tlvmTerminateContext(&m_data.context); \
     }, \
     { \
          tlvmReset(m_data.context); \
          tlvmByte cycles = 0; \
          m_data.context->m_Registers[TLVM_REG_H] = 0x01; \
          m_data.memory[0x00] = 99; \
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS); \
          ASSERT(m_data.context->m_Registers[TLVM_REG_##to] == 99); \
          ASSERT(cycles == 7); \
     }, \
     { \
      tlvmContext* context; \
      tlvmByte     bootloader[255]; \
      tlvmByte     memory[255]; \
     } \
    );

#define TEST_MOV_MEM_REG(from) \
TEST(M##from, MOV, 0.0f, \
     { \
      tlvmInitContext(&m_data.context); \
      tlvm8080Init(m_data.context); \
      tlvmSetMemory(m_data.context, m_data.bootloader, 0, 0xFF, TLVM_FLAG_READ); \
      tlvmSetMemory(m_data.context, m_data.memory, 0x100, 0xFF, TLVM_FLAG_READ|TLVM_FLAG_WRITE); \
      m_data.bootloader[0x00] = TLVM_MOV_M##from; \
     }, \
     { \
      tlvmTerminateContext(&m_data.context); \
     }, \
     { \
          tlvmReset(m_data.context); \
          tlvmByte cycles = 0; \
          m_data.context->m_Registers[TLVM_REG_##from] = 0x01; \
          m_data.context->m_Registers[TLVM_REG_H] = 0x01; \
          ASSERT(tlvmStep(m_data.context, &cycles) == TLVM_SUCCESS); \
          ASSERT(m_data.memory[0x00] == 0x01); \
          ASSERT(cycles == 7); \
     }, \
     { \
      tlvmContext* context; \
      tlvmByte     bootloader[255]; \
      tlvmByte     memory[255]; \
     } \
    );

#endif/*__TLVM_TESTS_H__*/
