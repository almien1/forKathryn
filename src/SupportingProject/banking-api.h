#pragma once
#include "config.h"

// Typedefs
typedef char* bankingApiString;
typedef void (*bankingCommandFunction) (const bankingApiString, bankingApiString, const size_t);

// DLL exports
SUPPORTING_PROJECT_C_API void bankingCommand(const bankingApiString command, bankingApiString response, const size_t responseLen);


