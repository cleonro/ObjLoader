#pragma once
#include "Utils/GLee.h"
#if WIN32
#include <windows.h>
#endif
#if __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
class OShader
{
public:
	OShader();
	~OShader();

	bool	LoadShaderString(const char* str, int type);	//type = 1, vertex shader
															//type = 2, fragment shader
	bool	LoadShaderFile(const char* filename, int type);
	char*	ShaderInfoLog(int type);
	char*	ProgramInfoLog();
	int		CompileStatus(int type);
	int		LinkStatus();

	void	CompileShader(int type);
	void	LoadShaders();
	void	Link();
	void	Use();

	bool	LoadSources(const char* str_vertex, const char* str_fragment);
	bool	LoadFileSources(const char* vertex_filename, const char* fragment_filename);
	void	BuildAll();

	GLint	UniformLocation(const char* location_name);

protected:
	char*	vertex_shader_s_;
	char*	fragment_shader_s_;
	GLuint	vertex_shader_;
	GLuint	fragment_shader_;
	GLuint	shader_;
};
