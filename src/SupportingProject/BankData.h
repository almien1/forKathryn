#pragma once
#include "BankEvent.h"
#include <list>
#include <map>
#include <string>

using BankAccountHistory = std::list<BankEventPtr>;
using BankAccounts = std::map<std::string, BankAccountHistory>;

typedef struct
{
	std::string selectedAccount;
	BankAccounts accounts;
} BankData;
