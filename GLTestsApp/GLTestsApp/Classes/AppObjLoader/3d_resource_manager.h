#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "3d_model.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

class C_3D_RESOURCE_MANAGER
{
public:
    struct T_MODEL_INF
    {
        T_MODEL_INF();
        unsigned int*                   indices;
        C_3D_MODEL::T_3D_MODEL_VERTEX*  vertices;
        vector<unsigned int>            object_start_indices;
        vector<string>                  object_names;
        unsigned int                    references;
        string                          name;
    };

    C_3D_RESOURCE_MANAGER();
    ~C_3D_RESOURCE_MANAGER();

    C_3D_MODEL* build_model(vector<unsigned int>& indices, vector<C_3D_MODEL::T_3D_MODEL_VERTEX>& vertices,
                            vector<unsigned int>& object_start_indices, vector<string>& object_names, string& model_name);

    void free_model(string name);
    void alloc_model(string name);

protected:

    map<string, T_MODEL_INF> m_models;
};

#endif // 3D_RESOURCE_MANAGER_H
