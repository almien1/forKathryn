#include "BankEventOpen.h"
#include "BankData.h"
#include <format>

BankEventOpen::BankEventOpen(const std::string& accountName) :
	m_accountName(accountName)
{

}

void BankEventOpen::apply(BankData& bank)
{
	if (bank.accounts.contains(m_accountName))
	{
		// TODO: once "close" is implemented, we might want to allow re-opening
		// (if exists and is still open, then give error)
		m_description = std::format("Could not open account with name \"{}\" - already exists", m_accountName);
	}
	else
	{
		m_description = std::format("Opening account with name \"{}\"", m_accountName);
		BankAccountHistory newHistory;
		newHistory.push_back(std::make_shared<BankEventOpen>(m_accountName));
		bank.accounts[m_accountName] = newHistory;
	}
}
