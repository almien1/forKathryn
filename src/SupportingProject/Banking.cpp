#include "Banking.h"

// Command headers
#include "BankCommandOpen.h"

Banking::Banking()
{
	// Assign commands
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
			BankEventPtr event = command->handle(input);
			response = event->description();
			handled = true;
		}
	}
	if (!handled)
	{
		response = "Not a valid command.";
	}

	return response;
}
