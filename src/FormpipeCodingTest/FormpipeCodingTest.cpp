#include <iostream>
#include <Windows.h>
#include <string>

#include "HelloWorldTest.h"
#include "../SupportingProject/banking-api.h"

// Option for selecting the initial part of the coding test
static const bool part1 = false;

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
		if (part1)
		{
			HelloWorldTest::run(supportingProject);
		}
		else
		{
			static const char* bankingFunctionName = "bankingCommand";

			// Load the "hello world" function
			const bankingCommandFunction bankingApi = reinterpret_cast<bankingCommandFunction>(GetProcAddress(supportingProject, bankingFunctionName));
			if (bankingApi == NULL)
			{
				std::cout << "Could not locate " << bankingFunctionName << " in " << dllFilename << std::endl;
			}
			else
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
						char response[MAX_RESPONSE_SIZE] = "";
						bankingApi(nextCommand.data(), response, sizeof(response));
						std::cout << std::string(response) << std::endl;
					}
				} // while not finished
			}
		}
	}
}
