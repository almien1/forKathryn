#include "Banking.h"

// Command headers
#include "BankCommandHelp.h"

Banking::Banking()
{
	// Assign commands
	m_commands.push_back(std::make_shared<BankCommandHelp>());

}

std::string Banking::command(const std::string& input)
{
	std::string response;
	bool handled = false;
	for (auto& command : m_commands)
	{
		if (command->recognise(input))
		{
			response = "You have been directed to module " + command->name();
			handled = true;
		}
	}
	if (!handled)
	{
		response = "No modules found for handling this command";
	}

	return response;
}
