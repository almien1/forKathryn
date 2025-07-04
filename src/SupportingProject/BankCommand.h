#pragma once
#include <regex>
#include <list>
#include <memory>

class BankCommand
{
public:
	// Constructor.
	// Supply a regex, using brackets to delimit any information you want out of the command.
	BankCommand(const char* commandRegexPattern);

	// Test whether a command should be handled by this module
	bool recognise(const std::string& potentialCommand);

	// Overridables
	virtual std::string name() const = 0;

protected:
	std::regex m_commandRegex;
};

using BankCommandPtr = std::shared_ptr< BankCommand>;
using BankCommands = std::list<BankCommandPtr>;