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
