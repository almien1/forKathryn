# Your notes

## Get the DLL working

So we need to load the DLL 
- https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya
- https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress

Steps:
- Check DLL is being built to the same directory, so we don't need to tell it about paths.
- Load DLL (null = fail)
- Define a function pointer type (for how many functions will we be creating)
- Find the function (assuming "C" style export?) (null = fail)
- Run the function to return a "const" string pointer (points to memory within the DLL?)
- Function returns a wide string, so we'll need to find a way to make that work with cout.

Issues
- Web says there's a std::wcout (not wout!) function for wide strings
- Casting to function pointer type doesn't work "can't convert far pointer to ..."
	- needed dynamic_cast not static_cast, because the type-protection here is "trust me bro"
	- probably ought to put the typedef into the DLL's header at some point, so DLL "owns" the definition
		- done, #1656b3
- Can't find function 
	- check with DLL Export Viewer, looks like it's not exporting any functions.
	- need to add dllexport (from config.h) to the helloWorldMessage declaration
	- check again with DLL view, the function exists but it's C++-decorated
		- So we can either choose to export C style, or give up on dynamic-loading and just link the two modules together as a start-time dependency.
		- No particular notes in readme about the project's preferences for this.

Result: 
- "Hello to the world from another DLL!" displayed in console.  Great success!
- Probably ought to test it with non-ASCII text just to see if the charset encoding works end-to-end?
- Newline style is set by the "test" program, so we don't know yet if the project has any preference for newline styles within the main program.
	- Test by outputting to a text file -> apparently it's [CR][CR][LF]
	- Notepad++ detects it as Mac style!
	- Maybe change "\r\n" to std::endl - I guess "\n" was being expanded to the two-byte version
	- Okay now we have a "Windows style" output with a single line.
