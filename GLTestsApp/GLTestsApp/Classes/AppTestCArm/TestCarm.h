#ifndef TESTCARM_H
#define TESTCARM_H

#include "gltest.h"
#include "Math/Quaternion.h"

class OTestCArm
{
public:
    OTestCArm(float size);
    ~OTestCArm();

    void Draw();

    float& Angulation();
    float& Rotation();
    float& Dra();

    void ComputeQuat();

    OQuaternion Quat() {return quat_;}
    float Size() {return inner_ray_;}

protected:

    float inner_ray_;
    float outer_ray_;

    float angulation_;  //degrees
    float rotation_;    //degrees
    float dra_;         //degrees

    OSpecialMesh* inner_ring_;
    OSpecialMesh* outer_ring_;
    OSpecialMesh* rod_;

    OQuaternion  quat_;
};

#endif // TESTCARM_H
