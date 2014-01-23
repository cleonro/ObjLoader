#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include "3d_model.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class C_3D_RESOURCE_MANAGER;

class C_OBJ_LOADER
{
    typedef void (C_OBJ_LOADER::*LINE_PARSER_FUNCTION)(vector<string> tokens);

    enum E_GEOMETRY_TYPE
    {
        GEOMETRY_NOT_DEFINED = 0,
        COORDS,
        COORDS_TEXCOORDS,
        COORDS_NORMALS,
        COORDS_TEXCOORDS_NORMALS
    };

public:

    struct T_OBJ_PARSER_ERROR
    {
        unsigned    int line;
        std::string error_message;
    };

    C_OBJ_LOADER();
    ~C_OBJ_LOADER();

    C_3D_MODEL* parse_obj_file(const char* file_name, C_3D_RESOURCE_MANAGER* resource_manager, string model_name);

protected:

    void parse_line(string& line);

    void o_line(vector<string> tokens);
    void v_line(vector<string> tokens);
    void vn_line(vector<string> tokens);
    void f_line(vector<string> tokens);

    void clear();

    map<string, LINE_PARSER_FUNCTION> m_line_parsers;

    //model geometry type
    E_GEOMETRY_TYPE m_geometry_type;

    //parser buffers
    vector<float> m_xyz_buffer;
    vector<float> m_n_xyz_buffer;
    map<string, unsigned int> m_f_tokens_map;

    unsigned int m_line_counter;
    unsigned int m_vertices_counter;
    vector<T_OBJ_PARSER_ERROR> m_errors;

    //parser output
    vector<unsigned int> m_output_indices; //model triangles vertex indices
    vector<C_3D_MODEL::T_3D_MODEL_VERTEX> m_output_vertices; //model triangles indices
    vector<unsigned int> m_output_object_starts; //model objects start points in indices vector
    vector<string> m_output_object_names; //model objects names


};

#endif // OBJ_LOADER_H
