#pragma once

#ifdef SUPPORTING_PROJECT_EXPORTS
#define SUPPORTING_PROJECT_API extern "C" __declspec(dllexport)
#define SUPPORTING_PROJECT_STATIC_API extern "C" __declspec(dllexport)
#else
#define SUPPORTING_PROJECT_API extern "C" __declspec(dllimport)
#define SUPPORTING_PROJECT_STATIC_API extern "C" __declspec(dllimport)
#endif
