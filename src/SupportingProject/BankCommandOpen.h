#pragma once
#include "BankCommand.h"
class BankCommandOpen : public BankCommand
{
public:
	BankCommandOpen();

	std::string name() const override;

protected:
	BankEventPtr handleInternal(const BankCommandFieldList fields) override;

};

