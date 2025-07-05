#pragma once

#ifdef SUPPORTING_PROJECT_EXPORTS
#define SUPPORTING_PROJECT_C_API extern "C" __declspec(dllexport)
#define SUPPORTING_PROJECT_EXPORT __declspec(dllexport)
#else
#define SUPPORTING_PROJECT_C_API extern "C" __declspec(dllimport)
#define SUPPORTING_PROJECT_EXPORT __declspec(dllimport)
#endif
