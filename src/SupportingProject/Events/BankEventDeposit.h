#pragma once
#include "BankEvent.h"

class BankEventDeposit : public BankEvent
{
public:
	BankEventDeposit(const Currency amount, const BankString currency = L"");

	void apply(BankData& bank) override;

	Currency balanceAdjust(const Currency previousBalance) const override;

	bool showInTransactionHistory() const override;
	TransactionDescription descriptionForTransactionHistory() const override;

private:
	Currency m_amount;
	BankString m_currency; // populated during apply() in original object, and constructor for copied object
};

