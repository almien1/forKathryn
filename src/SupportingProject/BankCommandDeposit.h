#pragma once
#include "BankCommand.h"
class BankCommandDeposit : public BankCommand
{
public:
	BankCommandDeposit();

protected:
	BankEventPtr handleInternal(const BankCommandFieldList fields) override;

};

