#include <Windows.h>
#include <iostream>
#include <string>

#include "../SupportingProject/banking-api.h"

// Buffer size for DLL banking command responses
constexpr auto MAX_RESPONSE_SIZE = 1024; // Longest response is probably the help text (which may be removed as it's not in original requirements)

int main()
{
	// Load the DLL
	static const char* dllFilename = "SupportingProject.DLL";
	HMODULE supportingProject = LoadLibraryA(dllFilename);
	if (supportingProject == NULL)
	{
		std::cout << dllFilename << " could not be loaded!" << std::endl;
	}
	else
	{
		static const char* bankingFunctionName = "bankingCommand";
		static const char *getMessageFunctionName = "getMessage";
		static const char* deleteMessageFunctionName = "deleteMessage";

		// Load the DLL functions
		const BankApiCommand bankingApi = reinterpret_cast<BankApiCommand>(GetProcAddress(supportingProject, bankingFunctionName));
		const BankApiGetMessage getMessageFunction = reinterpret_cast<BankApiGetMessage>(GetProcAddress(supportingProject, getMessageFunctionName));
		const BankApiDeleteMessage delMessageFunction = reinterpret_cast<BankApiDeleteMessage>(GetProcAddress(supportingProject, deleteMessageFunctionName));

		if (bankingApi && getMessageFunction && delMessageFunction)
		{
			// Continuously take user input for the banking API and display the responses
			std::string nextCommand;
			bool finished = false;
			while (!finished)
			{
				// Display prompt, wait for user input
				std::cout << "> ";
				std::getline(std::cin, nextCommand);

				if (nextCommand.empty())
				{
					finished = true;
				}
				else
				{
					// DLL call to process command and return response
					MessageID messageID = bankingApi(nextCommand.data());
					std::string response = getMessageFunction(messageID);
					delMessageFunction(messageID);

					std::cout << std::string(response) << std::endl;
				}
			} // while not finished
		}
		else
		{
			std::cout << "Could not locate functions in " << dllFilename << std::endl;
		}
	}
}
