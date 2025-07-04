#pragma once
#include "config.h"

// DLL exports
SUPPORTING_PROJECT_API void bankingCommand(const char *command, char *response, const size_t responseLen);

// Typedefs
typedef char* bankingApiString;
typedef void (*bankingCommandFunction) (const bankingApiString, bankingApiString, const size_t);

