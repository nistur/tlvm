#include <tlvm.h>

#include <iostream>
#include <sstream>
#include <map>

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
    tlvmChar     output[256];
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

        next = inst;
        if(next->address > address)
            break;

        prev = &inst->next;
        inst = next;
    }

    inst = new Instruction;
    inst->address = address;
    inst->next = next;

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

tlvmReturn step(tlvmContext* context)
{
    tlvmShort address = 0x0;
    while(true)
    {
        tlvmSetProgramCounter(context, address);
        tlvmChar* instruction = new tlvmChar[256];
        instruction[0] = 0;
        tlvmByte size;
        tlvmReturn state = tlvmDebugGetInstruction(context, &instruction, &size);
        Instruction* inst = GetInstruction(address);
        if(state == TLVM_SUCCESS)
        {
            printf("0x%.04X %s\n", address, instruction);
            address += size;
        }
        else
        {
            return state;
        }
    }
    return TLVM_SUCCESS;
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
