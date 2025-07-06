#pragma once
#include "BankEvent.h"
#include "BankingTypes.h"
#include <string>

class BankEventDeposit : public BankEvent
{
public:
	BankEventDeposit(const Currency amount);

	void apply(BankData& bank) override;

	Currency balanceAdjust(const Currency previousBalance) const override;

private:
	Currency m_amount;
};

