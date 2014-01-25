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

protected:

    float angulation_;  //degrees
    float rotation_;    //degrees
    float dra_;         //degrees  

    OQuaternion  quat_;
};

#endif // TESTCARM_H
