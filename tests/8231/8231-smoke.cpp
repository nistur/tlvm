#include "../tlvm-tests.h"
#include <stdio.h>

#define START_PROGRAM() int _programCounter = 0;
// technically we don't need the address here, as the program counter
// handles that, but if we ommit it, it's very difficult to work out
// JMP instructions manually, and it's a useful check that the addresses
// are what we expect
#define NEXT(addr, val) \
{ \
  if(addr != _programCounter) printf("WARNING: Incorrect address\n"); \
  m_data.program[_programCounter] = val; \
  _programCounter++; \
}

TEST_8231(SADD, Smoke, 0.0f,
{
  tlvmInitContext(&m_data.CPU);
  tlvmInitContext(&m_data.APU);
  tlvmInit8080(m_data.CPU);
  tlvmInit8231A(m_data.APU);

  tlvmSetClockspeed(m_data.CPU, TLVM_MHZ(2,0));
  tlvmSetClockspeed(m_data.APU, TLVM_MHZ(2,0));
  tlvmSetMemory(m_data.CPU, m_data.program, 0, 512, TLVM_FLAG_READ | TLVM_FLAG_WRITE);
  tlvmByte* svr = 0;
  tlvmByte* db = 0;
  tlvmByte* cmd = 0;
  tlvmGetPort(m_data.APU, 0, &svr);
  tlvmGetPort(m_data.APU, 1, &db);
  tlvmGetPort(m_data.APU, 2, &cmd);
  tlvmSetMemory(m_data.CPU, svr, 512, 1, TLVM_FLAG_READ | TLVM_FLAG_WRITE);
  tlvmSetMemory(m_data.CPU, db, 513, 1, TLVM_FLAG_READ | TLVM_FLAG_WRITE);
  tlvmSetMemory(m_data.CPU, cmd, 514, 1, TLVM_FLAG_READ | TLVM_FLAG_WRITE);

  /* Rough pseudo-ASM of what this will do
    JMP MAIN
  SET_LOW:
    PUSH B
    PUSH PSW
    MVI A,0xFF
    XRA B
    MOV B,A
    MOV A,[HL]
    ANA B
    MOV [HL],B
    POP PSW
    POP B
    RET
  SET_HIGH:
    PUSH PSW
    MOV A,[HL]
    ORA B
    MOV [HL],A
    POP PSW
    RET
  WAIT_FOR_LOW:
    PUSH B
    PUSH PSW
    MOV B,A
  WAIT_FOR_LOW_LOOP
    MOV A,[HL]
    CMP B
    JNZ WAIT_FOR_LOW_LOOP
    PUSH PSW
    POP B
    RET
  WAIT_FOR_HIGH:
    PUSH B
    MOV B,A
    PUSH A
  WAIT_FOR_HIGH_LOOP
    MOV A,[HL]
    CMP B
    JZ WAIT_FOR_HIGH_LOOP
    POP A
    POP B
    RET
  START_WRITE_DATA:
    PUSH PSW
    PUSH H
    LXI H,0x0102 ;; Point to CMD port
    MVI B,0x02 ;; CS pin
    CALL SET_LOW
    MVI B,0x10 ;; A0 pin
    CALL SET_LOW
    MVI B,0x04 ;; WR pin
    CALL SET_LOW
    MVI B,0x01 ;; READY pin
    CALL WAIT_FOR_LOW
    PUSH H
    POP PSW
    RET
  START_WRITE_CMD:
    PUSH PSW
    PUSH H
    LXI H,0x0102 ;; Point to CMD port
    MVI B,0x02 ;; CS pin
    CALL SET_LOW
    MVI B,0x10 ;; A0 pin
    CALL SET_HIGH
    MVI B,0x04 ;; WR pin
    CALL SET_LOW
    MVI B,0x01 ;; READY pin
    CALL WAIT_FOR_LOW
    PUSH H
    POP PSW
    RET
  END_WRITE_DATA:
    PUSH PSW
    PUSH H
    LXI H,0x0102 ;; Point to CMD port
    MVI B,0x04 ;; WR pin
    CALL SET_HIGH
    MVI B,0x10 ;; A0 pin
    CALL SET_HIGH
    MVI B,0x02 ;; CS pin
    CALL SET_HIGH
    POP H
    POP PSW
    RET
  END_WRITE_CMD:
    PUSH PSW
    PUSH H
    LXI H,0x0102 ;; Point to CMD port
    MVI B,0x04 ;; RWR pin
    CALL SET_HIGH
    MVI B,0x10 ;; A0 pin
    CALL SET_LOW
    MVI B,0x02 ;; CS pin
    CALL SET_HIGH
    MVI B,0x40
    CALL WAIT_FOR_LOW
    LXI H,0x0100 ;; Point to SVR port
    MVI B,0x04
    CALL SET_LOW
    LXI H,0x0102 ;; Point to CMD port
    MVI B,0x40
    CALL WAIT_FOR_HIGH
    LXI H,0x0100 ;; Point to SVR port
    MVI B,0x04
    CALL SET_HIGH
    POP H
    POP PSW
    RET
  WRITE:
    PUSH PSW
    MOV A,C
    CPI 1
    CZ START_WRITE_DATA
    CNZ START_WRITE_CMD
    POP PSW
    PUSH H
    LXI H,0x0101
    MOV A[HL]
    POP H
    PUSH PSW
    MOV A,C
    CPI 1
    CZ END_WRITE_DATA
    CNZ END_WRITE_CMD
    POP PSW
    RET
  READ:
    PUSH H
    LXI H,0x0102
    MVI B,0x02 ;; CS pin
    CALL SET_LOW
    MVI B,0x10 ;; A0 pin
    CALL SET_LOW
    MVI B,0x08 ;; RD pin
    CALL SET_LOW
    MVI B,0x01 ;; READY pin
    CALL WAIT_FOR_LOW
    MVI B,0x08 ;; RD pin
    CALL SET_HIGH
    LXI H,0x0101
    MOV C,[HL]
    MVI B,0x10 ;; A0 pin
    CALL SET_HIGH
    MVI B,0x02 ;; CS pin
    CALL SET_HIGH
    POP H
    RET
  MAIN:
  // ------- SET STACK POINTER!
    MVI C,0x01
    MVI A,0x00
    CALL WRITE
    MVI A,0xFF
    CALL WRITE
    MVI A,0x00
    CALL WRITE
    MVI A,0x1F
    CALL WRITE
    MVI C,0x00
    MVI A,0x6C
    CALL WRITE
    CALL READ
    MOV A,C
    OUT 1
  */
  START_PROGRAM();
  NEXT(0x0000, TLVM_JMP); // JMP MAIN
  NEXT(0x0001, 0xF7);
  NEXT(0x0002, 0x00);
  NEXT(0x0003, TLVM_PUSH_B); // SET_LOW
  NEXT(0x0004, TLVM_PUSH_PSW);
  NEXT(0x0005, TLVM_MVI_A);
  NEXT(0x0006, 0xFF);
  NEXT(0x0007, TLVM_XRA_B);
  NEXT(0x0008, TLVM_MOV_BA);
  NEXT(0x0009, TLVM_MOV_AM);
  NEXT(0x000A, TLVM_ANA_B);
  NEXT(0x000B, TLVM_MOV_MA);
  NEXT(0x000C, TLVM_POP_PSW);
  NEXT(0x000D, TLVM_POP_B);
  NEXT(0x000E, TLVM_RET);
  NEXT(0x000F, TLVM_PUSH_PSW); // SET_HIGH
  NEXT(0x0010, TLVM_MOV_AM);
  NEXT(0x0011, TLVM_ORA_B);
  NEXT(0x0012, TLVM_MOV_MA);
  NEXT(0x0013, TLVM_POP_PSW);
  NEXT(0x0014, TLVM_RET);
  NEXT(0x0015, TLVM_PUSH_B); // WAIT_FOR_LOW
  NEXT(0x0016, TLVM_PUSH_PSW);
  NEXT(0x0017, TLVM_MOV_BA);
  NEXT(0x0018, TLVM_MOV_AM); // WAIT_FOR_LOW_LOOP
  NEXT(0x0019, TLVM_CMP_B);
  NEXT(0x001A, TLVM_JNZ); // JNZ WAIT_FOR_LOW_LOOP
  NEXT(0x001B, 0x18);
  NEXT(0x001C, 0x00);
  NEXT(0x001D, TLVM_POP_PSW);
  NEXT(0x001E, TLVM_POP_B);
  NEXT(0x001F, TLVM_RET);
  NEXT(0x0020, TLVM_PUSH_B); // WAIT_FOR_HIGH
  NEXT(0x0021, TLVM_MOV_BA);
  NEXT(0x0022, TLVM_PUSH_PSW);
  NEXT(0x0023, TLVM_MOV_AM); // WAIT_FOR_HIGH_LOOP
  NEXT(0x0024, TLVM_CMP_B);
  NEXT(0x0025, TLVM_JZ); // JZ WAIT_FOR_HIGH_LOOP
  NEXT(0x0026, 0x23);
  NEXT(0x0027, 0x00);
  NEXT(0x0028, TLVM_POP_PSW);
  NEXT(0x0029, TLVM_POP_B);
  NEXT(0x002A, TLVM_RET);
  NEXT(0x002B, TLVM_PUSH_PSW); // START_WRITE_DATA
  NEXT(0x002C, TLVM_PUSH_H);
  NEXT(0x002D, TLVM_LXI_H);
  NEXT(0x002E, 0x02);
  NEXT(0x002F, 0x02);
  NEXT(0x0030, TLVM_MVI_B);
  NEXT(0x0031, 0x02);
  NEXT(0x0032, TLVM_CALL); // CALL SET_LOW
  NEXT(0x0033, 0x03);
  NEXT(0x0034, 0x00);
  NEXT(0x0035, TLVM_MVI_B);
  NEXT(0x0036, 0x10);
  NEXT(0x0037, TLVM_CALL);
  NEXT(0x0038, 0x03);
  NEXT(0x0039, 0x00);
  NEXT(0x003A, TLVM_MVI_B);
  NEXT(0x003B, 0x04);
  NEXT(0x003C, TLVM_CALL);
  NEXT(0x003D, 0x03);
  NEXT(0x003E, 0x00);
  NEXT(0x003F, TLVM_MVI_B);
  NEXT(0x0040, 0x01);
  NEXT(0x0041, TLVM_CALL); // CALL WAIT_FOR_LOW
  NEXT(0x0042, 0x15);
  NEXT(0x0043, 0x00);
  NEXT(0x0044, TLVM_POP_H);
  NEXT(0x0045, TLVM_POP_PSW);
  NEXT(0x0046, TLVM_RET);
  NEXT(0x0047, TLVM_PUSH_PSW); // START_WRITE_CMD
  NEXT(0x0048, TLVM_PUSH_H);
  NEXT(0x0049, TLVM_LXI_H);
  NEXT(0x004A, 0x02);
  NEXT(0x004B, 0x02);
  NEXT(0x004C, TLVM_MVI_B);
  NEXT(0x004D, 0x02);
  NEXT(0x004E, TLVM_CALL); // CALL SET_LOW
  NEXT(0x004F, 0x03);
  NEXT(0x0050, 0x00);
  NEXT(0x0051, TLVM_MVI_B);
  NEXT(0x0052, 0x10);
  NEXT(0x0053, TLVM_CALL); // CALL SET_HIGH
  NEXT(0x0054, 0x0F);
  NEXT(0x0055, 0x00);
  NEXT(0x0056, TLVM_MVI_B);
  NEXT(0x0057, 0x04);
  NEXT(0x0058, TLVM_CALL); // CALL SET_LOW
  NEXT(0x0059, 0x03);
  NEXT(0x005A, 0x00);
  NEXT(0x005B, TLVM_MVI_B);
  NEXT(0x005C, 0x01);
  NEXT(0x005D, TLVM_CALL); // CALL WAIT_FOR_LOW
  NEXT(0x005E, 0x15);
  NEXT(0x005F, 0x00);
  NEXT(0x0060, TLVM_POP_H);
  NEXT(0x0061, TLVM_POP_PSW);
  NEXT(0x0062, TLVM_RET); 
  NEXT(0x0063, TLVM_PUSH_PSW); // END_WRITE_DATA
  NEXT(0x0064, TLVM_PUSH_H);
  NEXT(0x0065, TLVM_LXI_H);
  NEXT(0x0066, 0x02);
  NEXT(0x0067, 0x02);
  NEXT(0x0068, TLVM_MVI_B);
  NEXT(0x0069, 0x04);
  NEXT(0x006A, TLVM_CALL); // CALL SET_HIGH
  NEXT(0x006B, 0x0F);
  NEXT(0x006C, 0x00);
  NEXT(0x006D, TLVM_MVI_B);
  NEXT(0x006E, 0x10);
  NEXT(0x006F, TLVM_CALL); // CALL SET_HIGH
  NEXT(0x0070, 0x0F);
  NEXT(0x0071, 0x00);
  NEXT(0x0072, TLVM_MVI_B);
  NEXT(0x0073, 0x02);
  NEXT(0x0074, TLVM_CALL);
  NEXT(0x0075, 0x0F);
  NEXT(0x0076, 0x00);
  NEXT(0x0077, TLVM_POP_H);
  NEXT(0x0078, TLVM_POP_PSW);
  NEXT(0x0079, TLVM_RET);
  NEXT(0x007A, TLVM_PUSH_PSW); // END_WRITE_CMD
  NEXT(0x007B, TLVM_PUSH_H);
  NEXT(0x007C, TLVM_LXI_H);
  NEXT(0x007D, 0x02);
  NEXT(0x007E, 0x02);
  NEXT(0x007F, TLVM_MVI_B);
  NEXT(0x0080, 0x04);
  NEXT(0x0081, TLVM_CALL); // CALL SET_HIGH
  NEXT(0x0082, 0x0F);
  NEXT(0x0083, 0x00);
  NEXT(0x0084, TLVM_MVI_B);
  NEXT(0x0085, 0x10);
  NEXT(0x0086, TLVM_CALL); // CALL SET_LOW
  NEXT(0x0087, 0x03);
  NEXT(0x0088, 0x00);
  NEXT(0x0089, TLVM_MVI_B);
  NEXT(0x008A, 0x02);
  NEXT(0x008B, TLVM_CALL); // CALL SET_HIGH
  NEXT(0x008C, 0x0F);
  NEXT(0x008D, 0x00);
  NEXT(0x008E, TLVM_MVI_B);
  NEXT(0x008F, 0x40);
  NEXT(0x0090, TLVM_CALL); // CALL WAIT_FOR_LOW
  NEXT(0x0091, 0x15);
  NEXT(0x0092, 0x00);
  NEXT(0x0093, TLVM_LXI_H);
  NEXT(0x0094, 0x00);
  NEXT(0x0095, 0x02);
  NEXT(0x0096, TLVM_MVI_B);
  NEXT(0x0097, 0x04);
  NEXT(0x0098, TLVM_CALL); // CALL SET_LOW
  NEXT(0x0099, 0x03);
  NEXT(0x009A, 0x00);
  NEXT(0x009B, TLVM_LXI_H);
  NEXT(0x009C, 0x02);
  NEXT(0x009D, 0x02);
  NEXT(0x009E, TLVM_MVI_B);
  NEXT(0x009F, 0x40);
  NEXT(0x00A0, TLVM_CALL); // CALL WAIT_FOR_HIGH
  NEXT(0x00A1, 0x20);
  NEXT(0x00A2, 0x00);
  NEXT(0x00A3, TLVM_LXI_H);
  NEXT(0x00A4, 0x00);
  NEXT(0x00A5, 0x02);
  NEXT(0x00A6, TLVM_MVI_B);
  NEXT(0x00A7, 0x04);
  NEXT(0x00A8, TLVM_CALL);
  NEXT(0x00A9, 0x0F);
  NEXT(0x00AA, 0x00);
  NEXT(0x00AB, TLVM_POP_H);
  NEXT(0x00AC, TLVM_POP_PSW);
  NEXT(0x00AD, TLVM_RET);
  NEXT(0x00AE, TLVM_PUSH_PSW); // WRITE
  NEXT(0x00AF, TLVM_MOV_AC);
  NEXT(0x00B0, TLVM_CPI);
  NEXT(0x00B1, 0x01);
  NEXT(0x00B2, TLVM_CZ); // CZ START_WRITE_DATA
  NEXT(0x00B3, 0x2B);
  NEXT(0x00B4, 0x00);
  NEXT(0x00B5, TLVM_CNZ); // CNZ START_WRITE_CMD
  NEXT(0x00B6, 0x47);
  NEXT(0x00B7, 0x00);
  NEXT(0x00B8, TLVM_POP_PSW);
  NEXT(0x00B9, TLVM_PUSH_H);
  NEXT(0x00BA, TLVM_LXI_H);
  NEXT(0x00BB, 0x01);
  NEXT(0x00BC, 0x02);
  NEXT(0x00BD, TLVM_MOV_MA);
  NEXT(0x00BE, TLVM_POP_H);
  NEXT(0x00BF, TLVM_PUSH_PSW);
  NEXT(0x00C0, TLVM_MOV_AC);
  NEXT(0x00C1, TLVM_CPI);
  NEXT(0x00C2, 0x01);
  NEXT(0x00C3, TLVM_CZ); // CZ END_WRITE_DATA
  NEXT(0x00C4, 0x63);
  NEXT(0x00C5, 0x00);
  NEXT(0x00C6, TLVM_CNZ); // CNZ END_WRITE_CMD
  NEXT(0x00C7, 0x7A);
  NEXT(0x00C8, 0x00);
  NEXT(0x00C9, TLVM_POP_PSW);
  NEXT(0x00CA, TLVM_RET);
  NEXT(0x00CB, TLVM_PUSH_H); // READ
  NEXT(0x00CC, TLVM_LXI_H);
  NEXT(0x00CD, 0x02);
  NEXT(0x00CE, 0x02);
  NEXT(0x00CF, TLVM_MVI_B);
  NEXT(0x00D0, 0x02);
  NEXT(0x00D1, TLVM_CALL); // CALL SET_LOW
  NEXT(0x00D2, 0x03);
  NEXT(0x00D3, 0x00);
  NEXT(0x00D4, TLVM_MVI_B);
  NEXT(0x00D5, 0x10);
  NEXT(0x00D6, TLVM_CALL); // CALL SET_LOW
  NEXT(0x00D7, 0x03);
  NEXT(0x00D8, 0x00);
  NEXT(0x00D9, TLVM_MVI_B);
  NEXT(0x00DA, 0x08);
  NEXT(0x00DB, TLVM_CALL); // CALL SET_LOW
  NEXT(0x00DC, 0x03);
  NEXT(0x00DD, 0x00);
  NEXT(0x00DE, TLVM_MVI_B);
  NEXT(0x00DF, TLVM_CALL); // CALL WAIT_FOR_LOW
  NEXT(0x00E0, 0x15);
  NEXT(0x00E1, 0x00);
  NEXT(0x00E2, TLVM_MVI_B);
  NEXT(0x00E3, 0x08);
  NEXT(0x00E4, TLVM_CALL); // CALL SET_HIGH
  NEXT(0x00E5, 0x0F);
  NEXT(0x00E6, 0x00);
  NEXT(0x00E7, TLVM_LXI_H);
  NEXT(0x00E8, 0x01);
  NEXT(0x00E9, 0x02);
  NEXT(0x00EA, TLVM_MOV_CM);
  NEXT(0x00EB, TLVM_MVI_B);
  NEXT(0x00EC, 0x10);
  NEXT(0x00ED, TLVM_CALL); // CALL SET_HIGH
  NEXT(0x00EE, 0x0F);
  NEXT(0x00EF, 0x00);
  NEXT(0x00F0, TLVM_MVI_B);
  NEXT(0x00F1, 0x02);
  NEXT(0x00F2, TLVM_CALL); // CALL SET_HIGH
  NEXT(0x00F3, 0x0F);
  NEXT(0x00F4, 0x00);
  NEXT(0x00F5, TLVM_POP_H);
  NEXT(0x00F6, TLVM_RET);
  NEXT(0x00F7, TLVM_STA); // MAIN
  NEXT(0x00F8, 0xFF);
  NEXT(0x00F9, 0x01);
  NEXT(0x00FA, TLVM_MVI_C);
  NEXT(0x00FB, 0x01);
  NEXT(0x00FC, TLVM_MVI_A);
  NEXT(0x00FD, 0x00);
  NEXT(0x00FE, TLVM_CALL); // CALL WRITE
  NEXT(0x00FF, 0xAE);
  NEXT(0x0100, 0x00);
  NEXT(0x0101, TLVM_MVI_A);
  NEXT(0x0102, 0xFF);
  NEXT(0x0103, TLVM_CALL); // CALL WRITE
  NEXT(0x0104, 0xAE);
  NEXT(0x0105, 0x00);
  NEXT(0x0106, TLVM_MVI_A);
  NEXT(0x0107, 0x00);
  NEXT(0x0108, TLVM_CALL); // CALL WRITE
  NEXT(0x0109, 0xAE);
  NEXT(0x010A, 0x00);
  NEXT(0x010B, TLVM_MVI_A);
  NEXT(0x010C, 0x1F);
  NEXT(0x010D, TLVM_CALL); // CALL WRITE
  NEXT(0x010E, 0xAE);
  NEXT(0x010F, 0x00);
  NEXT(0x0110, TLVM_MVI_C);
  NEXT(0x0111, 0x00);
  NEXT(0x0112, TLVM_MVI_A);
  NEXT(0x0113, 0x6C);
  NEXT(0x0114, TLVM_CALL); // CALL WRITE
  NEXT(0x0115, 0xAE);
  NEXT(0x0116, 0x00);
  NEXT(0x0117, TLVM_CALL); // CALL READ
  NEXT(0x0118, 0xCB);
  NEXT(0x0119, 0x00);
  NEXT(0x011A, TLVM_MOV_AC);
  NEXT(0x011B, TLVM_OUT);
  NEXT(0x011C, 0x01);
  NEXT(0x011D, TLVM_HLT);
},
{
  tlvmTerminateContext(&m_data.CPU);
  tlvmTerminateContext(&m_data.APU);
},
{
  tlvmRun(m_data.CPU);
},
{
  tlvmContext* CPU;
  tlvmContext* APU;

  tlvmByte program[512];
})