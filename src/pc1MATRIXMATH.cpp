
#include <memory.h>
#include <math.h>
#include "pc1MATRIXMATH.h"

//Matrix 3x3 
pc1MATRIX3X3::pc1MATRIX3X3()
{
}

pc1MATRIX3X3::~pc1MATRIX3X3()
{
}

//Matrix 4x3
const static FixedPoint_t identityMatrix[4][3] =
    {
        ConvertToFix((long)1), 0L, 0L,
        0L, ConvertToFix((long)1), 0l,
        0L, 0L, ConvertToFix((long)1),
        0L, 0L, 0L
    };

//making traslation ro rotation 

//make translation
void pc1MATRIX4X3::MakeIdentity(void)
{
    memcpy(m, identityMatrix, sizeof(identityMatrix));
}

void pc1MATRIX4X3::MakeXTranslation(FixedPoint_t amount)
{
    m[3][0] = amount;
    m[3][1] = 0;
    m[3][2] = 0;
}

void pc1MATRIX4X3::MakeYTranslation(FixedPoint_t amount)
{
    m[3][0] = 0;
    m[3][1] = amount;
    m[3][2] = 0;
}

void pc1MATRIX4X3::MakeZTranslation(FixedPoint_t amount)
{
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = amount;
}

void pc1MATRIX4X3::MakeTranslation(const pc1VECTOR3 &v)
{
    m[3][0] = v.x;
    m[3][1] = v.y;
    m[3][2] = v.z;
}
//end make translation 

//make rotation
void pc1MATRIX4X3::MakeXRotation(unsigned short amount)
{
    m[1][1] = cos(amount);
    m[2][2] = cos(amount);
    m[2][1] = -sin(amount);
    m[1][2] = sin(amount);
}

void pc1MATRIX4X3::MakeYRotation(unsigned short amount)
{
    m[0][0] = cos(amount);
    m[0][2] = -sin(amount);
    m[2][0] = sin(amount);
    m[2][2] = cos(amount);
}

void pc1MATRIX4X3::MakeZRotation(unsigned short amount)
{
    m[0][0] = cos(amount);
    m[1][1] = cos(amount);
    m[0][1] = sin(amount);
    m[1][0] = -sin(amount);
}

void pc1MATRIX4X3::MakeRotation(const pc1VECTOR3 &v)
{
    MakeXRotation(v.x);
    MakeYRotation(v.y);
    MakeZRotation(v.z);
}
//make rotation end

void pc1MATRIX4X3::NormalizeDirectionVectors(void)
{
    pc1VECTOR3 v;
    
    //get up vector from rotation submatrix
    //normalize vector, put back in rotation submatrix
    GetVU(v);
    v.Normalize();
    SetVU(v);
    
    //get right vector from rotation submatrix 
    //normalize vector, put back in rotation submatrix 
    GetVR(v);
    v.Normalize();
    SetVR(v);
    
    //get forward vector from rotation submatrix 
    //normalize vector, put back in rotation submatrix
    GetVF(v);
    v.Normalize();
    SetVF(v);
}

void pc1MATRIX4X3::SetTranslation(FixedPoint_t x, FixedPoint_t y, FixedPoint_t z)
{
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
}

pc1VECTOR3 pc1MATRIX4X3::GetTranslation(void) const
{
    return pc1VECTOR3(m[3][0], m[3][1], m[3][3]);
}

void pc1MATRIX4X3::GetVU(pc1VECTOR3 &v) const
{
    v.x = m[0][1];
    v.y = m[1][1];
    v.z = m[2][1];
}

void pc1MATRIX4X3::GetVR(pc1VECTOR3 &v) const
{
    v.x = m[0][0];
    v.y = m[1][0];
    v.z = m[2][0];
}

void pc1MATRIX4X3::GetVF(pc1VECTOR3 &v) const
{
    v.x = m[0][2];
    v.y = m[1][2];
    v.z = m[2][2];
}

void pc1MATRIX4X3::SetVU(const pc1VECTOR3 &v)
{
    m[0][1] = v.x;
    m[1][1] = v.y;
    m[2][1] = v.z;
}

void pc1MATRIX4X3::SetVR(const pc1VECTOR3 &v)
{
    m[0][0] = v.x;
    m[1][0] = v.y;
    m[2][0] = v.z;
}

void pc1MATRIX4X3::SetVF(const pc1VECTOR3 &v)
{
    m[0][2] = v.x;
    m[1][2] = v.y;
    m[2][2] = v.z;
}

