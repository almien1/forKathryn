#include "BankEventOpen.h"
#include "BankData.h"
#include <format>

BankEventOpen::BankEventOpen(const BankString& accountName) :
	m_accountName(accountName)
{

}

void BankEventOpen::apply(BankData& bank)
{
	if (bank.accounts.contains(m_accountName))
	{
		if (bank.accounts[m_accountName].closed)
		{
			m_description = std::format(L"Re-opening account \"{}\".", m_accountName);
			bank.accounts[m_accountName].closed = false;
			bank.accounts[m_accountName].history.push_back(std::make_shared<BankEventOpen>(m_accountName));
		}
		else
		{
			m_description = std::format(L"Could not open account with name \"{}\" - already exists", m_accountName);
		}
	}
	else
	{
		m_description = std::format(L"Opening account with name \"{}\".", m_accountName);
		BankAccount newAccount;
		newAccount.closed = false;
		newAccount.history.push_back(std::make_shared<BankEventOpen>(m_accountName));
		bank.accounts[m_accountName] = newAccount;
	}
}

bool BankEventOpen::showInTransactionHistory() const
{
	return true;
}

TransactionDescription BankEventOpen::descriptionForTransactionHistory() const
{
	return L"Account opened";
}

