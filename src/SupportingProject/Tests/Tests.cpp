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
			Assert::AreEqual(wstring(L"Not a valid command."), bank.command(L""));
		}

		TEST_METHOD(Test001_InvalidCommand)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Not a valid command."), bank.command(L"X"));
		}

		TEST_METHOD(Test002_OpenWithoutAName)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Not a valid command."), bank.command(L"O"));
		}

		TEST_METHOD(Test003_OpenAccount)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Opening account with name \"abcd\""), bank.command(L"O abcd"));
		}

		TEST_METHOD(Test004_OpenAccountWithNameVariations)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Opening account with name \"abcd efg\""), bank.command(L"O abcd efg"));
			Assert::AreEqual(wstring(L"Opening account with name \"単体テスト\""), bank.command(L"O 単体テスト"));
		}

		TEST_METHOD(Test005_RepeatedOpenAccount)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Opening account with name \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Opening account with name \"person2\""), bank.command(L"O person2"));
			Assert::AreEqual(wstring(L"Could not open account with name \"person2\" - already exists"), bank.command(L"O person2"));
			Assert::AreEqual(wstring(L"Opening account with name \"person3\""), bank.command(L"O person3"));
		}
		TEST_METHOD(Test006_OpenCloseAccount)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Opening account with name \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Closing account \"person1\""), bank.command(L"C person1"));
			Assert::AreEqual(wstring(L"Could not close account \"person1\" - already closed."), bank.command(L"C person1"));
			Assert::AreEqual(wstring(L"Re-opening account \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Closing account \"person1\""), bank.command(L"C person1"));
			Assert::AreEqual(wstring(L"Re-opening account \"person1\""), bank.command(L"O person1"));
		}
		TEST_METHOD(Test007_Activate)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Could not activate account \"person1\" - doesn't exist."), bank.command(L"A person1"));
			Assert::AreEqual(wstring(L"Opening account with name \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Activating account \"person1\""), bank.command(L"A person1"));
			Assert::AreEqual(wstring(L"Closing account \"person1\""), bank.command(L"C person1"));
			// Activating a closed account?
			Assert::AreEqual(wstring(L"Activating account \"person1\""), bank.command(L"A person1"));
		}
		TEST_METHOD(Test008_Deposit)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Opening account with name \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Activating account \"person1\""), bank.command(L"A person1"));
			Assert::AreEqual(wstring(L"Depositing 30 into selected account"), bank.command(L"D 30"));
			Assert::AreEqual(wstring(L"Depositing 0 into selected account"), bank.command(L"D 0")); // 0 is a valid deposit?
		}
		TEST_METHOD(Test009_InvalidNumbers)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Opening account with name \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Activating account \"person1\""), bank.command(L"A person1"));
			Assert::AreEqual(wstring(L"Not a valid command."), bank.command(L"D 999999999999")); // Too large for a long int
			// Note: this test may need to be changed if the currency format changes to floating point
		}
		TEST_METHOD(Test010_Withdraw)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Opening account with name \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Activating account \"person1\""), bank.command(L"A person1"));
			Assert::AreEqual(wstring(L"Withdrawing 30 from selected account"), bank.command(L"W 30"));
			Assert::AreEqual(wstring(L"Withdrawing 0 from selected account"), bank.command(L"W 0"));
			Assert::AreEqual(wstring(L"Not a valid command."), bank.command(L"W 999999999999"));
		}
		TEST_METHOD(Test011_Balance)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"No account selected."), bank.command(L"B"));
			Assert::AreEqual(wstring(L"Opening account with name \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Activating account \"person1\""), bank.command(L"A person1"));
			Assert::AreEqual(wstring(L"Depositing 30 into selected account"), bank.command(L"D 30"));
			Assert::AreEqual(wstring(L"Balance is 30"), bank.command(L"B"));
			Assert::AreEqual(wstring(L"Depositing 66 into selected account"), bank.command(L"D 66"));
			Assert::AreEqual(wstring(L"Balance is 96"), bank.command(L"B"));
			Assert::AreEqual(wstring(L"Withdrawing 12 from selected account"), bank.command(L"W 12"));
			Assert::AreEqual(wstring(L"Balance is 84"), bank.command(L"B"));
			Assert::AreEqual(wstring(L"Closing account \"person1\""), bank.command(L"C person1"));
			Assert::AreEqual(wstring(L"Account is closed."), bank.command(L"B"));
		}
		TEST_METHOD(Test012_ClosedAccountBalance)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Opening account with name \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Activating account \"person1\""), bank.command(L"A person1"));
			Assert::AreEqual(wstring(L"Depositing 99 into selected account"), bank.command(L"D 99"));
			Assert::AreEqual(wstring(L"Balance is 99"), bank.command(L"B"));
			Assert::AreEqual(wstring(L"Closing account \"person1\""), bank.command(L"C person1"));
			Assert::AreEqual(wstring(L"Account is closed."), bank.command(L"B"));
			// Now re-open the account, and the balance should be 0 because the account was closed
			Assert::AreEqual(wstring(L"Re-opening account \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Balance is 0"), bank.command(L"B"));
		}
		TEST_METHOD(Test013_TransactionHistory)
		{
			Banking bank;
			Assert::AreEqual(wstring(L"Opening account with name \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Activating account \"person1\""), bank.command(L"A person1"));
			Assert::AreEqual(wstring(L"Depositing 30 into selected account"), bank.command(L"D 30"));
			Assert::AreEqual(wstring(L"Account opened\nDeposited 30"), bank.command(L"T"));

			Assert::AreEqual(wstring(L"Balance is 30"), bank.command(L"B")); // this should not get shown in the history

			Assert::AreEqual(wstring(L"Withdrawing 15 from selected account"), bank.command(L"W 15"));
			Assert::AreEqual(wstring(L"Closing account \"person1\""), bank.command(L"C person1"));
			Assert::AreEqual(wstring(L"Re-opening account \"person1\""), bank.command(L"O person1"));
			Assert::AreEqual(wstring(L"Depositing 9 into selected account"), bank.command(L"D 9"));
			Assert::AreEqual(wstring(L"Account opened\nDeposited 30\nWithdrew 15\nAccount closed\nAccount opened\nDeposited 9"), bank.command(L"T"));

			Assert::AreEqual(wstring(L"Balance is 9"), bank.command(L"B"));
		}
	private:
		bool strContains(const wstring haystack, const wstring needle)
		{
			return (haystack.find(needle) != wstring::npos);
		}
	};
}
