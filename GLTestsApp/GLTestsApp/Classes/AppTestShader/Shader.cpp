#include "Shader.h"
#include <string.h>
#include <stdio.h>
#include <fstream>

OShader::OShader()
{
	vertex_shader_s_ = NULL;
	fragment_shader_s_ = NULL;

	vertex_shader_ = 0;
	fragment_shader_ = 0;
	shader_ = 0;
}

OShader::~OShader()
{
	delete [] vertex_shader_s_;
	delete [] fragment_shader_s_;
}

bool OShader::LoadShaderString(const char* str, int type)
{
	char** shader_s;
	switch(type) {
		case 1:
			shader_s = &vertex_shader_s_;
			break;
		case 2:
			shader_s = &fragment_shader_s_;
			break;
		default:
			break;
	}

	delete [] *shader_s;
	*shader_s = NULL;
	int l = strlen(str);
	if(l == 0) {
		return false;
	}
	*shader_s = new char[l + 1];
        strncpy(*shader_s, str, l);

	return true;
}

bool OShader::LoadShaderFile(const char* filename, int type)
{
	char** shader_s;
	switch(type) {
		case 1:
			shader_s = &vertex_shader_s_;
			break;
		case 2:
			shader_s = &fragment_shader_s_;
			break;
		default:
			break;
	}

	delete [] *shader_s;
	*shader_s = NULL;

    std::fstream f(filename, std::ios::in);
    if(!f.is_open())
    {
        return false;
    }
    int sz = 0;
    f.seekg(0, f.end);
    sz = f.tellg();
    f.seekg(0, f.beg);
    *shader_s = new char[sz + 1];
    f.read(*shader_s, sz);
    (*shader_s)[sz] = 0;
    f.close();

	return true;
}

char* OShader::ShaderInfoLog(int type)
{
	GLuint	shader = 0;
	int     infolog_length = 0;
	int     chars_written  = 0;
	char	*infolog = NULL;

	switch(type) {
		case 1:
			shader = vertex_shader_;
			break;
		case 2:
			shader = fragment_shader_;
			break;
		default:
			break;
	}

	glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infolog_length);

	if (infolog_length > 0) {
		infolog = new  char[infolog_length + 1];
		glGetShaderInfoLog (shader, infolog_length, &chars_written, infolog);
	}

	return infolog;
}

char* OShader::ProgramInfoLog()
{
	int     infolog_length = 0;
	int     chars_written  = 0;
	char	*infolog = NULL;

	glGetProgramiv (shader_, GL_INFO_LOG_LENGTH, &infolog_length);

	if (infolog_length > 0) {
		infolog = new  char[infolog_length + 1];
		glGetProgramInfoLog (shader_, infolog_length, &chars_written, infolog);
	}

	return infolog;
}

int OShader::CompileStatus(int type)
{
	int status = GL_TRUE;
	GLuint shader = 0;
	switch(type) {
		case 1:
			shader = vertex_shader_;
			break;
		case 2:
			shader = fragment_shader_;
			break;
		default:
			break;
	}
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	return status;
}

int OShader::LinkStatus()
{
	int status = GL_TRUE;
	glGetProgramiv(shader_, GL_LINK_STATUS, &status);
	return status;
}

void OShader::CompileShader(int type)
{
	GLuint* shader = NULL;
	const char* source = NULL;
	GLenum st = 0;
	switch(type) {
		case 1:
			shader = &vertex_shader_;
			source = vertex_shader_s_;
			st = GL_VERTEX_SHADER;
			break;
		case 2:
			shader = &fragment_shader_;
			source = fragment_shader_s_;
			st = GL_FRAGMENT_SHADER;
			break;
		default:
			break;
	}
	if(shader == NULL) {
		return;
	}
	*shader = glCreateShader(st);
	glShaderSource(*shader, 1, &source, NULL);
	glCompileShader(*shader);
}

void OShader::LoadShaders()
{
	shader_ = glCreateProgram();

	glAttachShader(shader_, vertex_shader_);
	glAttachShader(shader_, fragment_shader_);
}

void OShader::Link()
{
	glLinkProgram(shader_);
}

void OShader::Use()
{
	glUseProgram(shader_);
}

bool OShader::LoadSources(const char* str_vertex, const char* str_fragment)
{
	bool r1 = LoadShaderString(str_vertex, 1);
	bool r2 = LoadShaderString(str_fragment, 2);
	return r1 && r2;
}

bool OShader::LoadFileSources(const char* vertex_filename, const char* fragment_filename)
{
	bool r1 = LoadShaderFile(vertex_filename, 1);
	bool r2 = LoadShaderFile(fragment_filename, 2);
	return r1 && r2;
}

void OShader::BuildAll()
{
	CompileShader(1);
	CompileShader(2);
	LoadShaders();
	Link();
}

GLint OShader::UniformLocation(const char* location_name)
{
	GLint location = glGetUniformLocation(shader_, location_name);
	return location;
}
