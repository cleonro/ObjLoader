#ifndef _OBJECT_H
#define _OBJECT_H

#include <string>

using namespace std;

class C_3D_OBJECT
{
    friend class C_3D_RESOURCE_MANAGER;
public:

    struct T_3D_MODEL_VERTEX
    {
        T_3D_MODEL_VERTEX();
        void normalize();
        //geometry coordinates
        float x;
        float y;
        float z;
        //normal components
        float nx;
        float ny;
        float nz;
        //texture_1 coordinates
        float u;
        float v;
    };

    C_3D_OBJECT();
    ~C_3D_OBJECT();

    void draw();

protected:
    string                  m_name;
    unsigned int*           m_indices;
    T_3D_MODEL_VERTEX*      m_vertices;
    unsigned int            m_num_indices;

};

#endif // 3D_OBJECT_H
