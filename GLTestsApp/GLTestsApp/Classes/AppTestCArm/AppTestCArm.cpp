#include "AppTestCArm.h"


OAppTestCArm::OAppTestCArm()
{
    c_arm_ = new OTestCArm(50.0f);

    data_for_input_.camera = &camera_;
    data_for_input_.c_arm = c_arm_;
}


OAppTestCArm::~OAppTestCArm()
{
    delete c_arm_;
}

OAppTestCArm& OAppTestCArm::GetInstance()
{
    static OAppTestCArm instance;
    return instance;
};

void* OAppTestCArm::GetDataForInput()
{
    return (void*)&data_for_input_;
}

void OAppTestCArm::Init(void* data)
{
    OAppBaseState::Init(data);
}

void OAppTestCArm::Update(void* data)
{
    OAppBaseState::Update(data);

    KeyboardOperation();

    c_arm_->ComputeQuat();

    OQuaternion qrot = c_arm_->Quat();

    OQuaternion q_z_axis(0, 0, 1, 0);
    q_z_axis = qrot * q_z_axis * qrot.Transpose();

    z_axis_ = q_z_axis.V3();

    //z_axis_ = 1.2f * c_arm_->Size() * z_axis_;

    xz_proj_ = OVector3(z_axis_.X(), 0, z_axis_.Z());
    yz_proj_ = OVector3(0, z_axis_.Y(), z_axis_.Z());
}

void OAppTestCArm::Update2(void* data)
{
    OAppBaseState::Update2(data);
}

void OAppTestCArm::Draw()
{
    glUseProgram(0);

    LightOn();
    //DrawAxes(100.0f);
    VDraws->DrawAxes(110.0f, 1.0f);

    glEnable(GL_NORMALIZE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glPushMatrix();
    glScalef(5.0f, 5.0f, 5.0f);
    c_arm_->Draw();
    glPopMatrix();

    glDisableClientState(GL_COLOR_ARRAY);

    glColor4f(1, 1, 1, 1);
    ///draw_axis(OVector3(0, 0, 0), xz_proj_, xz_proj_.Norm());
    glColor4f(1, 1, 1, 1);
    //draw_axis(OVector3(0, 0, 0), yz_proj_, yz_proj_.Norm());

    ///VDraws->DrawBox(OVector3(0, 0, 0), z_axis_);

    //OVector3 vxz = xz_proj_ + (-1.0f) * z_axis_;
    //OVector3 vyz = yz_proj_ + (-1.0f) * z_axis_;

    //draw_axis(z_axis_, vxz, vxz.Norm(), false);
    //draw_axis(z_axis_, vyz, vyz.Norm(), false);

    ///VDraws->DrawHorizontalQuad(35.0f, 100.0f);

    LightOff();

}

void OAppTestCArm::KeyboardOperation()
{
    if(data_for_input_.key_op_type < 0) {
        //no keyboard operation
        return;
    }

    float dt = 3.0f;
    float dt1 = 0.1f;
    float dt2 = 0.2f * dt;
    if(data_for_input_.shift_modif) {
        dt1 *= -1;
        dt2 *= -1;
    }
    OVector3 t;
    switch(data_for_input_.key_op_type) {
        case 0:
            c_arm_->Rotation() -= dt;
            break;
        case 1:
            c_arm_->Rotation() += dt;
            break;
        case 2:
            c_arm_->Angulation() += dt;
            break;
        case 3:
            c_arm_->Angulation() -= dt;
            break;
        case 4:
            c_arm_->Dra() -= dt;
            break;
        case 5:
            c_arm_->Dra() += dt;
            break;

        case 6:
            //x translation - key Z
            t = OVector3 (dt1, 0, 0);
            c_arm_->UpdateLTestObjPos(t);
            break;
        case 7:
            //y translation - key X
            t = OVector3(0, dt1, 0);
            c_arm_->UpdateLTestObjPos(t);
            break;
        case 8:
            //c translation - key C
            t = OVector3(0, 0, dt1);
            c_arm_->UpdateLTestObjPos(t);
            break;
        case 9:
            //x rotation (pitch) - key V
            t = OVector3 (1, 0, 0);
            c_arm_->UpdateLTestObjRot(t, dt2);
            break;
        case 10:
            //y rotation (yaw) - key B
            t = OVector3 (0, 1, 0);
            c_arm_->UpdateLTestObjRot(t, dt2);
            break;
        case 11:
            //z rotation (roll) - key N
            t = OVector3 (0, 0, 1);
            c_arm_->UpdateLTestObjRot(t, dt2);
            break;
    }
}
