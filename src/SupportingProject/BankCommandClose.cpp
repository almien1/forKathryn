#include "BankCommandClose.h"
#include "BankEventClose.h"

BankCommandClose::BankCommandClose() :
	BankCommand("C (.*)")
{
	// "- C : Close account (C = Close)"
}

std::string BankCommandClose::name() const
{
	return("Open account");
}

BankEventPtr BankCommandClose::handleInternal(const BankCommandFieldList fields)
{
	return std::make_shared<BankEventClose>(fields[1].str());
}
