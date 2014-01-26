#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include "3d_model.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector3.h"

class C_3D_DYNAMIC_OBJECT : public C_3D_MODEL
{
public:
    C_3D_DYNAMIC_OBJECT();
    ~C_3D_DYNAMIC_OBJECT();

    OVector3& Position() {return position_;}
    OMatrix4& Rotation() {return rotation_;}

    virtual void draw(bool draw_axes = false);

protected:
    OVector3    position_;
    OMatrix4    rotation_;
};

#endif // 3D_DYNAMIC_OBJECT_H
