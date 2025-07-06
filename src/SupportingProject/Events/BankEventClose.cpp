#include "BankEventClose.h"
#include "BankData.h"
#include <format>

BankEventClose::BankEventClose(const std::string& accountName) :
	m_accountName(accountName)
{

}

void BankEventClose::apply(BankData& bank)
{
	if (!bank.accounts.contains(m_accountName))
	{
		m_description = std::format("Could not close account \"{}\" - doesn't exist.", m_accountName);
	}
	else if (bank.accounts[m_accountName].closed)
	{
		m_description = std::format("Could not close account \"{}\" - already closed.", m_accountName);
	}
	else
	{
		m_description = std::format("Closing account \"{}\"", m_accountName);
		bank.accounts[m_accountName].history.push_back(std::make_shared<BankEventClose>(m_accountName));
		bank.accounts[m_accountName].closed = true;
	}
}

Currency BankEventClose::balanceAdjust(const Currency previousBalance) const
{
	// Set the balance to 0 on account closure
	return 0;
}


bool BankEventClose::showInTransactionHistory() const
{
	return true;
}

TransactionDescription BankEventClose::descriptionForTransactionHistory() const
{
	return "Account closed";
}