#pragma once
#include "BankCommand.h"
class BankCommandDeposit : public BankCommand
{
public:
	BankCommandDeposit();

protected:
	bool canHandle(const BankCommandFieldList fields) const override;
	BankEventPtr handleInternal(const BankCommandFieldList fields) const override;

};

