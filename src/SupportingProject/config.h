#pragma once

#ifdef SUPPORTING_PROJECT_EXPORTS
#define SUPPORTING_PROJECT_API __declspec(dllexport)
#define SUPPORTING_PROJECT_STATIC_API __declspec(dllexport)
#else
#define SUPPORTING_PROJECT_API __declspec(dllimport)
#define SUPPORTING_PROJECT_STATIC_API __declspec(dllimport)
#endif
