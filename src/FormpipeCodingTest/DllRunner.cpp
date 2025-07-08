#include "DllRunner.h"
#include <format>

DllRunner::DllRunner(const std::string& filename) :
	m_filename(filename)
{
}

bool DllRunner::load()
{
	bool success = false;
	m_supportingProject = LoadLibraryA(m_filename.c_str());
	if (m_supportingProject == NULL)
	{
		m_lastError = std::format("{} could not be loaded", m_filename);
	}
	else
	{
		static const char* bankingFunctionName = "bankingCommand";
		static const char* getMessageFunctionName = "getMessage";
		static const char* deleteMessageFunctionName = "deleteMessage";

		// Load the DLL functions
		m_bankingApi = reinterpret_cast<BankApiCommand>(GetProcAddress(m_supportingProject, bankingFunctionName));
		m_getMessageFunction = reinterpret_cast<BankApiGetMessage>(GetProcAddress(m_supportingProject, getMessageFunctionName));
		m_delMessageFunction = reinterpret_cast<BankApiDeleteMessage>(GetProcAddress(m_supportingProject, deleteMessageFunctionName));

		if (m_bankingApi == nullptr)
		{
			m_lastError = std::format("could not locate {} in {}", bankingFunctionName, m_filename);
		}
		else if (m_getMessageFunction == nullptr)
		{
			m_lastError = std::format("could not locate {} in {}", getMessageFunctionName, m_filename);
		}
		else if (m_delMessageFunction == nullptr)
		{
			m_lastError = std::format("could not locate {} in {}", deleteMessageFunctionName, m_filename);
		}
		else
		{
			success = true;
		}
	}
	return success;
}

const std::string DllRunner::getLastError() const
{
	return m_lastError;
}

const std::string DllRunner::runCommand(std::string &command) const
{
	// DLL call to process command and return response
	MessageID messageID = m_bankingApi(command.data());
	std::string response = m_getMessageFunction(messageID);
	m_delMessageFunction(messageID);
	return response;
}
