#include "GLShaderCamera.h"

OGL3DShaderCamera::OGL3DShaderCamera()
{

}

OGL3DShaderCamera::~OGL3DShaderCamera()
{

}

//the argument is Vector4(zNear, zFar, fovy, aspect)
void OGL3DShaderCamera::SetPerspective(OVector4 s)
{
        zNear_ = s[0];
        zFar_ = s[1];
        fovy_ = s[2];
        aspect_ = s[3];

        float t = zNear_ * tanf(deg2rad(fovy_ / 2));
        float b = -t;
        float r = aspect_ * t;
        float l = -r;

        float A = (r + l) / (r - l);
        float B = (t + b) / (t - b);
        float C = (zFar_ + zNear_) / (zFar_ - zNear_);
        float D = 2.0f * zFar_ * zNear_ / (zFar_ - zNear_);

        projection_matrix_.m00_ = 2.0f * zNear_ / (r - l);
        projection_matrix_.m01_ = 0.0f;
        projection_matrix_.m02_ = A;
        projection_matrix_.m03_ = 0.0f;

        projection_matrix_.m10_ = 0.0f;
        projection_matrix_.m11_ = 2.0f * zNear_ / (t - b);
        projection_matrix_.m12_ = B;
        projection_matrix_.m13_ = 0.0f;

        projection_matrix_.m20_ = 0.0f;
        projection_matrix_.m21_ = 0.0f;
        projection_matrix_.m22_ = C;
        projection_matrix_.m23_ = D;

        projection_matrix_.m30_ = 0.0f;
        projection_matrix_.m31_ = 0.0f;
        projection_matrix_.m32_ = -1.0f;
        projection_matrix_.m33_ = 0.0f;
}
