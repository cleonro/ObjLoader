#include <QDebug>
#include "AppTestShader.h"


//shaders
const char* vertex_shader_s = "\
							  #version 140\n\
							  \
							  in vec4        MCvertex; \
							  in vec3        MCnormal; \
							  \
							  uniform mat4 MVMatrix; \
							  uniform mat4 MVPMatrix; \
							  uniform mat3 NormalMatrix; \
							  \
							  uniform vec3 LightPosition; \
							  \
							  const float SpecularContribution = 0.3; \
							  const float DiffuseContribution  = 1.0 - SpecularContribution; \
							  \
							  out float      LightIntensity; \
							  out vec2       MCposition; \
							  \
							  void main() \
							  { \
							  vec3 ecPosition = vec3(MVMatrix * MCvertex); \
							  vec3 tnorm        = normalize(gl_NormalMatrix * gl_Normal);/*normalize(NormalMatrix * MCnormal);*/ \
							  vec3 lightVec     = normalize(LightPosition - ecPosition); \
							  vec3 reflectVec = reflect(-lightVec, tnorm); \
							  vec3 viewVec      = normalize(-ecPosition); \
							  float diffuse     = max(dot(lightVec, tnorm), 0.0); \
							  float spec        = 0.0; \
							  \
							  if (diffuse > 0.0) \
							  { \
							  spec = max(dot(reflectVec, viewVec), 0.0); \
							  spec = pow(spec, 16.0); \
							  } \
							  \
							  LightIntensity    = DiffuseContribution * diffuse + \
							  SpecularContribution * spec; \
							  \
							  MCposition        = gl_Vertex.xy;/*MCvertex.xy;*/ \
							  gl_Position       = ftransform();/*MVPMatrix * MCvertex;*/ \
							  }\
							  ";


const char* fragment_shader_s = "\
								#version 140\n\
								\
								uniform vec3       BrickColor, MortarColor; \
								uniform vec2       BrickSize; \
								uniform vec2       BrickPct; \
								\
								in vec2            MCposition;\
								in float           LightIntensity; \
								\
								out vec4           FragColor; \
								\
								void main() \
								{ \
								vec3  color; \
								vec2  position, useBrick; \
								position = MCposition / BrickSize; \
								\
								if (fract(position.y * 0.5) > 0.5) \
								position.x += 0.5; \
								\
								position = fract(position);\
								\
								useBrick = step(position, BrickPct); \
								\
								color   = mix(MortarColor, BrickColor, useBrick.x * useBrick.y);\
								color *= LightIntensity; \
								FragColor = vec4(color, 1.0); \
								} \
								";


// const char* vertex_shader_s = "\
// 	uniform vec3 LightPosition;\
// 	const float SpecularContribution = 0.3;\
// 	const float DiffuseContribution  = 1.0 - SpecularContribution;\
// 	\
// 	varying float LightIntensity;\
// 	varying vec2  MCposition;\
// 	\
// 	void main()\
// 	{\
// 		vec3 ecPosition = vec3(gl_ModelViewMatrix * gl_Vertex);\
// 		vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal);\
// 		vec3 lightVec   = normalize(LightPosition - ecPosition);\
// 		vec3 reflectVec = reflect(-lightVec, tnorm);\
// 		vec3 viewVec    = normalize(-ecPosition);\
// 		float diffuse   = max(dot(lightVec, tnorm), 0.0);\
// 		float spec      = 0.0;\
// 		\
// 		if (diffuse > 0.0)\
// 		{\
// 			spec = max(dot(reflectVec, viewVec), 0.0);\
// 			spec = pow(spec, 16.0);\
// 		}\
// 		\
// 		LightIntensity = DiffuseContribution * diffuse + SpecularContribution * spec;\
// 		\
// 		MCposition     = gl_Vertex.xy;\
// 		gl_Position    = ftransform();\
// 		\
// 	}";



