#pragma once
#include "BankCommand.h"
class BankCommandBalance : public BankCommand
{
public:
	BankCommandBalance();

protected:
	BankEventPtr handleInternal(const BankCommandFieldList fields) const override;

};

