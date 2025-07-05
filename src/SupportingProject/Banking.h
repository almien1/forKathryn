#pragma once
#include "config.h"
#include "BankAccount.h"
#include "BankCommand.h"
#include <string>

class SUPPORTING_PROJECT_EXPORT Banking
{
public:
	Banking();

	std::string command(const std::string& input);

protected:
	BankAccounts m_bankAccounts;

	BankCommands m_commands;
};

