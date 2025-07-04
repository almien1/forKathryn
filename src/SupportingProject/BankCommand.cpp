#include "BankCommand.h"
#include <stdexcept>

BankCommand::BankCommand(const char* commandRegexPattern) : 
	m_commandRegex(commandRegexPattern)
{
}

bool BankCommand::recognise(const std::string& potentialCommand)
{
	bool matched = std::regex_match(potentialCommand, m_commandRegex);
	return matched;
}

std::string BankCommand::handle(const std::string command)
{
	std::string result;
	BankCommandFieldList fields;

	// This should always match, as we will have called recognise() first
	if (std::regex_match(command, fields, m_commandRegex))
	{
		result = handleInternal(fields, command);
	}
	else
	{
		throw std::runtime_error("Regex mismatch");
	}
	
	return result;
}