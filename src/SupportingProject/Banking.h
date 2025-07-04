#pragma once
#include "BankAccount.h"
#include "BankCommand.h"
#include <string>

class Banking
{
public:
	Banking();

	std::string command(const std::string& input);

protected:
	BankAccounts m_bankAccounts;

	BankCommands m_commands;
};

