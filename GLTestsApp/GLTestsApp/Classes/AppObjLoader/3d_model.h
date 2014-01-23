#ifndef _MODEL_H
#define _MODEL_H

#include <vector>
#include <string>

using namespace std;

class C_3D_OBJECT;

class C_3D_MODEL
{
    friend class C_3D_RESOURCE_MANAGER;

public:
    struct T_3D_MODEL_VERTEX
    {
        //geometry coordinates
        float x;
        float y;
        float z;
        //normal components
        float nx;
        float ny;
        float nz;
    };

protected:
    class C_3D_OBJECT
    {
        friend class C_3D_RESOURCE_MANAGER;
        friend class C_3D_MODEL;

    public:
        void draw();

        const T_3D_MODEL_VERTEX* vertices() {return m_vertices;}
        const unsigned int* indices() {return m_indices;}
        const string& name() {return m_name;}

    protected:
        C_3D_OBJECT();
        ~C_3D_OBJECT();

        C_3D_OBJECT* clone();

        string                  m_name;
        unsigned int*           m_indices;
        T_3D_MODEL_VERTEX*      m_vertices;
        unsigned int            m_num_indices;

    };

public:


    C_3D_MODEL();
    ~C_3D_MODEL();

    virtual void draw();

    void clone(C_3D_MODEL* model);

protected:
    string                  m_name;
    vector<C_3D_OBJECT*>    m_objects;
    C_3D_RESOURCE_MANAGER*  m_resource_manager;
};

#endif // 3D_MODEL_H
