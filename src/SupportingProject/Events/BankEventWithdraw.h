#pragma once
#include "BankEvent.h"
#include "BankingTypes.h"
#include <string>

class BankEventWithdraw : public BankEvent
{
public:
	BankEventWithdraw(const Currency amount);

	void apply(BankData& bank) override;

	Currency balanceAdjust(const Currency previousBalance) const override;

private:
	Currency m_amount;
};

