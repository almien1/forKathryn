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
			Assert::AreEqual(string("Not a valid command."), bank.command(""));
		}

		TEST_METHOD(Test001_InvalidCommand)
		{
			Banking bank;
			Assert::AreEqual(string("Not a valid command."), bank.command("X"));
		}

		TEST_METHOD(Test002_OpenWithoutAName)
		{
			Banking bank;
			Assert::AreEqual(string("Not a valid command."), bank.command("O"));
		}


		TEST_METHOD(Test003_OpenAccount)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"abcd\""), bank.command("O abcd"));
		}

		TEST_METHOD(Test004_OpenAccountWithSpaceInTheName)
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
