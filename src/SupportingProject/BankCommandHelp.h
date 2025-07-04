#pragma once
#include "BankCommand.h"
#include <string>
#include <list>

class BankCommandHelp : public BankCommand
{
public:
	BankCommandHelp();

	std::string name() const override;

protected:
	std::string handleInternal(BankCommandFieldList fields, const std::string fullCommand) override;

private:
	std::list<std::string> m_helpLines;
};