// const char* fragment_shader_s = "\
// 	uniform vec3  BrickColor, MortarColor;\
// 	uniform vec2  BrickSize;\
// 	uniform vec2  BrickPct;\
// 	\
// 	varying vec2  MCposition;\
// 	varying float LightIntensity;\
// 	\
// 	void main()\
// 	{\
// 		vec3  color;\
// 		vec2  position, useBrick;\
// 		position = MCposition / BrickSize;\
// 	\
// 		if (fract(position.y * 0.5) > 0.5)\
// 			position.x += 0.5;\
// 			\
// 		position = fract(position);\
// 		\
// 		useBrick = step(position, BrickPct);\
// 	\
// 		color  = mix(MortarColor, BrickColor, useBrick.x * useBrick.y);\
// 		color *= LightIntensity;\
// 		gl_FragColor = vec4(color, 1.0);\
// 	}";

// const char* vertex_shader_s = "\
// 	  varying vec4 PointColor;\
// 	  void main()\
// 	  {\
// 		  gl_Position = ftransform();\
// 	  }\
//  	";
//  
// const char* fragment_shader_s = "\
// 	void main()\
// 	{\
// 		gl_FragColor = gl_Color;\
// 	}\
//  	";


OAppTestShader::OAppTestShader()
{

}


OAppTestShader::~OAppTestShader()
{

}

OAppTestShader& OAppTestShader::GetInstance()
{
	static OAppTestShader instance;
	return instance;
};

void* OAppTestShader::GetDataForInput()
{
	return (void*)(&camera_);
}

void OAppTestShader::InitShader()
{
	//shader_.LoadSources(vertex_shader_s, fragment_shader_s);
	shader_.LoadFileSources("vertex_shader.shd", "fragment_shader.shd");
	shader_.BuildAll();
	char* vertex_log = shader_.ShaderInfoLog(1);
	char* fragment_log = shader_.ShaderInfoLog(2);
	char* program_log = shader_.ProgramInfoLog();
	qDebug()<<vertex_log;
	qDebug()<<fragment_log;
	qDebug()<<program_log;

	delete [] vertex_log;
	delete [] fragment_log;
	delete [] program_log;

	shader_.Use();
	GLint light_position = shader_.UniformLocation("LightPosition");
	GLint brick_color = shader_.UniformLocation("BrickColor");
	GLint mortar_color = shader_.UniformLocation("MortarColor");

	GLint brick_size = shader_.UniformLocation("BrickSize");
	GLint brick_pct = shader_.UniformLocation("BrickPct");

	float light_position_v [] = {0.0, 0.0, 4.0};
	float brick_color_v [] = {1.0, 0.3, 0.2};
	float mortar_color_v [] = {0.85, 0.86, 0.84};

	float brick_size_v [] = {0.3, 0.15};
	float brick_pct_v [] = {0.90, 0.85};

	glUniform3f(light_position, 0.0, 0.0, 4.0);
	glUniform3f(brick_color, 1.0, 0.3, 0.2);
	glUniform3f(mortar_color, 0.85, 0.86, 0.84);

	glUniform2f(brick_size, 0.3, 0.15);
	glUniform2f(brick_pct, 0.90, 0.85);
	glUseProgram(0);
}

void OAppTestShader::Init(void* data)
{
	const GLubyte* version = glGetString(GL_VERSION);
	qDebug()<<(const char*)version;
	
	version = glGetString(GL_SHADING_LANGUAGE_VERSION);
	qDebug()<<(const char*)version;

	OAppBaseState::Init(data);
	InitShader();
}

void OAppTestShader::Update(void* data)
{
	OAppBaseState::Update(data);
}

void OAppTestShader::Update2(void* data)
{
	OAppBaseState::Update2(data);
}

void OAppTestShader::Draw()
{
	glUseProgram(0);
	VDraws->DrawAxes(30.0f, 1.0f);
	shader_.Use();
	VDraws->DrawHorizontalQuad(20, 20);
}
