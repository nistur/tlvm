#include <tlvm.h>

#include <tlvm_internal.h>

#include <iostream>
#include <sstream>
#include <map>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;

struct Memory
{
    Memory* next;
    char* buffer;
    int   buffersize;
    int   address;
};

struct Instruction
{
    Instruction* next;
    tlvmShort    address;
    tlvmShort    size;
    tlvmChar     output[16];
    int          flags;
};

struct State
{
    Memory* memory;
    Instruction *instructions;

    bool    quit;
};

State g_state;

Instruction* GetInstruction(tlvmShort address)
{
    Instruction* inst = g_state.instructions;
    Instruction** prev = &g_state.instructions;
    Instruction* next = NULL;

    while(inst != NULL)
    {
        if(inst->address == address)
        {
            return inst;
        }

        prev = &inst->next;
        next = inst->next;
        if(next == NULL || next->address > address)
            break;

        inst = next;
    }

    inst = new Instruction;
    inst->address = address;
    inst->next = next;
    inst->flags = 0;

    *prev = inst;
    return inst;
}

char* loadFile(string filename, int& filesize)
{
    FILE* fp = fopen(filename.c_str(), "r");
    if(fp == NULL)
        return NULL;

    char* buffer;
    fseek(fp, 0L, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);
    buffer = new char[filesize];
    fread(buffer, 1, filesize, fp);
    fclose(fp);
    return buffer;
}

/* parseAddress
 *  This is among some of the most hideous code I've ever written
 * It takes a std::string and tries to guess what value it represents
 * It sort of works with hex numbers and normal integers.
 */
int parseAddress(string str)
{
    int addr = 0;
    if(str.find("0x") == 0)
    {
        for(int i = 2; i < str.length(); ++i)
        {
            addr <<= 4;
            char c = str[i];
            int v = ((c >= 'A') && (c <= 'F')) ? 10 + (c - 'A') :
                    ((c >= 'a') && (c <= 'f')) ? 10 + (c - 'a') : c - '0';
            addr += v;
        }
    }
    else
        addr = atoi(str.c_str());
    return addr;
}

void setMemory(char* buffer, int address, int size)
{
    Memory* mem = new Memory;
    mem->buffer = buffer;
    mem->buffersize = size;
    mem->address = address;
    mem->next = NULL;
    if(g_state.memory == NULL)
        g_state.memory = mem;
    else
    {
        Memory* prev = g_state.memory;
        while(prev->next != NULL) prev = prev->next;
        prev->next = mem;
    }
}

#define INST(x) (op[0] == TLVM_##x)

tlvmShort stack[256];
tlvmByte  sp = 0;

#define POP() \
if(sp) \
{ \
    sp--; \
    address = stack[sp]; \
} \
else \
    return TLVM_SUCCESS;

tlvmReturn step(tlvmContext* context)
{
    tlvmShort address = 0x0;
    while(true)
    {
        tlvmSetProgramCounter(context, address);
        tlvmChar* instruction = new tlvmChar[256];
        instruction[0] = 0;
        tlvmByte size;
        
        Instruction* inst = GetInstruction(address);
        if(inst->flags)
        {
            // already been here, pop to somewhere else
            POP()
        }
        else
        {
            tlvmReturn state = tlvmDebugGetInstruction(context, &instruction, &size);

            if(state == TLVM_SUCCESS)
            {
                sprintf((char*)inst->output, "%s", instruction);
                //printf("0x%.02X %s\n", address, instruction);
                inst->flags |= 0x01;
                inst->size = size;
                tlvmByte* op = new tlvmByte[1];
                tlvmDebugGetMemory(context,address, 1, &op);
                if(INST(JMP) || INST(JZ)  || INST(JNZ) ||
                   INST(JC)  || INST(JNC) || INST(JP)  ||
                   INST(JPO) || INST(JPE) || INST(JM)  ||
                   INST(CALL)|| INST(CZ)  || INST(CNZ) ||
                   INST(CC)  || INST(CNC) || INST(CP)  ||
                   INST(CPO) || INST(CPE) || INST(CM))
                {
                    if(!INST(JMP))
                    {
                        // this is a jump or a call
                        // know where to fall back to
                        stack[sp] = address + size;
                        sp++;
                    }
                    // get the address of the new place
                    tlvmByte* mem = new tlvmByte[2];
                    tlvmDebugGetMemory(context,address + 1, 2, &mem);
                    address = (((tlvmShort)mem[1]) << 8) | (mem[0]);

                    delete[] mem;
                }
//                else if(INST(RET) || INST(RZ)  || INST(RNZ) ||
//                        INST(RC)  || INST(RNC) || INST(RP)  ||
//                        INST(RPO) || INST(RPE) || INST(RM))
                // don't check conditional returns because then we end up
                // not disassembling the code if it doesn't branch
                else if(INST(RET))
                {
                    POP();
                }
                else
                {
                    address += size;
                }

                delete[] op;
            }
            else
            {
                POP();
            }
        }
    }
    return g_tlvmStatus;
}

