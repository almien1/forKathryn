#include "BankCommandDeposit.h"
#include "Events/BankEventDeposit.h"

BankCommandDeposit::BankCommandDeposit() :
	BankCommand(L"D ([0-9]+)")
{
	// "D amount : Deposit an amount (D = Deposit)"
}

bool BankCommandDeposit::canHandle(const BankCommandFieldList fields) const
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

BankEventPtr BankCommandDeposit::handleInternal(const BankCommandFieldList fields) const
{
	Currency amount = std::stoi(fields[1].str());
	return std::make_shared<BankEventDeposit>(amount);
}
