#pragma once
#include "BankEvent.h"
#include <string>

class BankEventClose : public BankEvent
{
public:
	BankEventClose(const BankString &accountName);

	void apply(BankData& bank) override;

	Currency balanceAdjust(const Currency previousBalance) const override;

	bool showInTransactionHistory() const override;
	TransactionDescription descriptionForTransactionHistory() const override;

private:
	BankString m_accountName;
};

