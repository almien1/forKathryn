#include "BankCommandWithdraw.h"
#include "Events/BankEventWithdraw.h"

BankCommandWithdraw::BankCommandWithdraw() :
	BankCommand("W ([0-9]+([\\.][0-9]{2})?)$")
{
	// "W amount : Withdraw an amount (W = Withdraw)"
}

bool BankCommandWithdraw::canHandle(const BankCommandFieldList fields) const
{
	// Just test converting the "number" to see if it's actually a valid number
	bool success = false;
	try
	{
		handleInternal(fields); 
		success = true;
	}
	catch (std::invalid_argument e)
	{
	}
	catch (std::out_of_range e)
	{
	}
	return success;
}

BankEventPtr BankCommandWithdraw::handleInternal(const BankCommandFieldList fields) const
{
	Currency amount = std::stod(fields[1].str());
	return std::make_shared<BankEventWithdraw>(amount);
}
