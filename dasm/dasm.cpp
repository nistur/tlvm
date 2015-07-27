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

#include <tlvm.h>

#include <tlvm_internal.h>

#include <fstream>
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

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#elif defined(__cplusplus)
# define UNUSED(x)
#else
# define UNUSED(x) x
#endif

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
    tlvmChar     output[256];
    int          flags;
    tlvmChar     label[8];
    Instruction* dest;
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
    inst->label[0] = 0;
    inst->flags = 0;
    inst->dest = NULL;

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
        for(unsigned int i = 2; i < str.length(); ++i)
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
tlvmShort labelIndex = 0;

#define POP() \
if(sp) \
{ \
    sp--; \
    address = stack[sp]; \
} \
else \
    return TLVM_SUCCESS;

tlvmReturn step(tlvmContext* context, tlvmShort address)
{
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
                    inst->dest = GetInstruction(address); // point to the place we're jumping to
                    if(inst->dest->label[0] == 0)
                        sprintf((char*)inst->dest->label, "LOC%.02d", labelIndex++);
                    tlvmByte* p = inst->output;
                    while(!isspace(*p) && *p) ++p;
                    if(*p) p[1] = 0; // nasty hack to remove the address from the instruction

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

#define PAD(l, w) \
    while(strlen(l) < w) sprintf(l,"%s ", l);

void printMemory(tlvmContext* context, tlvmShort address, tlvmShort size, std::ostream& stream)
{
    tlvmByte* dat = new tlvmByte[size];

    tlvmDebugGetMemory(context, address, size, &dat);
    char line[255];
    sprintf(line, "$%.04Xh", address);
    for(int i = 0; i < size; ++i)
    {
        if(i && i%8 == 0)
        {
            PAD(line, 80);
            sprintf(line, "%s; ", line);
            for(int j = 8; j > 0; --j)
            {
                tlvmByte c = dat[i-j];
                sprintf(line, "%s%c", line, c >= 0x20 ? c : '.');
            }
            stream << line << std::endl;
            sprintf(line, "");
        }
        PAD(line, 8+((i%8)*8));
        sprintf(line, "%s$%.02Xh", line, dat[i]);
        if(i == size - 1)
        {
            tlvmShort num = 8-i%8;
            PAD(line, 80);
            sprintf(line, "%s; ", line);
            for(int j = 8-num; j >= 0; --j)
            {
                tlvmByte c = dat[i-j];
                sprintf(line, "%s%c", line, c >= 0x20 ? c : '.');
            }
            stream << line << std::endl;
            sprintf(line, "");
        }
    }

    delete[] dat;
}

void printDisassembly(tlvmContext* context, std::ostream& stream)
{
    Instruction* prev = NULL;
    Instruction* inst = g_state.instructions;
    char line[256];
    while(inst)
    {
        line[0] = 0;
        // print any missing memory
        tlvmShort prevEnd = 0;
        if(prev)
            prevEnd = prev->address + prev->size;
        tlvmShort dataSize = inst->address - prevEnd;
        if(dataSize)
            printMemory(context, prevEnd, dataSize, stream);
        if(strlen((char*)inst->label))
            sprintf(line, "%s%s:", line, inst->label);
        PAD(line, 8);
        sprintf(line, "%s%s", line, inst->output);
        PAD(line, 16);
        sprintf(line, "%s%s", line, inst->dest ? (char*)inst->dest->label : "");
        PAD(line, 64);
        sprintf(line, "%s;$%.04Xh\n", line, inst->address);

        prev = inst;
        inst = inst->next;
        stream << line;
    }
    Memory* mem = g_state.memory;
    Memory* end = mem;
    while(mem)
    {
        tlvmShort prevEnd = end->address+end->buffersize;
        tlvmShort thisEnd = mem->address+mem->buffersize;
        if(thisEnd > prevEnd)
            end = mem;
        mem = mem->next;
    }
    if(prev && end)
    {
        tlvmShort memEnd = end->address + end->buffersize - 1;
        tlvmShort instEnd = prev->address + prev->size;
        tlvmShort endSize = memEnd - instEnd;
        printMemory(context, instEnd, endSize, stream);
    }
    sprintf(line, "END\n\n");
    stream << line;
}

void cleanUpInstructions()
{
    Instruction* next = g_state.instructions;
    while(next)
    {
        Instruction* inst = next;
        next = inst->next;
        delete inst;
    }
    g_state.instructions = NULL;
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
int main(int UNUSED(argc), char** UNUSED(argv))
{
    g_state.memory = NULL;
    g_state.quit = false;

    tlvmContext* context;
    tlvmInitContext(&context, TLVM_CPU_8080);
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

                printf("Loaded file %s into memory at $%04X - $%04X\n", filename.c_str(), address, address + size - 1);
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
                printf("Created %dB RAM at $%04X - $%04X\n", size, address, address + size - 1);
            }
        }
        HANDLE_INPUT_OPTION(run, r)
        {
            string addressStr;
            cin >> addressStr;
            int address = parseAddress(addressStr);

            tlvmReset(context);
            tlvmReturn ret = step(context, address);

            printDisassembly(context, cout);
            

            if(g_state.quit)
            {
                break;
            }
            cout << "Program quit with code: " << ret << endl;
            tlvmReset(context);
        }
        HANDLE_INPUT_OPTION(cleanup, c)
        {
            cleanUpInstructions();
        }
        HANDLE_INPUT_OPTION(label, l)
        {
            string addressStr;
            string label;
            cin >> addressStr;
            cin >> label;

            int address = parseAddress(addressStr);
            Instruction* inst = GetInstruction(address);
            sprintf((char*)inst->label, "%s", label.c_str());
        }
        HANDLE_INPUT_OPTION(print, p)
        {
            printDisassembly(context, cout);
        }
        HANDLE_INPUT_OPTION(write, w)
        {
            string filename;
            cin >> filename;
            std::ofstream file(filename.c_str());
            printDisassembly(context, file);
            file.close();
        }
        HANDLE_INPUT_OPTION(db, d)
        {
            string addressStr;
            string sizeStr;
            cin >> addressStr;
            cin >> sizeStr;

            int address = parseAddress(addressStr);
            int size = parseAddress(sizeStr);
            Instruction* inst = GetInstruction(address);
            inst->flags |= 0x01;
            inst->size = size;
            sprintf((char*)inst->output, "DB '");
            tlvmByte* dat = &inst->output[4];
            tlvmDebugGetMemory(context, address, size, &dat);
            dat[size] = '\'';
        }
    HANDLE_INPUT_END();

    cleanUpInstructions();

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
