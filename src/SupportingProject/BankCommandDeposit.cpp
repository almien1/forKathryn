#include "BankCommandDeposit.h"
#include "BankEventDeposit.h"

BankCommandDeposit::BankCommandDeposit() :
	BankCommand("D ([0-9]{1,9})")
{
	// "D amount : Deposit an amount (D = Deposit)"
}

BankEventPtr BankCommandDeposit::handleInternal(const BankCommandFieldList fields)
{
	try
	{
		Currency amount = std::stoi(fields[1].str());
		return std::make_shared<BankEventDeposit>(amount);
	}
	catch (std::invalid_argument e)
	{
		// What can we return here?
		// - either a generic "not allowed" event that doesn't do anything and just conveys the message
		// - or a deposit of 0 that's marked with an error message as not to be used
		// - or rely on clever regex to protect us against getting these errors
		// Maybe Commands need an optional pre-validation step that can be called after construction?
	}
	catch (std::out_of_range e)
	{
		// (as above - maybe limit the digits to {1,9})
	}
}
