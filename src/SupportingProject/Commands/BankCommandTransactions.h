#pragma once
#include "BankCommand.h"
class BankCommandTransactions : public BankCommand
{
public:
	BankCommandTransactions();

protected:
	BankEventPtr handleInternal(const BankCommandFieldList fields) const override;

};

