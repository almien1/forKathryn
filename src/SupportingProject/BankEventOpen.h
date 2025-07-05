#pragma once
#include "BankEvent.h"
#include <string>

class BankEventOpen : public BankEvent
{
public:
	BankEventOpen(const std::string &accountName);
};

