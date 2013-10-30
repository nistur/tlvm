#include <tlvm.h>

#include <iostream>
#include <pthread.h>

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

int s_dataPort = -1;
int s_statPort = -1;
int s_numDataPort = -1;
int s_numStatPort = -1;
void onIOWrite(tlvmContext* context, tlvmByte port)
{
	tlvmByte val = 0;
	tlvmGetPort(context, port, &val);
	if(port == s_dataPort)
	{
		if(val == '$')
			printf("\n");
		else
			printf("%c", val);
	}
	else if (port == s_numDataPort)
	{
		printf("%d\n", val);
	}
}

void startStdIO(tlvmContext* context, int dataPort, int statPort)
{
	s_dataPort = dataPort;
	s_statPort = statPort;
	tlvmSetPort(context, s_statPort, 0x01); // READY!
	tlvm8080SetIOCallback(context, onIOWrite);
}

void startIOPrint(tlvmContext* context, int dataPort, int statPort)
{
	s_numDataPort = dataPort;
	s_numStatPort = statPort;
	tlvmSetPort(context, s_numStatPort, 0x01); // READY!
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
	tlvmChar* instruction = new tlvmChar[256];
	instruction[0] = 0;
	tlvmDebugGetInstruction(context, &instruction);
	printf("0x%X\t%s\n", addr, instruction);
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
					tlvmDebugHalt(context);
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

			if(tlvmSetMemory(context, (tlvmByte*)file, address, size, TLVM_FLAG_READ) != TLVM_SUCCESS)
			{
				delete[] file;
			}
			else
			{
				setMemory(file, address, size);

				printf("Loaded file %s into memory at 0x%04X - 0x%04X\n", filename.c_str(), address, address + size);
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
			string dataPortStr;
			string statPortStr;

			cin >> dataPortStr;
			cin >> statPortStr;
			startStdIO(context, parseAddress(dataPortStr), parseAddress(statPortStr));
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
				printf("Created %dB RAM at 0x%04X - 0x%04X\n", size, address, address + size);
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