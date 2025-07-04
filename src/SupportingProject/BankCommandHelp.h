#pragma once
#include "BankCommand.h"

class BankCommandHelp : public BankCommand
{
public:
	BankCommandHelp();

	std::string name() const override;
};
