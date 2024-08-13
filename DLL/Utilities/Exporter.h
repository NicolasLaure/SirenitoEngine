#pragma once

#ifdef SIRENITO_EXPORT
#define SIRENITO_API __declspec(dllexport)
#else
#define SIRENITO_API __declspec(dllimport)
#endif
