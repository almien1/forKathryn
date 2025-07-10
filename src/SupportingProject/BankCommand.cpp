#include "BankCommand.h"
#include <stdexcept>

BankCommand::BankCommand(const wchar_t* commandRegexPattern) : 
	m_commandRegex(commandRegexPattern)
{
}

bool BankCommand::recognise(const BankString& potentialCommand) const
{
	bool validCommand = false;
	// Check whether it matches the regex
	BankCommandFieldList fields;
	if (std::regex_match(potentialCommand, fields, m_commandRegex))
	{
		// If so, check whether the fields are valid for this type of command
		if (canHandle(fields))
		{
			validCommand = true;
		}
	}
	return validCommand;
}

bool BankCommand::canHandle(const BankCommandFieldList fields) const
{
	// Assume that a command can handle anything that matches its regular-
	// expression unless they define a canHandle function
	return true;
}

BankEventPtr BankCommand::handle(const BankString command)
{
	BankEventPtr result;
	BankCommandFieldList fields;

	// This should always match, as we will have called recognise() first
	if (std::regex_match(command, fields, m_commandRegex))
	{
		result = handleInternal(fields);
	}
	else
	{
		throw std::runtime_error("Regex mismatch");
	}
	
	return result;
}
