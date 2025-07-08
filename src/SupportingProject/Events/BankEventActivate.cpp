#include "BankEventActivate.h"
#include "BankData.h"
#include <format>

BankEventActivate::BankEventActivate(const std::string& accountName) :
	m_accountName(accountName)
{

}

void BankEventActivate::apply(BankData& bank)
{
	if (!bank.accounts.contains(m_accountName))
	{
		m_description = std::format("Could not activate account \"{}\" - doesn't exist.", m_accountName);
	}
	else
	{
		m_description = std::format("Activating account \"{}\"", m_accountName);
		bank.selectedAccount = m_accountName;
	}
}
