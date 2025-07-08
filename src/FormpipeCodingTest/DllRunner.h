#pragma once
#include <string>
#include "../SupportingProject/banking-api.h"
#include <Windows.h>

class DllRunner
{
public:
	DllRunner(const std::string& filename);
	
	bool load();
	const std::string getLastError() const;

	const std::string runCommand(std::string &command) const;

protected:
	// DLL pointer
	HMODULE m_supportingProject = NULL;

	// Functions within the DLL
	BankApiCommand m_bankingApi = nullptr;
	BankApiGetMessage m_getMessageFunction = nullptr;
	BankApiDeleteMessage m_delMessageFunction = nullptr;

private:
	std::string m_filename;
	std::string m_lastError;
};

