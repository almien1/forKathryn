#include "BankCommandOpen.h"

BankCommandOpen::BankCommandOpen() : 
	BankCommand("O (.*)")
{

}

std::string BankCommandOpen::name() const
{
	return("Open account");
}

std::string BankCommandOpen::handleInternal(const BankCommandFieldList fields, const std::string fullCommand)
{
	return std::string("Opening account with name \"") + fields[0].str() + std::string("\"");
}
