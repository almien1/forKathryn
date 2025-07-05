#pragma once
#include <memory>
#include <string>

class BankData;

class BankEvent
{
public:
	std::string description() const;
	virtual void apply(BankData& bank) = 0;

protected:
	std::string m_description;
};

using BankEventPtr = std::shared_ptr<BankEvent>;
