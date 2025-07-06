#pragma once
#include "BankEvent.h"
#include "BankingTypes.h"
#include <string>

class BankEventBalance : public BankEvent
{
public:
	BankEventBalance();

	void apply(BankData& bank) override;

};

