#include "BankEventDeposit.h"
#include "BankData.h"
#include <format>

BankEventDeposit::BankEventDeposit(const Currency amount, const BankString currency) :
	m_amount(amount),
	m_currency(currency)
{

}

void BankEventDeposit::apply(BankData& bank)
{
	if (bank.selectedAccount.empty())
	{
		m_description = L"Could not deposit - no account selected.";
	}
	else if (bank.accounts[bank.selectedAccount].closed)
	{
		m_description = L"Could not deposit into closed account.";
	}
	else
	{
		m_currency = bank.accounts[bank.selectedAccount].currency;
		m_description = std::format(L"Depositing {} into selected account.", BankingTypes::formatCurrency(m_currency, m_amount));
		bank.accounts[bank.selectedAccount].history.push_back(std::make_shared<BankEventDeposit>(m_amount, m_currency));
	}
}

Currency BankEventDeposit::balanceAdjust(const Currency previousBalance) const
{
	// Deposits add to account balance
	return previousBalance + m_amount;
}

bool BankEventDeposit::showInTransactionHistory() const
{
	return true;
}

TransactionDescription BankEventDeposit::descriptionForTransactionHistory() const
{
	return std::format(L"Deposited {}", BankingTypes::formatCurrency(m_currency, m_amount));
}
