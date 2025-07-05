#include "BankCommandClose.h"
#include "BankEventClose.h"

BankCommandClose::BankCommandClose() :
	BankCommand("C (.*)")
{
	// "- C : Close account (C = Close)"
}

BankEventPtr BankCommandClose::handleInternal(const BankCommandFieldList fields)
{
	return std::make_shared<BankEventClose>(fields[1].str());
}
