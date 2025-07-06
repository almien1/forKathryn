#pragma once
#include "BankEvent.h"

class BankEventTransactions : public BankEvent
{
public:
	BankEventTransactions();

	void apply(BankData& bank) override;
};

