#pragma once
#include "BankCommand.h"
class BankCommandClose : public BankCommand
{
public:
	BankCommandClose();

	std::string name() const override;

protected:
	BankEventPtr handleInternal(const BankCommandFieldList fields) override;

};

