#include "3d_model.h"
#include "3d_resource_manager.h"
#include <math.h>

C_3D_MODEL::C_3D_MODEL()
{
    m_name = "";
    m_resource_manager = NULL;
}

C_3D_MODEL::~C_3D_MODEL()
{
    for(unsigned int i = 0; i < m_objects.size(); i++)
    {
        delete m_objects[i];
    }
    m_resource_manager->free_model(m_name);
}

void C_3D_MODEL::draw()
{
    for(unsigned int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->draw();
    }
}

void C_3D_MODEL::clone(C_3D_MODEL* model)
{
    m_resource_manager = model->m_resource_manager;
    m_name = model->m_name;
    m_objects.reserve(model->m_objects.size());
    for(unsigned int i = 0; i < model->m_objects.size(); i++)
    {
        m_objects.push_back(model->m_objects[i]->clone());
    }

    m_resource_manager->alloc_model(m_name);
}
