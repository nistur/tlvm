#ifdef  TLVM_HAS_8231A
#include "tlvm_internal.h"

tlvmReturn tlvmInit8231A(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    // make sure we have enough space for instructions
    if(context->m_InstructionSet)
        tlvmFree(context->m_InstructionSet);
    // in theory the 8231A has far fewer instructions than this
    // but they are spread out over the instruction space, so
    // we may as well make it easier for ourselves
    context->m_InstructionSet = tlvmMallocArray(tlvmInstruction, 256);

    // initialise the stack in the register space
    if(context->m_Registers)
        tlvmFree(context->m_Registers);
    context->m_Registers = tlvmMallocArray(tlvmByte, 0x13);

    // 8231A doesn't have any IO ports
    // but we will use 3 of them to represent our chip pins
    if(context->m_Ports)
        tlvmFree(context->m_Ports);
    context->m_Ports = tlvmMallocArray(tlvmByte, 3);

    context->m_StepFunction = tlvm8231Step;
    // start the stack at the end so that the first time
    // we push, it will push onto the beginning
    context->m_StackPointer = TLVM_8231A_STACK_END;

    TLVM_8231A_SET_PIN_HIGH(SVR,EACK);
    TLVM_8231A_SET_PIN_LOW(SVR,SVACK);
    TLVM_8231A_SET_PIN_LOW(SVR,SVREQ);

    TLVM_8231A_SET_PIN_LOW(CMD,RESET);
    TLVM_8231A_SET_PIN_LOW(CMD,READY);
    TLVM_8231A_SET_PIN_HIGH(CMD,CS);
    TLVM_8231A_SET_PIN_HIGH(CMD,A0);
    TLVM_8231A_SET_PIN_HIGH(CMD,RD);
    TLVM_8231A_SET_PIN_HIGH(CMD,WR);
    TLVM_8231A_SET_PIN_HIGH(CMD,END);

    return tlvmAdd8231AInstructions(context);
}

tlvmReturn tlvmAdd8231AInstructions(tlvmContext* context)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    context->m_InstructionSet[TLVM_8231A_NOP] = tlvm8231ANOP;
    context->m_InstructionSet[TLVM_8231A_POPS] = tlvm8231APOPS;
    context->m_InstructionSet[TLVM_8231A_PTOS] = tlvm8231APTOS;
    context->m_InstructionSet[TLVM_8231A_SADD] = tlvm8231ASADD;
    context->m_InstructionSet[TLVM_8231A_SSUB] = tlvm8231ASSUB;
    context->m_InstructionSet[TLVM_8231A_SDIV] = tlvm8231ASDIV;

    tlvmReturnCode(SUCCESS);
}

