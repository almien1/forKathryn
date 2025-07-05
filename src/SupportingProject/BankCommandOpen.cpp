#include "BankCommandOpen.h"
#include "BankEventOpen.h"

BankCommandOpen::BankCommandOpen() : 
	BankCommand("O (.*)")
{
	// "-O name : Create account with name(O = open)"
}

std::string BankCommandOpen::name() const
{
	return("Open account");
}

BankEventPtr BankCommandOpen::handleInternal(const BankCommandFieldList fields)
{
	return std::make_shared<BankEventOpen>(fields[1].str());
}
