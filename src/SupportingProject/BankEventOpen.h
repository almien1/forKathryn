#pragma once
#include "BankEvent.h"
#include <string>

class BankEventOpen : public BankEvent
{
public:
	BankEventOpen(const std::string &accountName);

	void apply(BankData& bank) override;

private:
	std::string m_accountName;
};

