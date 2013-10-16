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
	tlvmChar* instruction = new tlvmChar[256];
	instruction[0] = 0;
	tlvmDebugGetInstruction(context, &instruction);
	printf("0x%x\t%s\n", addr, instruction);
	delete[] instruction;

	HANDLE_INPUT_START();
		HANDLE_INPUT_OPTION(step, s)
		{
			tlvmDebugStep(context, breakpoint);
			return;
		}
		HANDLE_INPUT_OPTION(continue, c)
		{
			tlvmDebugContinue(context);
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
	HANDLE_INPUT_END();
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
	tlvmInit8080(context);
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
				Memory* mem = new Memory;
				mem->buffer = file;
				mem->buffersize = size;
				mem->address = address;
				if(g_state.memory == NULL)
					g_state.memory = mem;
				else
				{
					Memory* prev = g_state.memory;
					while(prev->next != NULL) prev = prev->next;
					prev->next = mem;
				}

				printf("Loaded file %s into memory at 0x%x\n", filename.c_str(), address);
			}
		}
		HANDLE_INPUT_OPTION(run, r)
		{
			tlvmReturn ret = tlvmRun(context);
			if(g_state.quit)
			{
				break;
			}
			cout << "Program quit with code: " << ret << endl;
		}
		HANDLE_INPUT_OPTION(breakpoint, b)
		{
			string address;
			cin >> address;
			tlvmDebugAddBreakpoint(context, parseAddress(address), breakpoint);
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