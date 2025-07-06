#pragma once
#include "BankCommand.h"
class BankCommandWithdraw : public BankCommand
{
public:
	BankCommandWithdraw();

protected:
	bool canHandle(const BankCommandFieldList fields) const override;
	BankEventPtr handleInternal(const BankCommandFieldList fields) const override;

};