void printDisassembly(tlvmContext* context)
{
    Instruction* prev = NULL;
    Instruction* inst = g_state.instructions;
    while(inst)
    {
        // print any missing memory
        tlvmShort prevEnd = 0;
        if(prev)
            prevEnd = prev->address + prev->size;
        tlvmShort dataSize = inst->address - prevEnd;
        if(dataSize)
        {
            tlvmByte* dat = new tlvmByte[dataSize];

            tlvmDebugGetMemory(context, prevEnd, dataSize, &dat);
            printf("0x%.04X", prevEnd);
            for(int i = 0; i < dataSize; ++i)
            {
                if(i && i%8 == 0)
                {
                    printf("\t");
                    for(int j = 8; j > 0; --j)
                    {
                        tlvmByte c = dat[i-j];
                        printf("%c", c >= 0x20 ? c : '.');
                    }
                    printf("\n");
                }

                printf("\t0x%.02X", dat[i]);
                if(i == dataSize - 1)
                {
                    tlvmShort num = 8-i%8;
                    for(int _ = 0; _ < num; ++_) printf("\t");
                    for(int j = 8-num; j >= 0; --j)
                    {
                        tlvmByte c = dat[i-j];
                        printf("%c", c >= 0x20 ? c : '.');
                    }
                    printf("\n");
                }
            }

            delete[] dat;
        }
        printf("0x%.04X\t%s\n", inst->address, inst->output);

        prev = inst;
        inst = inst->next;
    }
    printf("END\n\n");
}

#define HANDLE_INPUT_START() \
while(true) \
{ \
    string val; \
    cout << "> "; \
    cin >> val;

#define HANDLE_INPUT_END() \
}

#define HANDLE_INPUT_OPTION(opt, shortopt) \
if(val == #opt || val == #shortopt)

/* 8080 Disassembler
 *
 * this is incredibly hacked together
 * I will, at some point, tidy it up
 * but for now, I'm just making sure
 * it works
 */
int main(int argc, char** argv)
{
    g_state.memory = NULL;
    g_state.quit = false;

    tlvmContext* context;
    tlvmInitContext(&context);
    tlvm8080Init(context);
    tlvmSetClockspeed(context, TLVM_MHZ(2,0));

    HANDLE_INPUT_START();
        HANDLE_INPUT_OPTION(quit, q)
            break;
        HANDLE_INPUT_OPTION(file, f)
        {
            string filename;
            string addressStr;
            int address = 0;
            cin >> filename;
            int size;
            char* file = loadFile(filename, size);
            cin >> addressStr;
            address = parseAddress(addressStr);

            if(tlvmSetMemory(context, (tlvmByte*)file, address, size, TLVM_FLAG_READ) != TLVM_SUCCESS)
            {
                delete[] file;
            }
            else
            {
                setMemory(file, address, size);

                printf("Loaded file %s into memory at 0x%04X - 0x%04X\n", filename.c_str(), address, address + size - 1);
            }
        }
        HANDLE_INPUT_OPTION(memory, m)
        {
            string addressStr;
            string sizeStr;
            cin >> addressStr;
            cin >> sizeStr;

            int address = parseAddress(addressStr);
            int size = parseAddress(sizeStr);

            char* buffer = new char[size];
            memset(buffer, 0, size);
            if(tlvmSetMemory(context, (tlvmByte*)buffer, address, size, TLVM_FLAG_READ | TLVM_FLAG_WRITE) != TLVM_SUCCESS)
            {
                delete [] buffer;
                cout << "Unable to create memory buffer" << endl;
            }
            else
            {
                setMemory(buffer, address, size);
                printf("Created %dB RAM at 0x%04X - 0x%04X\n", size, address, address + size - 1);
            }
        }
        HANDLE_INPUT_OPTION(run, r)
        {
            tlvmReset(context);
            tlvmReturn ret = step(context);

            printDisassembly(context);

            if(g_state.quit)
            {
                break;
            }
            cout << "Program quit with code: " << ret << endl;
            tlvmReset(context);
        }
    HANDLE_INPUT_END();

    // Remove all the memory allocated
    Memory* mem = g_state.memory;
    while(mem)
    {
        Memory* next = mem->next;
        delete[] mem->buffer;
        delete mem;
        mem = next;
    }
    return 0;
}
