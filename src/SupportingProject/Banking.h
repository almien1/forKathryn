#pragma once
#include "BankAccount.h"
#include <string>

class Banking
{
public:
	std::string command(const std::string& input);

protected:
	BankAccounts m_bankAccounts;
};

