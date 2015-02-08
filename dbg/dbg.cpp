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

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WIN32
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#endif /*WIN32*/

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct Memory
{
	Memory* next;
	char* buffer;
	int   buffersize;
	int   address;
};

struct State
{
	Memory* memory;

	bool    quit;
};

State g_state;

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

int g_outDataPort = -1;
int g_inDataPort = -1;
int g_statPort = -1;
int g_numDataPort = -1;
int g_numStatPort = -1;

enum ThreadState { None, Running, Halt };

ThreadState g_inputThreadState = None;
pthread_t   g_inputThreadID;
void* InputThread(void* user)
{
	tlvmContext* context = (tlvmContext*)user;

	struct termios old_term;
	tcgetattr(STDIN_FILENO, &old_term);
	struct termios new_term;
	tcgetattr(STDIN_FILENO, &new_term);
	cfmakeraw(&new_term);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

	while(g_inputThreadState == Running)
	{
		tlvmSetPort(context, g_statPort, 0x01);
		tlvmByte c = getchar();
		if( c == 27 ) // Escape
		{
			g_inputThreadState = Halt;
			tlvmDebugHalt( context );
			break;
		}
		tlvmSetPort(context, g_inDataPort, c);
		tlvmSetPort(context, g_statPort, 0x02 | 0x01);
		usleep(50000); // sleep some time to allow the input to be handled
	}
  	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

	return NULL;
}

void onIOWrite(tlvmContext* context, tlvmByte port)
{
	tlvmByte val = 0;
	tlvmGetPort(context, port, &val);
	if(port == g_outDataPort)
	{
		if(val == '$')
			printf("\n");
		else
			printf("%c", val);
	}
	else if (port == g_numDataPort)
	{
		printf("%d\n", val);
	}
}

void startStdIO(tlvmContext* context, int outDataPort, int inDataPort, int statPort)
{
	g_outDataPort = outDataPort;
	g_inDataPort = outDataPort;
	g_statPort = statPort;
	tlvmSetPort(context, g_statPort, 0x01); // READY!
	g_inputThreadState = Halt; // dont start running now, instead let resume take over
	tlvm8080SetIOCallback(context, onIOWrite);
}

void pauseStdIO(tlvmContext* context)
{
	if(g_inputThreadState == Running)
	{
		g_inputThreadState = Halt;
		pthread_join(g_inputThreadID, NULL);
	}
}

void resumeStdIO(tlvmContext* context)
{
	if(g_inputThreadState == Halt)
	{
		g_inputThreadState = Running;
		pthread_create(&g_inputThreadID, NULL, InputThread, context);
	}
}

void startIOPrint(tlvmContext* context, int dataPort, int statPort)
{
	g_numDataPort = dataPort;
	g_numStatPort = statPort;
	tlvmSetPort(context, g_numStatPort, 0x01); // READY!
	tlvm8080SetIOCallback(context, onIOWrite);
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

void breakpoint(tlvmContext* context, tlvmByte message, tlvmShort addr)
{
	pauseStdIO(context);
	tlvmChar* instruction = new tlvmChar[256];
	instruction[0] = 0;
	tlvmByte size;
	tlvmDebugGetInstruction(context, &instruction, &size);
	printf("0x%X\t%s\n", addr, instruction);
	delete[] instruction;

	HANDLE_INPUT_START();
		HANDLE_INPUT_OPTION(step, s)
		{
			tlvmDebugStep(context, breakpoint);
			resumeStdIO(context);
			return;
		}
		HANDLE_INPUT_OPTION(continue, c)
		{
			tlvmDebugContinue(context);
			resumeStdIO(context);
			return;
		}
		HANDLE_INPUT_OPTION(quit, q)
		{
			cout << "Program is still running, are you sure? yes/no: ";
			while(true)
			{
				string confirm;
				cin >> confirm;
				if(confirm == "yes")
				{
					g_state.quit = true;
					tlvmDebugHalt(context);
					resumeStdIO(context);
					return;
				}
				else if(confirm == "no")
				{
					break;
				}
				else
				{
					cout << "Please answer yes or no: ";
				}
			}
		}
		HANDLE_INPUT_OPTION(breakpoint, b)
		{
			string address;
			cin >> address;
			tlvmDebugAddBreakpoint(context, parseAddress(address), breakpoint);
		}
		HANDLE_INPUT_OPTION(print, p)
		{
			string addressStr;
			string sizeStr;
			tlvmShort address, size;
			tlvmByte* mem;
			int iMem;

			cin >> addressStr;
			cin >> sizeStr;

			address = parseAddress(addressStr);
			size = parseAddress(sizeStr);
			mem = new tlvmByte[size];
			tlvmDebugGetMemory(context, address, size, &mem);
			for(iMem = 0; iMem < size; ++iMem)
			{
				printf("0x%02X%s", mem[iMem], (iMem + 1) % 8 ? "\t" : "\n");
			}
			cout << endl;
			delete [] mem;
		}
		HANDLE_INPUT_OPTION(register, x)
		{
			string regStr;
			tlvmByte reg;

			cin >> regStr;

			if(tlvmDebugParseRegister(context, (tlvmChar*)regStr.c_str(), &reg) != TLVM_SUCCESS)
				reg = parseAddress(regStr);
			tlvmDebugGetRegister(context, reg, &reg);
			printf("0x%02X\n", reg);
		}
	HANDLE_INPUT_END();
	resumeStdIO(context);
}

/* 8080 Debugger
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

			if(tlvmSetMemory(context, (tlvmByte*)file, address, size, TLVM_FLAG_READ | TLVM_FLAG_WRITE) != TLVM_SUCCESS)
			{
				delete[] file;
			}
			else
			{
				setMemory(file, address, size);

				printf("Loaded file %s into memory at 0x%04X - 0x%04X\n", filename.c_str(), address, address + size - 1);
			}
		}
		HANDLE_INPUT_OPTION(run, r)
		{
			resumeStdIO(context);
			tlvmReset(context);
			tlvmReturn ret = tlvmRun(context);
			pauseStdIO(context);
			if(g_state.quit)
			{
				break;
			}
			cout << "Program quit with code: " << ret << endl;
			tlvmReset(context);
		}
		HANDLE_INPUT_OPTION(breakpoint, b)
		{
			string address;
			cin >> address;
			tlvmDebugAddBreakpoint(context, parseAddress(address), breakpoint);
		}
		HANDLE_INPUT_OPTION(step, s)
		{
			cout << "Program not running" << endl;
		}
		HANDLE_INPUT_OPTION(continue, c)
		{
			cout << "Program not running" << endl;
		}
		HANDLE_INPUT_OPTION(print, p)
		{
			string dummy;
			cin >> dummy;
			cout << "Program not running" << endl;
		}
		HANDLE_INPUT_OPTION(register, x)
		{
			string dummy;
			cin >> dummy; 
			cin >> dummy;
			cout << "Program not running" << endl;
		}
		HANDLE_INPUT_OPTION(stdio, i)
		{
			string outDataPortStr;
			string inDataPortStr;
			string statPortStr;

			cin >> outDataPortStr;
			cin >> inDataPortStr;
			cin >> statPortStr;
			startStdIO(context, parseAddress(outDataPortStr), parseAddress(inDataPortStr), parseAddress(statPortStr));
		}
		HANDLE_INPUT_OPTION(watch, w)
		{
			string dataPortStr;
			string statPortStr;

			cin >> dataPortStr;
			cin >> statPortStr;
			startIOPrint(context, parseAddress(dataPortStr), parseAddress(statPortStr));
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
