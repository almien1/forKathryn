#include "BankEventWithdraw.h"
#include "BankData.h"
#include <format>

BankEventWithdraw::BankEventWithdraw(const Currency amount, const BankString currency) :
	m_amount(amount),
	m_currency(currency)
{

}

void BankEventWithdraw::apply(BankData& bank)
{
	if (bank.selectedAccount.empty())
	{
		m_description = L"Could not withdraw - no account selected.";
	}
	else if (bank.accounts[bank.selectedAccount].closed)
	{
		m_description = L"Could not withdraw from closed account.";
	}
	else
	{
		m_currency = bank.accounts[bank.selectedAccount].currency;
		m_description = std::format(L"Withdrawing {} from selected account.", BankingTypes::formatCurrency(m_currency, m_amount));
		bank.accounts[bank.selectedAccount].history.push_back(std::make_shared<BankEventWithdraw>(m_amount, m_currency));
	}
}

Currency BankEventWithdraw::balanceAdjust(const Currency previousBalance) const
{
	// Withdrawals subtract from account balance
	return previousBalance - m_amount;
}

bool BankEventWithdraw::showInTransactionHistory() const
{
	return true;
}

TransactionDescription BankEventWithdraw::descriptionForTransactionHistory() const
{
	return std::format(L"Withdrew {}", BankingTypes::formatCurrency(m_currency, m_amount));
}
