#pragma once
#include "BankCommand.h"
class BankCommandClose : public BankCommand
{
public:
	BankCommandClose();

protected:
	BankEventPtr handleInternal(const BankCommandFieldList fields) const override;

};

