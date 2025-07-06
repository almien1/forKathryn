#include "BankEventWithdraw.h"
#include "BankData.h"
#include <format>

BankEventWithdraw::BankEventWithdraw(const Currency amount) :
	m_amount(amount)
{

}

void BankEventWithdraw::apply(BankData& bank)
{
	if (bank.selectedAccount.empty())
	{
		m_description = "Could not withdraw - no account selected.";
	}
	else if (bank.accounts[bank.selectedAccount].closed)
	{
		m_description = "Could not withdraw from closed account.";
	}
	else
	{
		m_description = std::format("Withdrawing {} from selected account", m_amount);
		bank.accounts[bank.selectedAccount].history.push_back(std::make_shared<BankEventWithdraw>(m_amount));
	}
}

Currency BankEventWithdraw::balanceAdjust(const Currency previousBalance) const
{
	// Withdrawals subtract from account balance
	return previousBalance - m_amount;
}
