#include <iostream>
#include <Windows.h>
#include "../SupportingProject/hello-world.h"

int main()
{
	// Load the DLL
	//
	// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya
	//
	static const char* dllFilename = "SupportingProject.DLL";
	static const char* helloWorldFunctionName = "helloWorldMessage";
	HMODULE supportingProject = LoadLibraryA(dllFilename);
	if (supportingProject == NULL)
	{
		std::cout << dllFilename << " could not be loaded!\r\n";
	}
	else
	{
		// Load the "hello world" function
		//
		// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress
		//
		helloWorldFunctionType helloWorldFunction = reinterpret_cast<helloWorldFunctionType>(GetProcAddress(supportingProject, helloWorldFunctionName));
		if (helloWorldFunction == NULL)
		{
			std::cout << "Could not locate " << helloWorldFunctionName << " in " << dllFilename << "\r\n";
		}
		else
		{
			helloWorldFunctionReturn result = helloWorldFunction();
			std::wcout << result << std::endl;
		}
	}
}