tlvmReturn tlvm8231Step(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    if(TLVM_8231A_PIN_LOW(CMD, END))
    {
        if(TLVM_8231A_PIN_LOW(SVR, EACK))
    	{
    	    TLVM_8231A_SET_PIN_HIGH(CMD, END);
    	}
	    tlvmReturnCode(SUCCESS);
    }

    // first, handle toggling CS pin
    if(TLVM_8231A_PIN_HIGH(CMD, CS))
    {
        context->m_Registers[TLVM_8231A_STATE] = TLVM_8231A_STATE_ACTIVE;
    }
    else if(context->m_Registers[TLVM_8231A_STATE] == TLVM_8231A_STATE_ACTIVE)
    {
        context->m_Registers[TLVM_8231A_STATE] = TLVM_8231A_STATE_WAIT;
        tlvmReturnCode(SUCCESS);
    }

    // if the chip is active, just perform normal execution
    if(context->m_Registers[TLVM_8231A_STATE] == TLVM_8231A_STATE_ACTIVE)
    {
        if(context->m_InstructionSet[context->m_Registers[TLVM_8231A_COMMAND]] != NULL)
        {
            if(context->m_Registers[TLVM_8231A_COMMAND] == TLVM_8231A_NOP)
                tlvmReturnCode(SUCCESS);
            context->m_InstructionSet[context->m_Registers[TLVM_8231A_COMMAND]](context, cycles);
            TLVM_8231A_SET_PIN_LOW(CMD, END);
            tlvmReturn();
        }
        else
        {
            tlvmReturnCode(UNKNOWN_INSTRUCTION);
        }
    }
    else if(context->m_Registers[TLVM_8231A_STATE] == TLVM_8231A_STATE_WAIT)
    {
        if(TLVM_8231A_PIN_LOW(CMD, RD))
        {
            context->m_Registers[TLVM_8231A_STATE] = TLVM_8231A_STATE_WAIT_READ;
            TLVM_8231A_SET_PIN_LOW(CMD, READY);
            tlvmReturnCode(SUCCESS);
        }
        else if(TLVM_8231A_PIN_LOW(CMD, WR))
        {
            if(TLVM_8231A_PIN_LOW(CMD, A0))
            {
                context->m_Registers[TLVM_8231A_STATE] = TLVM_8231A_STATE_WAIT_WRITE;
            }
            else
            {
                context->m_Registers[TLVM_8231A_STATE] = TLVM_8231A_STATE_WAIT_CMD;   
            }
            TLVM_8231A_SET_PIN_LOW(CMD, READY);
            tlvmReturnCode(SUCCESS);
        }
    }
    else if(context->m_Registers[TLVM_8231A_STATE] == TLVM_8231A_STATE_WAIT_READ)
    {
        if(TLVM_8231A_PIN_HIGH(CMD, RD))
        {
            TLVM_8231A_SET_PIN_HIGH(CMD, READY);
            context->m_Ports[TLVM_8231A_PORT_DB] = tlvm8231AStackPop(context);
            context->m_Registers[TLVM_8231A_STATE] = TLVM_8231A_STATE_WAIT;
        }
        tlvmReturnCode(SUCCESS);
    }
    else if(context->m_Registers[TLVM_8231A_STATE] == TLVM_8231A_STATE_WAIT_WRITE)
    {
        if(TLVM_8231A_PIN_HIGH(CMD, WR))
        {
            TLVM_8231A_SET_PIN_HIGH(CMD, READY);
            tlvm8231AStackPush(context, context->m_Ports[TLVM_8231A_PORT_DB]);
            context->m_Registers[TLVM_8231A_STATE] = TLVM_8231A_STATE_WAIT;
        }
        tlvmReturnCode(SUCCESS);
    }
    else if(context->m_Registers[TLVM_8231A_STATE] == TLVM_8231A_STATE_WAIT_CMD)
    {
        if(TLVM_8231A_PIN_HIGH(CMD, WR))
        {
            TLVM_8231A_SET_PIN_HIGH(CMD, READY);
            context->m_Registers[TLVM_8231A_COMMAND] = context->m_Ports[TLVM_8231A_PORT_DB];
            context->m_Registers[TLVM_8231A_STATE] = TLVM_8231A_STATE_WAIT;
        }
        tlvmReturnCode(SUCCESS);
    }

    tlvmReturnCode(SUCCESS);
}

void tlvm8231AStackPush(tlvmContext* context, tlvmByte val)
{
    if(context == NULL) return;

    context->m_StackPointer++;

    // wrap
    if(context->m_StackPointer > TLVM_8231A_STACK_END)
        context->m_StackPointer = TLVM_8231A_STACK_START;

    context->m_Registers[context->m_StackPointer] = val;
}

tlvmByte tlvm8231AStackPop(tlvmContext* context)
{
    if(context == NULL) return 0;

    tlvmByte val = context->m_Registers[context->m_StackPointer];

    // wrap
    if(context->m_StackPointer == TLVM_8231A_STACK_START)
        context->m_StackPointer = TLVM_8231A_STACK_END;
    else
        context->m_StackPointer--;        

    return val;
}

tlvmReturn tlvm8231ANOP(tlvmContext* context, tlvmByte* cycles)
{
    if(context == NULL)
        tlvmReturnCode(NO_CONTEXT);

    if(cycles)
        *cycles = 4;

    tlvmReturnCode(SUCCESS);
}

#endif/*TLVM_HAS_8231A*/
