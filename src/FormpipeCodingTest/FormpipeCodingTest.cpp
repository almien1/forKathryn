#include "DllRunner.h"
#include <iostream>

int main()
{
	DllRunner supportingProject("SupportingProject.DLL");

	// Load the DLL
	if (supportingProject.load())
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
				std::string response = supportingProject.runCommand(nextCommand);

				std::cout << std::string(response) << std::endl;
			}
		}
	}
	else
	{
		std::cout << supportingProject.getLastError() << std::endl;
	}
}
