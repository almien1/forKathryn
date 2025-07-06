#pragma once
#include "BankCommand.h"
class BankCommandActivate : public BankCommand
{
public:
	BankCommandActivate();

protected:
	BankEventPtr handleInternal(const BankCommandFieldList fields) const override;

};

