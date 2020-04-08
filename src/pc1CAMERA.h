#ifndef PC1CAMERA_H
#define PC1CAMERA_H
#include "pc1FIXPOINTMATH.h"
#include "pc1VECTORMATH.h"

class pc1CAMERA
{
private:
    FixedPoint_t vdf, hdf;
    int vfov, hfov; 
    int half_screen_w;
    int half_screen_h;
    
    void SetVFOV(unsigned angle, int vport_width);
    void SetHFOV(unsigned angle, int vport_width);
    
    inline int HProjection(FixedPoint_t value, FixedPoint_t z)const;
    inline int VProjection(FixedPoint_t value, FixedPoint_t z)const;
public:
    pc1CAMERA(unsigned fov);
    ~pc1CAMERA();
    
    void ProjectPoints(const pc1VECTOR3 *source, pc1VECTOR3 *dest, 
                       int num_vectices ) const;

};

#endif // PC1CAMERA_H
