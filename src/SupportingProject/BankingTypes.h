#pragma once
#include <string>

// Option for variable to store currency
using Currency = double;

using BankString = std::wstring;

class BankingTypes
{
public:
	static BankString formatCurrency(const BankString currency, const Currency value);
	static const BankString defaultCurrency();
};