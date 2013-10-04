#pragma once
#ifndef __8132A_H__
#define __8132A_H__

/* Register structure
 * 0x00 flags
 * 0x01 Stack AU
 * 0x02
 * 0x03 Stack AL
 * 0x04
 * 0x05 Stack BU
 * 0x06
 * 0x07 Stack BL
 * 0x08
 * 0x09 Stack CU
 * 0x0A
 * 0x0B Stack CL
 * 0x0C
 * 0x0D Stack CU
 * 0x0E
 * 0x0F Stack CL
 * 0x10
 */

#define TLVM_8132A_REG_F       0x00
#define TLVM_8132A_STACK_START 0x01
#define TLVM_8132A_STACK_END   0x0F

#endif/*__8132A_H__*/
