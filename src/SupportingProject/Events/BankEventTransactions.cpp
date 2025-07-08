#include "BankEventTransactions.h"
#include "BankData.h"
#include <format>

BankEventTransactions::BankEventTransactions()
{

}

void BankEventTransactions::apply(BankData& bank)
{
	if (bank.selectedAccount.empty())
	{
		m_description = L"No account selected.";
	}
	else
	{
		static const BankString newline = L"\n";
		BankString transactionHistory;
		bool first = true;
		
		for (auto& event : bank.accounts[bank.selectedAccount].history)
		{
			if (event->showInTransactionHistory())
			{
				if (!first)
				{
					transactionHistory += newline;
				}
				transactionHistory += event->descriptionForTransactionHistory();
				first = false;
			}
		}
		m_description = transactionHistory;
	}
}