pc1VECTOR3 operator * (const pc1VECTOR3 &v, const pc1MATRIX3X3 &m)
{
    pc1VECTOR3 res;
    
    res.x = FixMultiply(m[0][0], v.x) + 
            FixMultiply(m[1][0], v.y) +
            FixMultiply(m[2][0], v.z);
            
    res.y = FixMultiply(m[0][1], v.x) + 
            FixMultiply(m[1][1], v.y) +
            FixMultiply(m[2][1], v.z);
            
    res.z = FixMultiply(m[0][2], v.x) + 
            FixMultiply(m[1][2], v.y) +
            FixMultiply(m[2][2], v.z);
            
    return res;
}

pc1VECTOR3 operator * (const pc1VECTOR3 &v, const pc1MATRIX4X3 &m)
{
    pc1VECTOR3 res;
    
    res.x = FixMultiply(m[0][0], v.x) + 
            FixMultiply(m[1][0], v.y) +
            FixMultiply(m[2][0], v.z) +
            m[3][0];
            
    res.y = FixMultiply(m[0][1], v.x) + 
            FixMultiply(m[1][1], v.y) +
            FixMultiply(m[2][1], v.z) +
            m[3][1];
            
    res.z = FixMultiply(m[0][2], v.x) + 
            FixMultiply(m[1][2], v.y) +
            FixMultiply(m[2][2], v.z) +
            m[3][2];
            
    return res;
}

pc1MATRIX4X3 operator * (const pc1MATRIX4X3 &a, const pc1MATRIX4X3 &b)
{
    static pc1MATRIX4X3 m;
    
    m[0][0] = FixMultiply(a[0][0], b[0][0]) + 
              FixMultiply(a[0][1], b[1][0]) +
              FixMultiply(a[0][2], b[2][0]);
            
    m[0][1] = FixMultiply(a[0][0], b[0][1]) + 
              FixMultiply(a[0][1], b[1][1]) +
              FixMultiply(a[0][2], b[2][1]);
              
    m[0][2] = FixMultiply(a[0][0], b[0][2]) + 
              FixMultiply(a[0][1], b[1][2]) +
              FixMultiply(a[0][2], b[2][2]);
              
    m[1][0] = FixMultiply(a[1][0], b[0][0]) + 
              FixMultiply(a[1][1], b[1][0]) +
              FixMultiply(a[1][2], b[2][0]);
              
    m[1][1] = FixMultiply(a[1][0], b[0][1]) + 
              FixMultiply(a[1][1], b[1][1]) +
              FixMultiply(a[1][2], b[2][1]);
              
    m[1][2] = FixMultiply(a[1][0], b[0][2]) + 
              FixMultiply(a[1][1], b[1][2]) +
              FixMultiply(a[1][2], b[2][2]);
    
    m[2][0] = FixMultiply(a[2][0], b[0][0]) + 
              FixMultiply(a[2][1], b[1][0]) +
              FixMultiply(a[2][2], b[2][0]);
              
    m[2][1] = FixMultiply(a[2][0], b[0][1]) + 
              FixMultiply(a[2][1], b[1][1]) +
              FixMultiply(a[2][2], b[2][1]);
              
    m[2][2] = FixMultiply(a[2][0], b[0][2]) + 
              FixMultiply(a[2][1], b[1][2]) +
              FixMultiply(a[2][2], b[2][2]);
              
    m[3][0] = FixMultiply(a[3][0], b[0][0]) + 
              FixMultiply(a[3][1], b[1][0]) +
              FixMultiply(a[3][2], b[2][0]) +
              b[3][0];
              
    m[3][1] = FixMultiply(a[3][0], b[0][1]) + 
              FixMultiply(a[3][1], b[1][1]) +
              FixMultiply(a[3][2], b[2][1]) +
              b[3][1];
              
    m[3][2] = FixMultiply(a[3][0], b[0][2]) + 
              FixMultiply(a[3][1], b[1][2]) +
              FixMultiply(a[3][2], b[2][2]) +
              b[3][2];
    /*          
    for(int i = 0; i < 3; ++i)
    {
        for(j = 0; j < 2; ++j)
        {
            m[i][j] = FixMultiply(a[i][0], b[0][j]) + 
                      FixMultiply(a[i][1], b[1][j]) +
                      FixMultiply(a[i][2], b[2][j]);
            if(i==3)
            m[i][j] += b[i][j];
        }
    }
     */   
    return m;
}