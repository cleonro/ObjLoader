#include "3d_dynamic_object.h"
#include "Math/Quaternion.h"
#include "gltest.h"

#ifdef WIN32
#include <windows.h>
#endif
#if __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


C_3D_DYNAMIC_OBJECT::C_3D_DYNAMIC_OBJECT()
{
    OQuaternion q(0.0f, 0.0f, 0.0f, 1.0f);
    rotation_ = q.ToMatrix();
    position_ = OVector3(0.0f, 0.0f, 0.0f);
}

C_3D_DYNAMIC_OBJECT::~C_3D_DYNAMIC_OBJECT()
{

}

void C_3D_DYNAMIC_OBJECT::draw(bool draw_axes)
{
    glPushMatrix();

    glTranslatef(position_.X(), position_.Y(), position_.Z());
    glMultMatrixf(rotation_.GetSafeM());
    C_3D_MODEL::draw();

    if(draw_axes) {
        DrawAxes(10.0f);
    }

    glPopMatrix();
}
