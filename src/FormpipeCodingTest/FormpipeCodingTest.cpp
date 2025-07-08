#include "DllRunner.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>

int main()
{
	(void)_setmode(_fileno(stdout), _O_U8TEXT);
	(void)_setmode(_fileno(stdin), _O_U8TEXT);
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	DllRunner supportingProject(L"SupportingProject.DLL");

	// Load the DLL
	if (supportingProject.load())
	{
		// Continuously take user input for the banking API and display the responses
		std::wstring nextCommand;
		bool finished = false;
		while (!finished)
		{
			// Display prompt, wait for user input
			std::wcout << L"> ";
			std::getline(std::wcin, nextCommand);

			if (nextCommand.empty())
			{
				finished = true;
			}
			else
			{
				// DLL call to process command and return response
				std::wstring response = supportingProject.runCommand(nextCommand);

				std::wcout << std::wstring(response) << std::endl;
			}
		}
	}
	else
	{
		std::wcout << supportingProject.getLastError() << std::endl;
	}
}
