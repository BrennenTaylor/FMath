#pragma once

#ifdef FMATH_EXPORT

#define FMATH_EXPORT extern "C" __declspec(dllexport)

#else

#define FMATH_EXPORT

#endif