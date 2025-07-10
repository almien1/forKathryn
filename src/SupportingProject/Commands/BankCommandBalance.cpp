#include "BankCommandBalance.h"
#include "Events/BankEventBalance.h"

BankCommandBalance::BankCommandBalance() :
	BankCommand("B$")
{
	// "B : Show current balance (B = balance)"
}

BankEventPtr BankCommandBalance::handleInternal(const BankCommandFieldList fields) const
{
	return std::make_shared<BankEventBalance>();
}
