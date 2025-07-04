#pragma once
#include "BankCommand.h"
class BankCommandOpen : public BankCommand
{
public:
	BankCommandOpen();

	std::string name() const override;

protected:
	std::string handleInternal(const BankCommandFieldList fields, const std::string fullCommand) override;


	// "-O name : Create account with name(O = open)"
};

