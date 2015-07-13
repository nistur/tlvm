;; Fibbonacci

OUTDATA EQU 0x01
OUTSTAT EQU 0x02

READY EQU   0x01

JMP MAIN
OUTPUT:						;; 0x0003
	PUSH PSW
OUTLOOP						;; 0x0004
	IN OUTSTAT
	CPI READY
	JNZ OUTLOOP				;; Wait for READY to be high
	MOV A,C
	OUT OUTDATA
	POP PSW
	RET
FIB:						;; 0x0010
	POP H 					;; Copy the address we're calling from (ie main)
	POP B					;; We expect the top of the stack to be the last 2 values
	PUSH H 					;; Put the address we're calling from back at the top of the stack
	XRA A
	ADC B
	ADC C
	JC FIB_DONE				;; If we overflow, then bail
	MOV B,C
	MOV C,A
	CALL OUTPUT
	PUSH B
	CALL FIB
FIB_DONE:					;; 0x001E
	RET
MAIN:						;; 0x002
	STA 0x01FF
	MVI B,0x00
	MVI C,0x01
	PUSH B
	CALL FIB
	HLT