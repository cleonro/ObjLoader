#include "3d_resource_manager.h"

C_3D_RESOURCE_MANAGER::T_MODEL_INF::T_MODEL_INF()
{
    indices = NULL;
    vertices = NULL;
    references = 0;
}

C_3D_RESOURCE_MANAGER::C_3D_RESOURCE_MANAGER()
{

}

C_3D_RESOURCE_MANAGER::~C_3D_RESOURCE_MANAGER()
{
    for(map<string, T_MODEL_INF>::iterator it = m_models.begin(); it != m_models.end(); it++)
    {
        T_MODEL_INF model_inf = it->second;
        delete [] model_inf.indices;
        delete [] model_inf.vertices;
    }
}

C_3D_MODEL* C_3D_RESOURCE_MANAGER::build_model(vector<unsigned int>& indices, vector<C_3D_MODEL::T_3D_MODEL_VERTEX>& vertices,
                        vector<unsigned int>& object_start_indices, vector<string>& object_names, string& model_name)
{
    T_MODEL_INF model_inf;
    model_inf.name = model_name;
    model_inf.references = 1;

    model_inf.vertices = new C_3D_MODEL::T_3D_MODEL_VERTEX[vertices.size()];
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        model_inf.vertices[i] = vertices[i];
    }

    model_inf.indices = new unsigned int[indices.size()];
    for(unsigned int i = 0; i < indices.size(); i++)
    {
        model_inf.indices[i] = indices[i];
    }

    model_inf.object_start_indices.reserve(object_start_indices.size());
    for(unsigned int i = 0; i < object_start_indices.size(); i++)
    {
        model_inf.object_start_indices.push_back(object_start_indices[i]);
    }

    model_inf.object_names.reserve(object_names.size());
    for(unsigned int i = 0; i < object_names.size(); i++)
    {
        model_inf.object_names.push_back(object_names[i]);
    }

    C_3D_MODEL* model = new C_3D_MODEL;
    model->m_name = model_name;
    model->m_resource_manager = this;
    model->m_objects.reserve(object_names.size());

    m_models[model_name] = model_inf;

    model->m_objects.reserve(object_names.size());
    for(unsigned int i = 0; i < object_names.size(); i++)
    {
        C_3D_MODEL::C_3D_OBJECT* object = new C_3D_MODEL::C_3D_OBJECT;
        object->m_indices = model_inf.indices + object_start_indices[i];
        object->m_vertices = model_inf.vertices;
        object->m_name = object_names[i];
        if(i != object_names.size() - 1)
        {
            object->m_num_indices = object_start_indices[i + 1] - object_start_indices[i];
        }
        else
        {
           object->m_num_indices = indices.size() - object_start_indices[i];
        }
        model->m_objects.push_back(object);
    }

    return model;
}

void C_3D_RESOURCE_MANAGER::free_model(string name)
{
    map<string, T_MODEL_INF>::iterator it = m_models.find(name);
    if(it == m_models.end())
    {
        return;
    }

    T_MODEL_INF model_inf = it->second;
    model_inf.references--;
    if(model_inf.references == 0)
    {
        delete [] model_inf.indices;
        delete [] model_inf.vertices;
        m_models.erase(it);
    }
    else
    {
        m_models[name] = model_inf;
    }
}

void C_3D_RESOURCE_MANAGER::alloc_model(string name)
{
     map<string, T_MODEL_INF>::iterator it = m_models.find(name);
     if(it == m_models.end())
     {
         return;
     }

     it->second.references++;
}
