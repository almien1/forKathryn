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
			// Allow the command to generate an event
			BankEventPtr event = command->handle(input);

			// Apply the event to the bank's current state - this is the step which
			// lets us know whether it worked or not, which allows the message to
			// be created.
			event->apply(m_bank);

			// Now that we have a description, that can be returned to the API
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
