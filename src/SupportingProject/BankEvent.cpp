#include "BankEvent.h"

BankString BankEvent::description() const
{
    return m_description;
}

Currency BankEvent::balanceAdjust(const Currency previousBalance) const
{
	// Default behaviour is not to change the balance
	return previousBalance;
}

bool BankEvent::showInTransactionHistory() const
{
	// Default is not to display transactions which haven't overridden this
	return false;
	// (remember that transactions which return false here might not even 
	//  be recorded in the account history)
}

TransactionDescription BankEvent::descriptionForTransactionHistory() const
{
	// (will never be called as showInTransactionHistory is false for base-class)
	return L"";
}
