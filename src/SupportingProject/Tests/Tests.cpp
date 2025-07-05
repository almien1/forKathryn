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

		TEST_METHOD(Test005_RepeatedOpenAccount)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"person1\""), bank.command("O person1"));
			Assert::AreEqual(string("Opening account with name \"person2\""), bank.command("O person2"));
			Assert::AreEqual(string("Could not open account with name \"person2\" - already exists"), bank.command("O person2"));
			Assert::AreEqual(string("Opening account with name \"person3\""), bank.command("O person3"));
		}
		TEST_METHOD(Test006_OpenCloseAccount)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"person1\""), bank.command("O person1"));
			Assert::AreEqual(string("Closing account \"person1\""), bank.command("C person1"));
			Assert::AreEqual(string("Could not close account \"person1\" - already closed."), bank.command("C person1"));
			Assert::AreEqual(string("Re-opening account \"person1\""), bank.command("O person1"));
			Assert::AreEqual(string("Closing account \"person1\""), bank.command("C person1"));
			Assert::AreEqual(string("Re-opening account \"person1\""), bank.command("O person1"));
		}
		TEST_METHOD(Test007_Activate)
		{
			Banking bank;
			Assert::AreEqual(string("Could not activate account \"person1\" - doesn't exist."), bank.command("A person1"));
			Assert::AreEqual(string("Opening account with name \"person1\""), bank.command("O person1"));
			Assert::AreEqual(string("Activating account \"person1\""), bank.command("A person1"));
			Assert::AreEqual(string("Closing account \"person1\""), bank.command("C person1"));
			Assert::AreEqual(string("Could not activate closed account \"person1\"."), bank.command("A person1"));
		}
		TEST_METHOD(Test008_Deposit)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"person1\""), bank.command("O person1"));
			Assert::AreEqual(string("Activating account \"person1\""), bank.command("A person1"));
			Assert::AreEqual(string("Depositing £30 into selected account"), bank.command("D 30"));
			Assert::AreEqual(string("Depositing £0 into selected account"), bank.command("D 0")); // 0 is a valid deposit?
			// Note: the £ isn't displaying correctly on console
		}

	private:
		bool strContains(const string haystack, const string needle)
		{
			return (haystack.find(needle) != string::npos);
		}
	};
}
