#include "BankCommandDeposit.h"
#include "Events/BankEventDeposit.h"

BankCommandDeposit::BankCommandDeposit() :
	BankCommand("D ([0-9]+)")
{
	// "D amount : Deposit an amount (D = Deposit)"
}

bool BankCommandDeposit::canHandle(const BankCommandFieldList fields) const
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

BankEventPtr BankCommandDeposit::handleInternal(const BankCommandFieldList fields) const
{
	Currency amount = std::stoi(fields[1].str());
	return std::make_shared<BankEventDeposit>(amount);
}
