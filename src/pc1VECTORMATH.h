#ifndef PC1VECTORMATH_H
#define PC1VECTORMATH_H

#include <cmath>
#include "pc1FIXPOINTMATH.h"

class pc1VECTOR3
{
public:
    FixedPoint_t x, y, z;

    pc1VECTOR3(float x, float y, float z);
    pc1VECTOR3();
    ~pc1VECTOR3();
    
    void Zero();
    void SetPosition(float x, float y , float z);
    
    void Normalize();
    float Magnitude() const;
    float SqrtMagnitude() const;
    float Distance(const pc1VECTOR3 &v) const;
    float DotProduct(const pc1VECTOR3 &v) const;
    pc1VECTOR3 CrossProduct(const pc1VECTOR3 &v)const;
    
    //vector to scaler math
    void operator *= (const FixedPoint_t scaler);
    void operator /= (const FixedPoint_t scaler);
    void operator += (const FixedPoint_t scaler);
    void operator -= (const FixedPoint_t scaler);
    
    //vector to vector math
    void operator *= (const pc1VECTOR3 &v);
    void operator /= (const pc1VECTOR3 &v);
    void operator += (const pc1VECTOR3 &v);
    void operator -= (const pc1VECTOR3 &v);
};

#endif // PC1VECTORMATH_H
