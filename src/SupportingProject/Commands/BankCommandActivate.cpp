#include "BankCommandActivate.h"
#include "Events/BankEventActivate.h"

BankCommandActivate::BankCommandActivate() :
	BankCommand("A (.*)$")
{
	// "A name : Make name the account that following commands will work on (A = Activate)"
}

BankEventPtr BankCommandActivate::handleInternal(const BankCommandFieldList fields) const
{
	return std::make_shared<BankEventActivate>(fields[1].str());
}
