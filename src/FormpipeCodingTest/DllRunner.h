#pragma once
#include <string>
#include "../SupportingProject/banking-api.h"
#include <Windows.h>

class DllRunner
{
public:
	DllRunner(const std::wstring& filename);
	
	bool load();
	const std::wstring getLastError() const;

	const std::wstring runCommand(std::wstring &command) const;

protected:
	// DLL pointer
	HMODULE m_supportingProject = NULL;

	// Functions within the DLL
	BankApiCommand m_bankingApi = nullptr;
	BankApiGetMessage m_getMessageFunction = nullptr;
	BankApiDeleteMessage m_delMessageFunction = nullptr;

private:
	std::wstring m_filename;
	std::wstring m_lastError;
};

