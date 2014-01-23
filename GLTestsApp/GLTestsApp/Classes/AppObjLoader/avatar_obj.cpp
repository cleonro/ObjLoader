#include "avatar_obj.h"
#include "quaternion.h"
#include "math_utils.h"
#include <windows.h>
#include <GL/gl.h>

C_AVATAR_OBJ::C_AVATAR_OBJ()
{
    C_QUATERNION q(0.0f, 0.0f, 0.0f, 1.0f);
    m_carm_orientation = q.to_matrix();
    m_carm_pivot = C_VECTOR3(0.0f, 0.0f, 0.0f);
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

    m_carm_pivot.x() = point.x;
    m_carm_pivot.y() = point.y;
    m_carm_pivot.z() = point.z;

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

    glTranslatef(m_carm_pivot.x(), m_carm_pivot.y(), m_carm_pivot.z());
    glMultMatrixf(m_carm_orientation.matrix_v());
    glTranslatef(-m_carm_pivot.x(), -m_carm_pivot.y(), -m_carm_pivot.z());

    m_carm->draw();

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
            glColor4f(0.35f, 0.35f, 0.95f, 1.0f);
            object->draw();
        }
    }
    if(m_carm != NULL)
    {
        glColor4f(0.9f, 0.9f, 0.7f, 0.95f);
        draw_carm();
    }
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}
