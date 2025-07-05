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


## Event handler

"UI -> Handler -> Command -> Event".  "The UI will in our case be the command line."

Requirements:
- O name : Create account with name (O = open)
- A name : Make name the account that following commands will work on (A = Activate)
- C : Close account (C = Close)
- D amount : Deposit an amount (D = Deposit)
- W amount : Withdraw an amount (W = Withdraw)
- B : Show current balance (B = balance)
- T : List transactions on account (T = Transactions)

Quick requirements analysis:
- O: unique name needed.  name restrictions? (like spaces?) Does O imply A, or should someone activate an account after opening it?
- A: This implies that the application state needs a "currently selected account" field
- C: I guess this means no further actions can be done on that account
- C: Should it be possible to open another account with the same name?  i.e. do we delete the account, or just mark it as closed?  If it can be marked as closed, can O open the account again?
- D: pretty simple.  I guess we're using a single abstract currency.  Do we need to care about how currency is stored - e.g. ones with very large numbers like vietnam.  Do we need to use integer methods because it's currency or is floating point okay in this case?
- W: looks like a conflict between two requirements: 
	- "just assume that overdrawing is okay"
	- "what to do when withdrawing an amount that is too big" - how can it be too big?  Is there an overdraft limit?  There's no way to configure a limit in the API.
- B: pretty simple.  Formatting?  Do we need a currency symbol (or, there is a generic symbol - https://en.wikipedia.org/wiki/Currency_sign_(generic) (U+00A4) - but if that's not well-known by the target audience it could cause confusion)
- T: does "transactions" mean just D,W (and A,C?) - it won't show that you queried the balance in the past?
- A must be required before any command that doesn't specify a name - so C,D,W,B,T are invalid without an A

Interface:

Guess we have two options:
- commands are given as command-line parameters.  So two commands would mean running the program twice.  This would mean that we need to save state to disk or external storage.
- commands are entered via STDIN.  This would let us keep everything in memory, but means that the text input processing is more complex.

The presence of an A command seems to be leaning towards the second option, as it would be prety weird to have a "current user" state just permanently stored!  Or are we thinking to allow multiple commands as a long list of parameters?

Also, this was supposed to be used for a web application, so is there some concept of "session" that the website would be supplying?  e.g. if that session had previously sent an A, then a subsequent command with the same session would be allowed to issue a B or T.


### GUI

Assuming we go with the console idea, we'll need a loop of "std::cin >> (DLL) >> std::cout"

Note: don't just pipe cin, that doesn't work with empty lines, and apparently it tries to interpret spaces as different fields!

For now, we'll stop at the first empty command (press enter to exit) but it might be nice to support Ctrl-D/Ctrl-C at some point (registering some signal handlers?)

### DLL interface

For the DLL interface, I'm going to suggest C-style strings on the basis that this is clearly 
being designed for use in some web technology, so the program eventually calling this DLL 
might not be written in C/C++.  

If we give it the simplest possible interface that doesn't rely on (e.g.) std::string, then it 
should be easier if anyone needs to use this DLL within a Python/Delphi/whatever program.

Interface:
- command (string)
- response (string buffer)

Downsides:
- possibility of truncated output if the calling function doesn't supply enough space for a long response
- wasted memory if the caller is too cautious with overallocating spce
- maybe we just need to document a "suggested" length?

### Application state

Global variable in the DLL for now ("It is perfectly fine") - once the MVP is working we can 
demo it as part of a discussion on long-term storage requirements.

### Command handling

Looks like std has a regular expression library, which seems like a good start for this text handling.

- Base class can do standard stuff like "does this match"
- Sub classes can be given a regex match list to use when processing a command
- Need to store these as pointers not objects so that the subclassing is retained.
- Suggest list<shared_ptr> since we'll be just be iterating through the list of commands


### Unit tests

Google (gtest) and MStest are both easily available - been using gtest recently, so may as well learn
the other one!

- Remove precompiled headers to avoid clutter.  
- Need to add `$(SolutionDir)\Build\` into the output folder to keep it in the same place as the rest.
- (Same for intermediate files)
- Setting dependency on SupportingProject isn't enough to bring in the functions
- Adding a reference to SupportingProject isn't enough to bring in the functions
- Adding the .lib as linker input isn't enough to bring in the functions
- Apparently we need to declspec export to the class definition?  
- So rearrange config.h to give definitions for "C function exports" and "general exports"

Ok, unit tests are working - we can run a command and check the returned message.

Additional documentation is at https://learn.microsoft.com/en-us/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2022

Looks like it's displaying tests in alphabetical order rather than test order, which is annoying -
maybe need a prefix on the test names, but it's a function name so can't start with a number
so we need *another* prefix (eyeroll emoji)
https://learn.microsoft.com/en-us/dotnet/core/testing/order-unit-tests?pivots=mstest

Maybe want a two-part prefix like A001,A001 for one command, B001,B002 for the next command so
we don't need to renumber things if going back to add unit tests into the earlier work.

# Next steps:

- Get the unit-test project started - it should be able to test simple stuff like O name
- main() is getting large enough to make it a class.  Maybe remove the "part 1" stuff?
  (or create a branch from when it was first working)

Then we can start to think about a command design - I guess the "state" is the "BankAccounts" 
typedef (we could clarify this by making another typedef) so it would be something like 
"BankCommand::handleInternal -> BankingEvent(BankAccounts &state, ...)"

Are we allowed to just manipulate m_bankAccounts after each command, or is there supposed to 
be some "const currentState -> nextState" type structure?  ("Decider pattern" isn't listed on 
https://en.wikipedia.org/wiki/Software_design_pattern but apparently ChatGPT can provide advice)

