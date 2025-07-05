#include "Banking.h"

// Command headers
#include "BankCommandHelp.h"
#include "BankCommandOpen.h"

Banking::Banking()
{
	static const bool includeHelpOption = true;

	// Assign commands
	if (includeHelpOption)
	{
		m_commands.push_back(std::make_shared<BankCommandHelp>());
	}
	m_commands.push_back(std::make_shared<BankCommandOpen>());

}

std::string Banking::command(const std::string& input)
{
	std::string response;
	bool handled = false;
	for (auto& command : m_commands)
	{
		if (command->recognise(input))
		{
			response = command->handle(input);
			handled = true;
		}
	}
	if (!handled)
	{
		response = "Not a valid command - use ? for help.";
	}

	return response;
}
