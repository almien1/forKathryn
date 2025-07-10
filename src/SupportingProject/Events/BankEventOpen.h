#pragma once
#include "BankEvent.h"
#include <string>

class BankEventOpen : public BankEvent
{
public:
	BankEventOpen(const BankString&accountName);

	void apply(BankData& bank) override;

	bool showInTransactionHistory() const override;
	TransactionDescription descriptionForTransactionHistory() const override;

private:
	BankString m_accountName;
};

