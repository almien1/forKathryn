#pragma once
#include "BankEvent.h"

class BankEventBalance : public BankEvent
{
public:
	BankEventBalance();

	void apply(BankData& bank) override;
};

