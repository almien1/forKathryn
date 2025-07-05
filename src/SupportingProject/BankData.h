#pragma once
#include "BankEvent.h"
#include <list>
#include <map>
#include <string>

using BankAccountHistory = std::list<BankEventPtr>;
using BankAccounts = std::map<std::string, BankAccountHistory>;

class BankData
{
public:
	std::string selectedAccount;
	BankAccounts accounts;
};
