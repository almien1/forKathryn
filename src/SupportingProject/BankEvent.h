#pragma once
#include <memory>
#include <string>

class BankEvent
{
public:
	std::string description() const;

protected:
	std::string m_description;
};

using BankEventPtr = std::shared_ptr<BankEvent>;