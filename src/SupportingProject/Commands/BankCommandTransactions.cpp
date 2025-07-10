#include "BankCommandTransactions.h"
#include "Events/BankEventTransactions.h"

BankCommandTransactions::BankCommandTransactions() :
	BankCommand("T$")
{
	// "T : List transactions on account (T = Transactions)"
}

BankEventPtr BankCommandTransactions::handleInternal(const BankCommandFieldList fields) const
{
	return std::make_shared<BankEventTransactions>();
}
