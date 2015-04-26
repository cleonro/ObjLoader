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

        int key_op_type;   //value "-1" stops an operation controlled from keyboard
                           //positive value starts an operation controlled from keyboard
        bool shift_modif;  //Shift key is pressed

        tDataForInput()
        {
            camera = NULL;
            c_arm = NULL;
            key_op_type = -1;
            shift_modif = false;
        }
    };

    virtual void Init(void* data);
    virtual void Update(void* data = NULL);
    virtual void Update2(void* data = NULL);
    virtual void Draw();

    virtual void* GetDataForInput();

protected:
    static OAppTestCArm& GetInstance();

    OAppTestCArm();
    ~OAppTestCArm();

    void TestObjectKeyboardOperation();
    void TestObjectDrawKeyboardOperation();

    OTestCArm*      c_arm_;
    tDataForInput   data_for_input_;

    OVector3        z_axis_;
    OVector3        xz_proj_;//secondary angle
    OVector3        yz_proj_;//primary angle

    OVector3        keyboard_op_startp_;
    OVector3        keyboard_op_axis_;
    bool            keyboard_op_started_;
};
