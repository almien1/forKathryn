#include "BankCommand.h"
#include <stdexcept>

BankCommand::BankCommand(const char* commandRegexPattern) : 
	m_commandRegex(commandRegexPattern)
{
}

bool BankCommand::recognise(const std::string& potentialCommand) const
{
	bool matched = std::regex_match(potentialCommand, m_commandRegex);
	return matched;
}

BankEventPtr BankCommand::handle(const std::string command)
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