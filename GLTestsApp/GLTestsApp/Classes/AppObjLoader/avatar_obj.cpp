#include "avatar_obj.h"
#include "Math/Quaternion.h"
#include "Utils/math_utils.h"
#include "VariousObjects.h"

#include <windows.h>
#include <GL/gl.h>

C_AVATAR_OBJ::C_AVATAR_OBJ()
{
    OQuaternion q(0.0f, 0.0f, 0.0f, 1.0f);
    m_carm_orientation = q.ToMatrix();
    m_carm_pivot = OVector3(0.0f, 0.0f, 0.0f);
    m_carm = NULL;
}

C_AVATAR_OBJ::~C_AVATAR_OBJ()
{

}

void C_AVATAR_OBJ::init()
{
    m_carm = NULL;
    C_3D_OBJECT* pivot = NULL;
    for(unsigned int i = 0; i < m_objects.size(); i++)
    {
        if(m_objects[i]->name() == PIVOT_NAME)
        {
            pivot = m_objects[i];
        }
        if(m_objects[i]->name() == CARM_NAME)
        {
            m_carm = m_objects[i];
        }
    }
    if(pivot == NULL)
    {
        return;
    }

    const unsigned int* indices = pivot->indices();
    const C_3D_MODEL::T_3D_MODEL_VERTEX* vertices = pivot->vertices();
    C_3D_MODEL::T_3D_MODEL_VERTEX point = vertices[indices[0]];

    m_carm_pivot.X() = point.x;
    m_carm_pivot.Y() = point.y;
    m_carm_pivot.Z() = point.z;

    //test-remove
    //float hsin = sinf(0.5f * deg2rad(45.0f));
    //float hcos = cosf(0.5f * deg2rad(45.0f));
    //C_QUATERNION q(0, hsin, 0, hcos);
    //m_carm_orientation = q.to_matrix();
    //
}

void C_AVATAR_OBJ::draw_carm()
{
    glPushMatrix();

    glTranslatef(m_carm_pivot.X(), m_carm_pivot.Y(), m_carm_pivot.Z());
    glMultMatrixf(m_carm_orientation.GetSafeM());
    glTranslatef(-m_carm_pivot.X(), -m_carm_pivot.Y(), -m_carm_pivot.Z());

    m_carm->draw();
    //VDraws->DrawAxes(50.0, 1.0);

    glPopMatrix();
}

void C_AVATAR_OBJ::draw()
{
    C_3D_OBJECT* object;
    for(unsigned int i = 0; i < m_objects.size(); i++)
    {
        object = m_objects[i];
        if(object != m_carm && object->name() != PIVOT_NAME)
        {
            object->draw();
        }
        else if(object == m_carm)
        {
            draw_carm();
        }
    }
}
