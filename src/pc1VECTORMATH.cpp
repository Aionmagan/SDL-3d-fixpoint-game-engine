#include "pc1VECTORMATH.h"

pc1VECTOR3::pc1VECTOR3(float x, float y, float z)
{
    this->x = ConvertToFix(x);
    this->y = ConvertToFix(y);
    this->z = ConvertToFix(z);
}

pc1VECTOR3::pc1VECTOR3()
{
    Zero();
}

pc1VECTOR3::~pc1VECTOR3()
{
    
}

void pc1VECTOR3::Zero()
{
    x = 0;
    y = 0;
    z = 0;
}

void pc1VECTOR3::SetPosition(float x, float y, float z)
{
    this->x = ConvertToFix((long)x);
    this->y = ConvertToFix((long)y);
    this->z = ConvertToFix((long)z);
}

void pc1VECTOR3::Normalize()
{
    float mag = Magnitude();
    x = x / mag;
    y = y / mag;
    z = z / mag;
}

float pc1VECTOR3::Magnitude() const
{
    return sqrt(x*x + y*y + z*z);
}

float pc1VECTOR3::SqrtMagnitude() const
{
    return (x*x + y*y + z*z);
}

float pc1VECTOR3::Distance(const pc1VECTOR3 &v) const
{
    return sqrt((v.x * x)+(v.y * y)+(v.z * z));
}

float pc1VECTOR3::DotProduct(const pc1VECTOR3 &v) const
{
    return (x * v.x + y * v.y + z * v.z);
}

pc1VECTOR3 pc1VECTOR3::CrossProduct(const pc1VECTOR3 &v) const
{
    return pc1VECTOR3((y*v.z) - (z*v.y),
                      (z*v.x) - (x*v.z),
                      (x*v.y) - (y*v.x));
}

void pc1VECTOR3::operator *=(const FixedPoint_t scaler)
{
    x *= scaler;
    y *= scaler;
    z *= scaler;
}

void pc1VECTOR3::operator /=(const FixedPoint_t scaler)
{
    x /= scaler;
    y /= scaler;
    z /= scaler;
}

void pc1VECTOR3::operator +=(const FixedPoint_t scaler)
{
    x += scaler;
    y += scaler;
    z += scaler;
}

void pc1VECTOR3::operator -=(const FixedPoint_t scaler)
{
    x -= scaler;
    y -= scaler;
    z -= scaler;
}

void pc1VECTOR3::operator *=(const pc1VECTOR3 &v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
}

void pc1VECTOR3::operator /=(const pc1VECTOR3 &v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
}

void pc1VECTOR3::operator +=(const pc1VECTOR3 &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

void pc1VECTOR3::operator -=(const pc1VECTOR3 &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}