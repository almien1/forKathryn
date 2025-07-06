#pragma once
#include "config.h"

// Typedefs
typedef char* bankingApiString;
typedef int MessageID;

// Function pointer typedefs
typedef MessageID              (*BankApiCommand)       (const bankingApiString);
typedef const bankingApiString (*BankApiGetMessage)    (const MessageID);
typedef void                   (*BankApiDeleteMessage) (const MessageID);

// DLL exports
SUPPORTING_PROJECT_C_API MessageID bankingCommand(const bankingApiString command);
SUPPORTING_PROJECT_C_API const bankingApiString getMessage(const MessageID messageID);
SUPPORTING_PROJECT_C_API void deleteMessage(const MessageID messageID);

// BankingCommand will return a message identifier.  
// Use getMessage to retrieve the text, copy it to a dynamic-length string variable,
// then call deleteMessage.  Please call deleteMessage even if not using the text.
