#ifndef AVATAR_OBJ_H
#define AVATAR_OBJ_H

#include "3d_model.h"
#include "Math/Vector3.h"
#include "Math/Matrix4x4.h"

#define PIVOT_NAME "avatar_pivot_point"
#define CARM_NAME "avatar_carm_mesh"

class C_AVATAR_OBJ : public C_3D_MODEL
{
public:
    C_AVATAR_OBJ();
    virtual ~C_AVATAR_OBJ();

    OMatrix4& matrix() {return m_carm_orientation;}
    OVector3& pivot() {return m_carm_pivot;}

    void init();
    virtual void draw();

protected:

    void draw_carm();

    OMatrix4       m_carm_orientation;
    OVector3       m_carm_pivot;
    C_3D_OBJECT*    m_carm;
};

#endif // AVATAR_OBJ_H
