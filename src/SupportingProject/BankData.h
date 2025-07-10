#pragma once
#include "BankEvent.h"
#include <list>
#include <map>
#include <string>
#include "BankingTypes.h"

// Each bank account contains a list of events for anything that modifies the account,
// and a tag for whether the account has been closed:
using BankAccountHistory = std::list<BankEventPtr>;

class BankAccount
{
public:
	bool closed = false;
	BankString currency = BankingTypes::defaultCurrency();
	BankAccountHistory history;
};

// Bank accounts are referenced by name
using BankAccounts = std::map<BankString, BankAccount>; // account name -> account data

// The "state" of the bank includes the list of accounts,
// and the active account on the current connection:
class BankData
{
public:
	BankString selectedAccount;
	BankAccounts accounts;
};
