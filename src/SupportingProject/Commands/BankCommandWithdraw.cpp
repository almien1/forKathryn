#include "BankCommandWithdraw.h"
#include "Events/BankEventWithdraw.h"

BankCommandWithdraw::BankCommandWithdraw() :
	BankCommand("W ([0-9]+)")
{
	// "W amount : Withdraw an amount (W = Withdraw)"
}

bool BankCommandWithdraw::canHandle(const BankCommandFieldList fields) const
{
	// Just test converting the "number" to see if it's actually a valid number
	try
	{
		handleInternal(fields); 
		return true;
		// we could just copy the stoi() here, but calling the real function ensures we always 
		// test the real code (although it "wastes" a make_shared call)
	}
	catch (std::invalid_argument e)
	{
		return false;
	}
	catch (std::out_of_range e)
	{
		return false;
	}
}

BankEventPtr BankCommandWithdraw::handleInternal(const BankCommandFieldList fields) const
{
	Currency amount = std::stoi(fields[1].str());
	return std::make_shared<BankEventWithdraw>(amount);
}
