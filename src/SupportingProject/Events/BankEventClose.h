#pragma once
#include "BankEvent.h"
#include <string>

class BankEventClose : public BankEvent
{
public:
	BankEventClose(const std::string &accountName);

	void apply(BankData& bank) override;

	Currency balanceAdjust(const Currency previousBalance) const override;

private:
	std::string m_accountName;
};

