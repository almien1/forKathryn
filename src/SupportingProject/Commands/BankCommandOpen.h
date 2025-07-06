#pragma once
#include "BankCommand.h"
class BankCommandOpen : public BankCommand
{
public:
	BankCommandOpen();

protected:
	BankEventPtr handleInternal(const BankCommandFieldList fields) const override;

};

