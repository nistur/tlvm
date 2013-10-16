#ifndef __8080_DEBUG_H__
#define __8080_DEBUG_H__

#ifdef  TLVM_HAS_8080
#ifdef  TLVM_DEBUG

tlvmReturn tlvm8080DebugGetInstruction(tlvmContext* context, tlvmChar** instruction);

#endif/*TLVM_DEBUG*/
#endif/*TLVM_HAS_8080*/

#endif/*__8080_DEBUG_H__*/