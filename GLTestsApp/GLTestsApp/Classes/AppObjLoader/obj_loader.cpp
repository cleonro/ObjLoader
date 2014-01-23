#include "obj_loader.h"
#include "3d_resource_manager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

C_OBJ_LOADER::C_OBJ_LOADER()
{
    m_geometry_type = GEOMETRY_NOT_DEFINED;
    m_line_counter = 0;
    m_vertices_counter = 0;

     m_line_parsers["o"] = &C_OBJ_LOADER::o_line;
    m_line_parsers["v"] = &C_OBJ_LOADER::v_line;
    m_line_parsers["vn"] = &C_OBJ_LOADER::vn_line;
    m_line_parsers["f"] = &C_OBJ_LOADER::f_line;
}

C_OBJ_LOADER::~C_OBJ_LOADER()
{

}

void C_OBJ_LOADER::clear()
{
    m_vertices_counter = 0;
    m_line_counter = 0;

    m_xyz_buffer.clear();
    m_n_xyz_buffer.clear();

    m_f_tokens_map.clear();

    m_errors.clear();

    m_output_indices.clear();
    m_output_vertices.clear();
    m_output_object_starts.clear();
    m_output_object_names.clear();
}

void C_OBJ_LOADER::o_line(vector<string> tokens)
{
    string name = "unknown";
    if(tokens.size() > 1)
    {
        name = tokens[1];
    }

    //m_output_object_starts.push_back(m_indices_counter);
    m_output_object_starts.push_back(m_output_indices.size());
    m_output_object_names.push_back(name);
}

void C_OBJ_LOADER::v_line(vector<string> tokens)
{
    if(tokens.size() < 4)
    {
        T_OBJ_PARSER_ERROR error;
        error.error_message = "Not enough coordinates on this line. Line ignored...";
        error.line = m_line_counter;
        m_errors.push_back(error);
        return;
    }
    float x;
    int ix = sscanf_s(tokens[1].c_str(), "%f", &x);
    float y;
    int iy = sscanf_s(tokens[2].c_str(), "%f", &y);
    float z;
    int iz = sscanf_s(tokens[3].c_str(), "%f", &z);

    if(ix <= 0 || iy <= 0 || iz <= 0)
    {
        T_OBJ_PARSER_ERROR error;
        error.error_message = "Invalid strings on this line. Line ignored...";
        error.line = m_line_counter;
        m_errors.push_back(error);
        return;
    }

    m_xyz_buffer.push_back(x);
    m_xyz_buffer.push_back(y);
    m_xyz_buffer.push_back(z);
}

void C_OBJ_LOADER::vn_line(vector<string> tokens)
{
    if(tokens.size() < 4)
    {
        T_OBJ_PARSER_ERROR error;
        error.error_message = "Not enough normal coordinates on this line. Line ignored...";
        error.line = m_line_counter;
        m_errors.push_back(error);
        return;
    }
    float nx;
    int inx = sscanf_s(tokens[1].c_str(), "%f", &nx);
    float ny;
    int iny = sscanf_s(tokens[2].c_str(), "%f", &ny);
    float nz;
    int inz = sscanf_s(tokens[3].c_str(), "%f", &nz);

    if(inx <= 0 || iny <= 0 || inz <= 0)
    {
        T_OBJ_PARSER_ERROR error;
        error.error_message = "Invalid strings on this line. Line ignored...";
        error.line = m_line_counter;
        m_errors.push_back(error);
        return;
    }

    m_n_xyz_buffer.push_back(nx);
    m_n_xyz_buffer.push_back(ny);
    m_n_xyz_buffer.push_back(nz);
}

void C_OBJ_LOADER::f_line(vector<string> tokens)
{
    if(tokens.size() < 4)
    {
        T_OBJ_PARSER_ERROR error;
        error.error_message = "A face must have at least 3 vertices. Line ignored...";
        error.line = m_line_counter;
        m_errors.push_back(error);
        return;
    }

    for(unsigned int i = 1; i < 4; i++)
    {
        istringstream str_stream(tokens[i]);
        vector<string> elem_tokens;
        string tkn;

        while(!str_stream.eof())
        {
            getline(str_stream, tkn, '/');
            elem_tokens.push_back(tkn);
        }
        int sz = elem_tokens.size();

        map<string, unsigned int>::iterator it =  m_f_tokens_map.find(tokens[i]);
        if(it == m_f_tokens_map.end())
        {
            //add new pair in f_tokens map (and new vertex in output_vertices)

            //new vertex
            C_3D_MODEL::T_3D_MODEL_VERTEX vertex;

            int idx_coords = 3 * (atoi(elem_tokens[0].c_str()) - 1);
            vertex.x = m_xyz_buffer[idx_coords];
            vertex.y = m_xyz_buffer[idx_coords + 1];
            vertex.z = m_xyz_buffer[idx_coords + 2];
            if(sz == 3)
            {
                int idx_normal = 3 * (atoi(elem_tokens[2].c_str()) - 1);
                vertex.nx = m_n_xyz_buffer[idx_normal];
                vertex.ny = m_n_xyz_buffer[idx_normal + 1];
                vertex.nz = m_n_xyz_buffer[idx_normal + 2];
            }
            //vertex.normalize();
            m_output_vertices.push_back(vertex);
            m_output_indices.push_back(m_vertices_counter);

            m_f_tokens_map[tokens[i]] = m_vertices_counter;
            m_vertices_counter++;
        }
        else
        {

            m_output_indices.push_back(it->second);

        }
    }
}

void C_OBJ_LOADER::parse_line(string& line)
{
    //model must not be a null pointer
    vector<string> tokens;
    string tkn;
    istringstream str_stream(line);

    while(!str_stream.eof())
    {
        getline(str_stream, tkn, ' ');
        if(tkn != "")
        {
            tokens.push_back(tkn);
        }
    }

    if(tokens.size() == 0)
    {
        return;
    }

    map<string, LINE_PARSER_FUNCTION>::iterator it = m_line_parsers.find(tokens[0]);
    if(it == m_line_parsers.end())
    {
        T_OBJ_PARSER_ERROR error;
        error.error_message = "No parser found for this line. Line ignored...";
        error.line = m_line_counter;
        m_errors.push_back(error);
        return;
    }

    LINE_PARSER_FUNCTION line_parser = it->second;
    (this->*line_parser)(tokens);

}

C_3D_MODEL* C_OBJ_LOADER::parse_obj_file(const char* file_name, C_3D_RESOURCE_MANAGER* resource_manager, string model_name)
{

    C_3D_MODEL* model = NULL;

    ifstream file_stream(file_name);
    if(!file_stream.is_open())
    {
        //file couldn't be open
        return model;
    }

    string line;
    while(!file_stream.eof())
    {
        getline(file_stream, line);
        m_line_counter++;
        if(line.size() == 0)
        {
            //empty line
            continue;
        }
        if(line[0] == '#')
        {
            //comment line
            continue;
        }
        parse_line(line);
    }

    file_stream.close();

    model = resource_manager->build_model(m_output_indices, m_output_vertices,
                                          m_output_object_starts, m_output_object_names, model_name);

    clear();

    return model;
}
