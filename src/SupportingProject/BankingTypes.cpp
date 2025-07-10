#include "BankingTypes.h"
#include <format>

BankString BankingTypes::formatCurrency(const BankString currency, const Currency value)
{
	if (value < 0)
	{
		// Formatting of negative currency values?
		// 
		// Options include:
		//   £-33.33       Easier to parse for automated systems.
		//   -£33.33       Easier to read for regular users.
		//   (£33.33)      *Maybe* easier to read for accounting users, but might get misinterpreted.
		//
		return std::format(L"-{}{:1.2f}", currency, -value);
	}
	else
	{
		return std::format(L"{}{:1.2f}", currency, value);
	}
}

const BankString BankingTypes::defaultCurrency()
{
	return L"£";
}
