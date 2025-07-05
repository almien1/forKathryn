#pragma once
#include "BankEvent.h"
#include <list>
#include <map>
#include <string>

using BankAccountHistory = std::list<BankEventPtr>;

class BankAccount
{
public:
	bool closed;
	BankAccountHistory history;
};

using BankAccounts = std::map<std::string, BankAccount>;

class BankData
{
public:
	std::string selectedAccount;
	BankAccounts accounts;
};
