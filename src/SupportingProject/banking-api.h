#pragma once
#include "config.h"

// Typedefs
typedef wchar_t* BankingApiString;
typedef int MessageID;

// Function pointer typedefs
typedef MessageID              (*BankApiCommand)       (const BankingApiString);
typedef const BankingApiString (*BankApiGetMessage)    (const MessageID);
typedef void                   (*BankApiDeleteMessage) (const MessageID);

// DLL exports
SUPPORTING_PROJECT_C_API MessageID bankingCommand(const BankingApiString command);
SUPPORTING_PROJECT_C_API const BankingApiString getMessage(const MessageID messageID);
SUPPORTING_PROJECT_C_API void deleteMessage(const MessageID messageID);

// BankingCommand will return a message identifier.  
// Use getMessage to retrieve the text, copy it to a string variable, then call deleteMessage.
// Please call deleteMessage even if not using the text.
