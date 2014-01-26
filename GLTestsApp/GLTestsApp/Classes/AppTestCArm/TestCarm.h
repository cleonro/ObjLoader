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

    //computes c-arm orientation from angulation, rotation, dra
    void ComputeQuat();

    //update test object position
    //translation is in object local coordinates
    void UpdateLTestObjPos(const OVector3& translation);

    //update test object orientation
    //rotation axis is in object local coordinates
    void UpdateLTestObjRot(const OVector3& axis, const float& angle);

    OQuaternion Quat() {return quat_;}

protected:

    float angulation_;  //degrees
    float rotation_;    //degrees
    float dra_;         //degrees  

    OQuaternion  quat_; //c-arm orientation

    //test object data
    OVector3 test_obj_pos_;     //global position
    OQuaternion test_obj_rot_;  //global orientation
};

#endif // TESTCARM_H
