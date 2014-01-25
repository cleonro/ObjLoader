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
    //glScalef(5.0f, 5.0f, 5.0f);
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
