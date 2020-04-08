#ifndef PC1MATRIXMATH_H
#define PC1MATRIXMATH_H

#include "pc1FIXPOINTMATH.h"
#include "pc1VECTORMATH.h"

class pc1MATRIX3X3
{
protected:
    FixedPoint_t m[3][3];
    
public:
    pc1MATRIX3X3();
    ~pc1MATRIX3X3();
    
    void Transpose(void);
    
    const FixedPoint_t * operator[] (int a) const
    {return m[a];}
    
    FixedPoint_t * operator[] (int a)
    {return m[a];}

};


//another class
class pc1MATRIX4X3
{
protected:
    FixedPoint_t m[4][3];
    
public:
    
     void MakeIdentity(void);
     
     void MakeXTranslation(FixedPoint_t amount);
     void MakeYTranslation(FixedPoint_t amount);
     void MakeZTranslation(FixedPoint_t amount);
     
     void MakeXRotation(unsigned short amount);
     void MakeYRotation(unsigned short amount);
     void MakeZRotation(unsigned short amount);
     
     void MakeTranslation(const pc1VECTOR3 &v);
     void MakeRotation(const pc1VECTOR3 &v);
     
     void NormalizeDirectionVectors(void);
     
     void GetRotationMatrix(pc1MATRIX3X3 &rm) const;
     void SetRotationMatrix(const pc1MATRIX3X3 &rm);
     void SetTranslation(FixedPoint_t x, FixedPoint_t y, FixedPoint_t z);
     void SetTranslation(pc1VECTOR3 &v)
     {SetTranslation(v.x, v.y, v.z);}
     
     pc1VECTOR3 GetTranslation(void) const;
     
     void GetVU(pc1VECTOR3 &v) const;
     void GetVR(pc1VECTOR3 &v) const;
     void GetVF(pc1VECTOR3 &v) const;
     
     void SetVU(const pc1VECTOR3 &v);
     void SetVR(const pc1VECTOR3 &v);
     void SetVF(const pc1VECTOR3 &v);
     
     const FixedPoint_t * operator[](int a) const {return m[a];}
     FixedPoint_t *operator[](int a) {return m[a];}
};

extern pc1VECTOR3 operator * (const pc1VECTOR3 &v, const pc1MATRIX3X3 &m);
extern pc1VECTOR3 operator * (const pc1VECTOR3 &v, const pc1MATRIX4X3 &m);
extern pc1MATRIX4X3 operator * (const pc1MATRIX4X3 &a, const pc1MATRIX4X3 &b);
#endif //PC1MATRIX4X3_H