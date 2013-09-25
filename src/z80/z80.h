#pragma once
#ifndef __Z80_H__
#define __Z80_H__

#ifdef  TLVM_HAS_Z80
/*********************************************
 * tlvmAdd8080
 *     Add Zilog Z80 instruction set to CPU
 * parameters:
 *     context - the CPU context to add Z80 
 *     support to
 *********************************************/
TLVM_EXPORT tlvmReturn  tlvmAddZ80Instructions(tlvmContext* context);

#endif/*TLVM_HAS_Z80*/
#endif/*__Z80_H__*/