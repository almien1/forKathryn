#include "BankCommandHelp.h"

BankCommandHelp::BankCommandHelp() : 
	BankCommand("h") // TODO ("\\?") but test with something easy first, as ? is special in regex and we don't know how many times we need to escape it
{
}

std::string BankCommandHelp::name() const
{
	return("Help");
}