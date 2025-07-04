#pragma once
#include <regex>
#include <list>
#include <memory>

/* Note: Copy these to each subclass header to get started

public:
	std::string name() const override;
protected:
	std::string handleInternal(const BankCommandFieldList fields, const std::string fullCommand) override;

*/


class BankCommand
{
public:
	// Constructor.
	// Supply a regex, using brackets to delimit any information you want out of the command.
	BankCommand(const char* commandRegexPattern);

	// Test whether a command should be handled by this module
	bool recognise(const std::string& potentialCommand);

	// Module name
	virtual std::string name() const = 0;

	// Handle a command
	// - handle() is the main external API, and the base class will do regex processing
	// - handleInternal() is then called with the fields extracted from the regular expression
	// 
	// - Note the "fullCommand" parameter should *rarely* be used 
	// - the fields will have been processed and are available in the "fields" parameter
	std::string handle(const std::string command);

protected:
	std::regex m_commandRegex;

	using BankCommandFieldList = std::match_results<std::string::const_iterator>;
	virtual std::string handleInternal(const BankCommandFieldList fields, const std::string fullCommand) = 0;

};

using BankCommandPtr = std::shared_ptr< BankCommand>;
using BankCommands = std::list<BankCommandPtr>;