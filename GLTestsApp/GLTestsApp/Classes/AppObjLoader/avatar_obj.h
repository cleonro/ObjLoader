#ifndef AVATAR_OBJ_H
#define AVATAR_OBJ_H

#include "3d_model.h"
#include "vector3.h"
#include "matrix4.h"

#define PIVOT_NAME "avatar_pivot_point"
#define CARM_NAME "avatar_carm_mesh"

class C_AVATAR_OBJ : public C_3D_MODEL
{
public:
    C_AVATAR_OBJ();
    ~C_AVATAR_OBJ();

    C_MATRIX4& matrix() {return m_carm_orientation;}
    C_VECTOR3& pivot() {return m_carm_pivot;}

    void init();
    virtual void draw();

protected:

    void draw_carm();

    C_MATRIX4       m_carm_orientation;
    C_VECTOR3       m_carm_pivot;
    C_3D_OBJECT*    m_carm;
};

#endif // AVATAR_OBJ_H
