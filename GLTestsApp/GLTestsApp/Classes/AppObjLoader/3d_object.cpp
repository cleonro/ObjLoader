#include "3d_model.h"
#ifdef WIN32
#include <windows.h>
#endif
#if __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


C_3D_MODEL::C_3D_OBJECT::C_3D_OBJECT()
{
    m_name = "";
    m_num_indices = 0;
    m_indices = NULL;
    m_vertices = NULL;
}

C_3D_MODEL::C_3D_OBJECT::~C_3D_OBJECT()
{

}

void C_3D_MODEL::C_3D_OBJECT::draw()
{
    glVertexPointer(3, GL_FLOAT, sizeof(T_3D_MODEL_VERTEX), &m_vertices[0].x);
    glDisableClientState(GL_COLOR_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(T_3D_MODEL_VERTEX), &m_vertices[0].nx);

    glDrawElements(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_INT, m_indices);
}

C_3D_MODEL::C_3D_OBJECT* C_3D_MODEL::C_3D_OBJECT::clone()
{
    C_3D_OBJECT* object = new C_3D_OBJECT;

    object->m_vertices = m_vertices;
    object->m_indices = m_indices;
    object->m_num_indices = m_num_indices;
    object->m_name = m_name;

    return object;
}
