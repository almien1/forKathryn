#include "HelloWorldTest.h"
#include <iostream>
#include "../SupportingProject/hello-world.h"

void HelloWorldTest::run(HMODULE& supportingProject)
{
	static const char* helloWorldFunctionName = "helloWorldMessage";

	// Load the "hello world" function
	const helloWorldFunctionType helloWorldFunction = reinterpret_cast<helloWorldFunctionType>(GetProcAddress(supportingProject, helloWorldFunctionName));
	if (helloWorldFunction == NULL)
	{
		std::cout << "Could not locate " << helloWorldFunctionName << " in DLL" << std::endl;
	}
	else
	{
		// Run the function, and display the (wide char) output
		const helloWorldFunctionReturn result = helloWorldFunction();
		std::wcout << result << std::endl;
	}
}
