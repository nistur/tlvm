#include <tlvm.h>

#include <iostream>

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
};

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

void breakpoint(tlvmByte message, tlvmShort addr)
{
	cout << "Breakpoint " << addr << endl;
	while(1);
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
	State state;
	state.memory = NULL;

	tlvmContext* context;
	tlvmInitContext(&context);
	tlvmInit8080(context);
	tlvmSetClockspeed(context, TLVM_MHZ(2,0));
	while(true)
	{
		string val;
		cout << "> ";
		cin >> val;
		if(val == "q" || val == "quit")
		{
			break;
		}
		if(val == "f" || val == "file")
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
				Memory* mem = new Memory;
				mem->buffer = file;
				mem->buffersize = size;
				mem->address = address;
				if(state.memory == NULL)
					state.memory = mem;
				else
				{
					Memory* prev = state.memory;
					while(prev->next != NULL) prev = prev->next;
					prev->next = mem;
				}
			}
		}
		if(val == "r" || val == "run")
		{
			tlvmRun(context);
		}
		if(val == "b" || val == "break" || val == "breakpoint")
		{
			string address;
			cin >> address;
			tlvmDebugAddBreakpoint(context, parseAddress(address), breakpoint);
		}
	}

	Memory* mem = state.memory;
	while(mem)
	{
		Memory* next = mem->next;
		delete[] mem->buffer;
		delete mem;
		mem = next;
	}
	return 0;
}