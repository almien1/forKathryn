#pragma once
#include "BankEvent.h"
#include <string>

class BankEventActivate : public BankEvent
{
public:
	BankEventActivate(const std::string &accountName);

	void apply(BankData& bank) override;

private:
	std::string m_accountName;
};

