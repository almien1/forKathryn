#include "BankEventOpen.h"
#include <format>

BankEventOpen::BankEventOpen(const std::string& accountName)
{
	m_description = std::format("Opening account with name \"{}\"", accountName);
}
