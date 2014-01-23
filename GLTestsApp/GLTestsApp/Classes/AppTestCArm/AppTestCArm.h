#pragma once

#include "Utils/GLee.h"
#if WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include "AppBaseState.h"

#include "TestCarm.h"

class OAppTestCArm : public OAppBaseState
{
    friend class OAppManager;

public:

    struct tDataForInput
    {
        OGL3DCamera*    camera;
        OTestCArm*      c_arm;
    };

    virtual void Init(void* data);
    virtual void Update(void* data = NULL);
    virtual void Update2(void* data = NULL);
    virtual void Draw();

    virtual void* GetDataForInput();

    void* CArm() {return c_arm_;}

protected:
    static OAppTestCArm& GetInstance();

    OAppTestCArm();
    ~OAppTestCArm();

    OTestCArm*      c_arm_;
    tDataForInput   data_for_input_;

    OVector3        z_axis_;
    OVector3        xz_proj_;//secondary angle
    OVector3        yz_proj_;//primary angle
};
