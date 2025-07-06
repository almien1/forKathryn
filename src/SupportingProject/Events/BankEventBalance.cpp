#include "BankEventBalance.h"
#include "BankData.h"
#include <format>

BankEventBalance::BankEventBalance()
{

}

void BankEventBalance::apply(BankData& bank)
{
	if (bank.selectedAccount.empty())
	{
		m_description = "No account selected.";
	}
	else if (bank.accounts[bank.selectedAccount].closed)
	{
		m_description = "Account is closed.";
	}
	else
	{
		// Calculate the balance by adding deposits/withdrawals over time
		Currency balance = 0;
		for (auto& event : bank.accounts[bank.selectedAccount].history)
		{
			balance = event->balanceAdjust(balance);
		}
		m_description = std::format("Balance is {}", balance);
	}
}
