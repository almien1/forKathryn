#pragma once
#include "BankEvent.h"

class BankEventWithdraw : public BankEvent
{
public:
	BankEventWithdraw(const Currency amount);

	void apply(BankData& bank) override;

	Currency balanceAdjust(const Currency previousBalance) const override;

	bool showInTransactionHistory() const override;
	TransactionDescription descriptionForTransactionHistory() const override;

private:
	Currency m_amount;
};

