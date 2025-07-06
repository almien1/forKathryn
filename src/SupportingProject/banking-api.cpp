#include "banking-api.h"
#include "Banking.h"
#include <string>

// Global "banking" object to keep state in memory for duration of the executable which loads this DLL
Banking g_banking;

void bankingCommand(const bankingApiString command, bankingApiString response, size_t responseLen)
{
	// Run the command against the banking system
	std::string responseStr = g_banking.command(std::string(command));

	// Copy the result for the C interface
	strncpy_s(response, responseLen, responseStr.c_str(), _TRUNCATE);
}
