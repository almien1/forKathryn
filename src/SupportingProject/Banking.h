#pragma once
#include "config.h"
#include "BankCommand.h"
#include "BankData.h"
#include "BankingTypes.h"
#include <string>

class SUPPORTING_PROJECT_EXPORT Banking
{
public:
	Banking();

	BankString command(const BankString& input);

protected:
	BankData m_bank;
	BankCommands m_commands;
};

