#ifndef PC1FIXPOINTMATH_H
#define PC1FIXPOINTMATH_H

#define _FloatScaler 65536.0
#define _FixShift 16

#include <SDL.h>

typedef int32_t FixedPoint_t;

inline FixedPoint_t ConvertToFix(const double a)
{
    return (FixedPoint_t) (a * _FloatScaler);
}

inline FixedPoint_t ConvertToFix(const float a)
{
    return (FixedPoint_t) (a * _FloatScaler);
}

inline FixedPoint_t ConvertToFix(const long a)
{
    return (FixedPoint_t) (a << _FixShift);
}

inline FixedPoint_t ConvertToFix(const int a)
{
    return (FixedPoint_t) (((long)a) << _FixShift);
}

inline FixedPoint_t  FixMultiply(FixedPoint_t a, FixedPoint_t b)
{
    return ((int64_t)a * (int64_t)b) / (1 << _FixShift);
}

inline FixedPoint_t FixDivition(FixedPoint_t a, FixedPoint_t b)
{
    return ((int64_t)a * (1 << _FixShift)) / b;
}

inline float ConvertToFloat(const FixedPoint_t a)
{
    return ((a)/_FloatScaler);
}

inline int ConvertToInt(const FixedPoint_t a)
{
    return (int)((a) >> _FixShift);
}

#endif