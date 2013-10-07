#pragma once
#ifndef __8231A_H__
#define __8231A_H__

#ifdef  TLVM_HAS_8231A

/* Register structure
 * 0x00 Stack AU
 * 0x01
 * 0x02 Stack AL
 * 0x03
 * 0x04 Stack BU
 * 0x05
 * 0x06 Stack BL
 * 0x07
 * 0x08 Stack CU
 * 0x09
 * 0x0A Stack CL
 * 0x0B
 * 0x0C Stack DU
 * 0x0D
 * 0x0E Stack DL
 * 0x0F
 * 0x10 flags
 * 0x11 command
 * 0x12 state
 */

#define TLVM_8231A_STACK_START 0x00
#define TLVM_8231A_STACK_END   0x0F
#define TLVM_8231A_REG_F       0x10
#define TLVM_8231A_COMMAND     0x11
#define TLVM_8231A_STATE       0x12


/*********************************************
 * States
 *********************************************/
#define TLVM_8231A_STATE_ACTIVE     0x00
#define TLVM_8231A_STATE_WAIT       0x01
#define TLVM_8231A_STATE_WAIT_READ  0x02
#define TLVM_8231A_STATE_WAIT_WRITE 0x03
#define TLVM_8231A_STATE_WAIT_CMD   0x04
#define TLVM_8231A_STATE_WAIT_END   0x05

/*********************************************
 * Ports
 *   for the 8231A, the ports are being used to
 * represent the chip pins. Frustratingly they
 * don't appear to be arranged nicely, as
 * DB0-DB7 (the data bus) starts on pin 8, 
 * which would mean that data input would be
 * spread over two bytes. There are a number
 * of pins that aren't relevant in our 
 * situation so byte0 will contain pins 0-6, 
 * which include the service request bits,
 * byte1 contains pins 7-14, the data bus byte
 * and byte2 contains pins 16-23, which
 * includes read, write, chip select and
 * address pins. In this way only pin 15 is
 * not represented, which is VDD (+12V power)
 *********************************************/
#define TLVM_8231A_PORT_SVR    0x0 // pins 0-6
#define TLVM_8231A_PORT_DB	   0x1 // pins 7-14
#define TLVM_8231A_PORT_CMD    0x2 // pins 16-23

// PORT 0
#define TLVM_8231A_SVR_EACK    (1 << 0x2) // End of execution Acknowledge
#define TLVM_8231A_SVR_SVACK   (1 << 0x3) // Service Request Acknowledge
#define TLVM_8231A_SVR_SVREQ   (1 << 0x4) // Service Request

// PORT 1
// no separate pins, this port represents the data bus

// PORT 2
#define TLVM_8231A_CMD_READY   (1 << 0x0) // Ready
#define TLVM_8231A_CMD_CS      (1 << 0x1) // Chip Select
#define TLVM_8231A_CMD_WR      (1 << 0x2) // Write
#define TLVM_8231A_CMD_RD      (1 << 0x3) // Read
#define TLVM_8231A_CMD_A0      (1 << 0x4) // command data
#define TLVM_8231A_CMD_RESET   (1 << 0x5) // Reset
#define TLVM_8231A_CMD_END     (1 << 0x7) // End of execution

#define TLVM_8231A_PIN_HIGH(port, pin) ((context->m_Ports[TLVM_8231A_PORT_##port] & TLVM_8231A_##port##_##pin))
#define TLVM_8231A_PIN_LOW(port, pin)  (!TLVM_8231A_PIN_HIGH(port, pin))

#define TLVM_8231A_SET_PIN_HIGH(port, pin) (context->m_Ports[TLVM_8231A_PORT_##port] |=  TLVM_8231A_##port##_##pin)
#define TLVM_8231A_SET_PIN_LOW(port, pin)  (context->m_Ports[TLVM_8231A_PORT_##port] &= ~TLVM_8231A_##port##_##pin)


/*********************************************
 * Instructions
 *********************************************/ 
 #define TLVM_8231A_NOP   0x00
 #define TLVM_8231A_POPS  0x78
 #define TLVM_8231A_PTOS  0x77
 #define TLVM_8231A_SADD  0x6C
 #define TLVM_8231A_SSUB  0x6D

tlvmReturn tlvm8231ANOP (tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvm8231APOPS(tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvm8231APTOS(tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvm8231ASADD(tlvmContext* context, tlvmByte* cycles);
tlvmReturn tlvm8231ASSUB(tlvmContext* context, tlvmByte* cycles);

/*********************************************
 * tlvmAdd8080
 *     Add Intel 8080 instruction set to CPU
 * parameters:
 *     context - the CPU context to add 8080 
 *     support to
 *********************************************/
tlvmReturn tlvmAdd8231AInstructions(tlvmContext* context);

tlvmReturn tlvm8231Step(tlvmContext* context, tlvmByte* cycles);

void     tlvm8231AStackPush(tlvmContext* context, tlvmByte val);
tlvmByte tlvm8231AStackPop(tlvmContext* context);

#endif/*TLVM_HAS_8231A*/

#endif/*__8231A_H__*/
