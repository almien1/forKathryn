#include "BankCommandHelp.h"

BankCommandHelp::BankCommandHelp() : 
	BankCommand("\\?")
{
	m_helpLines.push_back("Commands available:");
	m_helpLines.push_back("-O name : Create account with name(O = open)");
	m_helpLines.push_back("- A name : Make name the account that following commands will work on(A = Activate)");
	m_helpLines.push_back("- C : Close account(C = Close)");
	m_helpLines.push_back("- D amount : Deposit an amount(D = Deposit)");
	m_helpLines.push_back("- W amount : Withdraw an amount(W = Withdraw)");
	m_helpLines.push_back("- B : Show current balance(B = balance)");
	m_helpLines.push_back("- T : List transactions on account(T = Transactions)");
}

std::string BankCommandHelp::name() const
{
	return("Help");
}

std::string BankCommandHelp::handleInternal(BankCommandFieldList fields, const std::string fullCommand)
{
	// Return help lines as a multi-line response
	std::string response;
	bool first = true;
	for (const auto& line : m_helpLines)
	{
		if (first)
		{
			response += "\n";
		}
		response += line;
	}
	return response;
}
