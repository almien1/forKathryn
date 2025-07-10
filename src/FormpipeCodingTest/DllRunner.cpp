#include "DllRunner.h"
#include <format>

DllRunner::DllRunner(const std::wstring& filename) :
	m_filename(filename)
{
}

bool DllRunner::load()
{
	bool success = false;
	m_supportingProject = LoadLibraryW(m_filename.c_str());
	if (m_supportingProject == NULL)
	{
		m_lastError = std::format(L"{} could not be loaded", m_filename);
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
			m_lastError = std::format(L"could not locate bank api in {}", m_filename);
		}
		else if (m_getMessageFunction == nullptr)
		{
			m_lastError = std::format(L"could not locate message function 1 in {}", m_filename);
		}
		else if (m_delMessageFunction == nullptr)
		{
			m_lastError = std::format(L"could not locate message function 2 in {}", m_filename);
		}
		else
		{
			success = true;
		}
	}
	return success;
}

const std::wstring DllRunner::getLastError() const
{
	return m_lastError;
}

const std::wstring DllRunner::runCommand(std::wstring &command) const
{
	// DLL call to process command and return response
	MessageID messageID = m_bankingApi(command.data());
	std::wstring response = m_getMessageFunction(messageID);
	m_delMessageFunction(messageID);
	return response;
}
