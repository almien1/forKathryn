#pragma once
#include "BankEvent.h"
#include <string>

class BankEventActivate : public BankEvent
{
public:
	BankEventActivate(const BankString &accountName);

	void apply(BankData& bank) override;

private:
	BankString m_accountName;
};

