#pragma once
#include "BankEvent.h"
#include "BankingTypes.h"
#include <regex>
#include <list>
#include <memory>

using BankCommandFieldList = std::match_results<std::wstring::const_iterator>;

class BankCommand
{
public:
	// Constructor.
	// Supply a regex, using brackets to delimit any information you want out of the command.
	BankCommand(const wchar_t* commandRegexPattern);

	// Test whether a command should be handled by this module
	bool recognise(const BankString& potentialCommand) const;

	// Handle a command
	// - handle() is the main external API, and the base class will do regex processing
	// - handleInternal() is then called with the fields extracted from the regular expression
	BankEventPtr handle(const BankString command);

protected:
	std::wregex m_commandRegex;

	virtual bool canHandle(const BankCommandFieldList fields) const;
	virtual BankEventPtr handleInternal(const BankCommandFieldList fields) const = 0;

};

using BankCommandPtr = std::shared_ptr< BankCommand>;
using BankCommands = std::list<BankCommandPtr>;