#pragma once
#include "GLCamera.h"

class OGL3DShaderCamera : public OGL3DCamera
{
public:
    OGL3DShaderCamera();
    ~OGL3DShaderCamera();

    virtual void SetPerspective(OVector4);//the argument is Vector4(zNear, zFar, fovy, aspect)

protected:
	OMatrix4	projection_matrix_;
};
