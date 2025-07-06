#pragma once
#include <memory>
#include <string>
#include "BankingTypes.h"

class BankData;

using TransactionDescription = std::string;

class BankEvent
{
public:
	std::string description() const;
	virtual void apply(BankData& bank) = 0;

	// Override this if the event changes the account balance
	virtual Currency balanceAdjust(const Currency previousBalance) const;

	// Override these to list the transaction in the account history
	virtual bool showInTransactionHistory() const;
	virtual TransactionDescription descriptionForTransactionHistory() const;

protected:
	std::string m_description;
};

using BankEventPtr = std::shared_ptr<BankEvent>;
