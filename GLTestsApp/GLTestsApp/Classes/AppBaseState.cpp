#include "AppTestShader/AppTestShader.h"
#include "AppBaseState.h"
//#include "Utils/draw_utils.h"
#include "gltest.h"
#include "AppTestCArm/AppTestCArm.h"

//AppBaseState
#include <string>
extern std::string AppResPath;

OAppBaseState::OAppBaseState()
{
	
}

OAppBaseState::~OAppBaseState()
{

}

OAppBaseState& OAppBaseState::GetInstance()
{
	static OAppBaseState base_state; 
	return base_state;
}

void* OAppBaseState::GetDataForInput()
{
	return (void*)(&camera_);
}

void OAppBaseState::Init(void *data) 
{
	float aspect = *(float*)data;
	camera_.SetPerspective(OVector4(1, 2048, 75, aspect));
	camera_.PlaceAt(OVector3(- 3 * 39, 1 * 50, 5 * 30 + 20));
	camera_.LookAt(OVector3(0, 0, 0));

    glUseProgram(0);

	//GenerateData();
}


void OAppBaseState::Update(void *data)
{
	camera_.SetGLModelViewMatrix();
}

void OAppBaseState::Update2(void* data)
{

}

//http://www.lighthouse3d.com/opengl/tutorials.shtml
void OAppBaseState::Draw()
{		
// 	char str[30];
// 	sprintf_s(str, 30, "Camera Roll %.2f", camera_.GetRoll());
// 	show_fps(1, 15, 150, 150, str);

	LightOn();
    DrawAxes(100.0f);
	glEnable(GL_NORMALIZE);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

    static OSpecialMesh mesh(100, 100, 50.0f, 5.0f);
    static std::string path = AppResPath + "Bifurcation 1 (ARO).txt";
    mesh.DrawMeshFromFile(path.c_str());
    //mesh.DrawMesh(OSpecialMesh::THORUS);
    //mesh.DrawMesh(OSpecialMesh::SPHERE);
    //mesh.DrawMesh(OSpecialMesh::CYLINDER);
    glDisableClientState(GL_COLOR_ARRAY);

	LightOff();
}

void OAppBaseState::LightOn()
{
	// Enable lighting, one light source, and color material
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHT1 );
	
	glEnable( GL_COLOR_MATERIAL );

	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	// Specify a white specular highlight
	const GLfloat ambient[4] = { 0.5f, 0.5f, 0.5f, 1.f };
	const GLfloat white[4] = { 0.8f, 0.8f, 0.8f, 1.f };
	const GLfloat pos[4] = { 0.f, 0.f, 170.0f, 1.0f };
	const GLfloat pos1[4] = { 0.f, 0.f, -70.0f, 0.0f };
	const GLfloat dir[3] = { 0.0f, 0.0f, -1.0f};
	const GLfloat dir1[3] = { 0.0f, 0.0f, 1.0f};
	const GLfloat cutoff = 85.0f;

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, true);

	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
	glLightfv( GL_LIGHT0, GL_POSITION, pos );
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
// 	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
// 	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	
	glLightfv( GL_LIGHT1, GL_POSITION, pos1 );
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir1);
// 	glLightfv(GL_LIGHT1, GL_AMBIENT, white);
// 	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, white );
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 85.f );
/*
	const GLfloat yell[] = {0.5f, 0.5f, 0.1f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yell);

	const GLfloat rd[] = {0.5f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rd);
*/
}

void OAppBaseState::LightOff()
{
	glDisable(GL_LIGHTING);
}


//AppManager
OAppManager::OAppManager()
{
        app_state_id_ = APP_NULL_STATE;
	app_state_ = NULL;
}

OAppManager::~OAppManager()
{
	app_state_id_ = -1;
	app_state_ = NULL;
}

void OAppManager::ChangeState(eAppStates state_id)
{
	switch(state_id){

        case APP_NULL_STATE:
            app_state_ = NULL;
            break;
		case APP_BASE_STATE :
			app_state_ = &(OAppBaseState::GetInstance());
			break;
        case APP_TEST_SHADER:
			app_state_ = &(OAppTestShader::GetInstance());
			break;
        case APP_TEST_C_ARM:
            app_state_ = &(OAppTestCArm::GetInstance());
            break;

		default:
			break;
	}

	app_state_id_ = state_id;
}

OAppBaseState* OAppManager::GetState()
{
	return app_state_;
}

OAppManager& OAppManager::GetInstance()
{
	static OAppManager instance;
	return instance;
}
