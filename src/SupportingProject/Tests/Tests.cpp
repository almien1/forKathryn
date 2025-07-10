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
			Assert::AreEqual(string("Opening account with name \"abcd\"."), bank.command("O abcd"));
		}

		TEST_METHOD(Test004_OpenAccountWithSpaceInTheName)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"abcd efg\"."), bank.command("O abcd efg"));
		}

		TEST_METHOD(Test005_RepeatedOpenAccount)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Opening account with name \"person2\"."), bank.command("O person2"));
			Assert::AreEqual(string("Could not open account with name \"person2\" - already exists"), bank.command("O person2"));
			Assert::AreEqual(string("Opening account with name \"person3\"."), bank.command("O person3"));
		}
		TEST_METHOD(Test006_OpenCloseAccount)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Closing account \"person1\"."), bank.command("C person1"));
			Assert::AreEqual(string("Could not close account \"person1\" - already closed."), bank.command("C person1"));
			Assert::AreEqual(string("Re-opening account \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Closing account \"person1\"."), bank.command("C person1"));
			Assert::AreEqual(string("Re-opening account \"person1\"."), bank.command("O person1"));
		}
		TEST_METHOD(Test007_Activate)
		{
			Banking bank;
			Assert::AreEqual(string("Could not activate account \"person1\" - doesn't exist."), bank.command("A person1"));
			Assert::AreEqual(string("Opening account with name \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Activating account \"person1\"."), bank.command("A person1"));
			Assert::AreEqual(string("Closing account \"person1\"."), bank.command("C person1"));
			// Activating a closed account?
			Assert::AreEqual(string("Activating account \"person1\"."), bank.command("A person1"));
		}
		TEST_METHOD(Test008_Deposit)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Activating account \"person1\"."), bank.command("A person1"));
			Assert::AreEqual(string("Depositing 30.00 into selected account."), bank.command("D 30"));
			Assert::AreEqual(string("Depositing 30.12 into selected account."), bank.command("D 30.12"));
			Assert::AreEqual(string("Depositing 0.00 into selected account."), bank.command("D 0")); // 0 is a valid deposit?
		}
		TEST_METHOD(Test009_InvalidNumbers)
		{
			// (this test was for when currency was stored as a long integer)
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Activating account \"person1\"."), bank.command("A person1"));
			Assert::AreEqual(string("Depositing 999999999999.00 into selected account."), bank.command("D 999999999999"));
		}
		TEST_METHOD(Test010_Withdraw)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Activating account \"person1\"."), bank.command("A person1"));
			Assert::AreEqual(string("Withdrawing 30.00 from selected account."), bank.command("W 30"));
			Assert::AreEqual(string("Withdrawing 30.12 from selected account."), bank.command("W 30.12"));
			Assert::AreEqual(string("Not a valid command."), bank.command("W 30.0"));
			Assert::AreEqual(string("Not a valid command."), bank.command("W 30.000"));
			Assert::AreEqual(string("Withdrawing 0.00 from selected account."), bank.command("W 0"));
			Assert::AreEqual(string("Withdrawing 999999999999.00 from selected account."), bank.command("W 999999999999"));
		}
		TEST_METHOD(Test011_Balance)
		{
			Banking bank;
			Assert::AreEqual(string("No account selected."), bank.command("B"));
			Assert::AreEqual(string("Opening account with name \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Activating account \"person1\"."), bank.command("A person1"));
			Assert::AreEqual(string("Depositing 30.12 into selected account."), bank.command("D 30.12"));
			Assert::AreEqual(string("Balance is 30.12"), bank.command("B"));
			Assert::AreEqual(string("Depositing 66.55 into selected account."), bank.command("D 66.55"));
			Assert::AreEqual(string("Balance is 96.67"), bank.command("B"));
			Assert::AreEqual(string("Withdrawing 12.12 from selected account."), bank.command("W 12.12"));
			Assert::AreEqual(string("Balance is 84.55"), bank.command("B"));
			Assert::AreEqual(string("Withdrawing 20.00 from selected account."), bank.command("W 20"));
			Assert::AreEqual(string("Balance is 64.55"), bank.command("B"));
			Assert::AreEqual(string("Closing account \"person1\"."), bank.command("C person1"));
			Assert::AreEqual(string("Account is closed."), bank.command("B"));
		}
		TEST_METHOD(Test012_ClosedAccountBalance)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Activating account \"person1\"."), bank.command("A person1"));
			Assert::AreEqual(string("Depositing 99.00 into selected account."), bank.command("D 99"));
			Assert::AreEqual(string("Balance is 99.00"), bank.command("B"));
			Assert::AreEqual(string("Closing account \"person1\"."), bank.command("C person1"));
			Assert::AreEqual(string("Account is closed."), bank.command("B"));
			// Now re-open the account, and the balance should be 0 because the account was closed
			Assert::AreEqual(string("Re-opening account \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Balance is 0.00"), bank.command("B"));
		}
		TEST_METHOD(Test013_TransactionHistory)
		{
			Banking bank;
			Assert::AreEqual(string("Opening account with name \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Activating account \"person1\"."), bank.command("A person1"));
			Assert::AreEqual(string("Depositing 30.00 into selected account."), bank.command("D 30"));
			Assert::AreEqual(string("Account opened\nDeposited 30.00"), bank.command("T"));

			Assert::AreEqual(string("Balance is 30.00"), bank.command("B")); // this should not get shown in the history

			Assert::AreEqual(string("Withdrawing 15.00 from selected account."), bank.command("W 15"));
			Assert::AreEqual(string("Closing account \"person1\"."), bank.command("C person1"));
			Assert::AreEqual(string("Re-opening account \"person1\"."), bank.command("O person1"));
			Assert::AreEqual(string("Depositing 9.00 into selected account."), bank.command("D 9"));
			Assert::AreEqual(string("Account opened\nDeposited 30.00\nWithdrew 15.00\nAccount closed\nAccount opened\nDeposited 9.00"), bank.command("T"));

			Assert::AreEqual(string("Balance is 9.00"), bank.command("B"));
		}
	private:
		bool strContains(const string haystack, const string needle)
		{
			return (haystack.find(needle) != string::npos);
		}
	};
}
