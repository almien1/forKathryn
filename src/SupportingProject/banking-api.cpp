#include "banking-api.h"
#include "Banking.h"
#include <string>
#include <map>

// Global "banking" object to keep state in memory for duration of the executable which loads this DLL
Banking g_banking;

// Messages waiting to be picked up by the calling system
std::map<MessageID, std::string> g_messages;
MessageID g_nextMessageID = 0;

MessageID bankingCommand(const BankingApiString command)
{
	MessageID messageID = g_nextMessageID;
	g_nextMessageID++;

	// Run the command against the banking system, and store the returned 
	// message long enough for the calling function to collect it
	g_messages[messageID] = g_banking.command(std::string(command));

	return messageID;
}

const BankingApiString getMessage(const MessageID messageID)
{
	return g_messages[messageID].data();
}

void deleteMessage(const MessageID messageID)
{
	g_messages.erase(messageID);
}