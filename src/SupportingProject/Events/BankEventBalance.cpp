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
		m_description = L"No account selected.";
	}
	else if (bank.accounts[bank.selectedAccount].closed)
	{
		m_description = L"Account is closed.";
	}
	else
	{
		// Calculate the balance by adding deposits/withdrawals over time
		Currency balance = 0;
		for (auto& event : bank.accounts[bank.selectedAccount].history)
		{
			balance = event->balanceAdjust(balance);
		}

		// This is the only point at which currency values can be negative.
		// It currently displays like £-33.33, but -£33.33 or (£33.33) might be more "correct"
		m_description = std::format(L"Balance is {}{:1.2f}", bank.accounts[bank.selectedAccount].currency, balance);
	}
}
