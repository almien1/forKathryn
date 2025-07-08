#pragma once
#include "BankEvent.h"
#include <list>
#include <map>
#include <string>

// Each bank account contains a list of events for anything that modifies the account,
// and a tag for whether the account has been closed:
using BankAccountHistory = std::list<BankEventPtr>;

class BankAccount
{
public:
	bool closed = false;
	BankAccountHistory history;
};

// Bank accounts are referenced by name
using BankAccounts = std::map<std::string, BankAccount>; // account name -> account data

// The "state" of the bank includes the list of accounts,
// and the active account on the current connection:
class BankData
{
public:
	std::string selectedAccount;
	BankAccounts accounts;
};
