#include "BankCommandOpen.h"
#include "BankEventOpen.h"

BankCommandOpen::BankCommandOpen() : 
	BankCommand("O (.*)")
{
	// "-O name : Create account with name(O = open)"
}

BankEventPtr BankCommandOpen::handleInternal(const BankCommandFieldList fields)
{
	return std::make_shared<BankEventOpen>(fields[1].str());
}
