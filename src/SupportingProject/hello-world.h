#pragma once
#include "config.h"

// DLL exports
SUPPORTING_PROJECT_API const wchar_t* helloWorldMessage();

// Typedefs for using the DLL
typedef const wchar_t* helloWorldFunctionReturn;
typedef helloWorldFunctionReturn(* helloWorldFunctionType) ();
