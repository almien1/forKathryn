#include "BankCommandOpen.h"
#include "Events/BankEventOpen.h"

BankCommandOpen::BankCommandOpen() : 
	BankCommand("O (.*)$")
{
	// "-O name : Create account with name(O = open)"
}

BankEventPtr BankCommandOpen::handleInternal(const BankCommandFieldList fields) const
{
	return std::make_shared<BankEventOpen>(fields[1].str());
}
