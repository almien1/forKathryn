#pragma once
#include "config.h"
#include "BankCommand.h"
#include "BankData.h"
#include <string>

class SUPPORTING_PROJECT_EXPORT Banking
{
public:
	Banking();

	std::string command(const std::string& input);

protected:
	BankData m_bank;
	BankCommands m_commands;
};

