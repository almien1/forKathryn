#include "CppUnitTest.h"
#include "../Banking.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(Test000_EmptyCommand)
		{
			Banking bank;
			Assert::AreEqual(string("Not a valid command - use ? for help."), bank.command(""));
		}

		TEST_METHOD(Test001_InvalidCommand)
		{
			Banking bank;
			Assert::AreEqual(string("Not a valid command - use ? for help."), bank.command("X"));
		}

		TEST_METHOD(Test002_HelpFile)
		{
			Banking bank;

			// This returns quite a long message, so just look for parts of the text.
			// 
			// If any of these fail, easiest way to see the full text is to put a breakpoint after the result= line.
			//
			string result = bank.command("?");

			if (strContains(result, "Not a valid command"))
			{
				Assert::Fail(L"If the help command is removed from the final product, remember to disable the unit test!");
			}

			Assert::IsTrue(strContains(result, "Commands available:"));

			// Check that we got the end of the test (this isn't particularly relevant in the C++
			// interface, but any tests using the DLL interface would be interested in this)
			Assert::IsTrue(strContains(result, "(T = Transactions)"));
			
		}

		TEST_METHOD(Test003_OpenWithoutAName)
		{
			Banking bank;
			Assert::AreEqual(string("Not a valid command - use ? for help."), bank.command("O"));
		}


		TEST_METHOD(Test004_OpenAccount)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"abcd\""), bank.command("O abcd"));
		}

		TEST_METHOD(Test005_OpenAccountWithSpaceInTheName)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"abcd efg\""), bank.command("O abcd efg"));
		}
	private:
		bool strContains(const string haystack, const string needle)
		{
			return (haystack.find(needle) != string::npos);
		}
	};
}
