#include "BankEvent.h"

std::string BankEvent::description() const
{
    return m_description;
}

Currency BankEvent::balanceAdjust(const Currency previousBalance) const
{
	// Default behaviour is not to change the balance
	return previousBalance;
}