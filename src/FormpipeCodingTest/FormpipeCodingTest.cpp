#include <iostream>
#include <Windows.h>
#include "HelloWorldTest.h"

// Option for selecting the initial part of the coding test
static const bool part1 = true;

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
			// TODO: New code here for command-line event thingie

		}
	}
}
