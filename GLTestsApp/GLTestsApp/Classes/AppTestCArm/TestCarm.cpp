#include "TestCarm.h"
#if WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include "AppBaseState.h"

//test-remove
#include "AppObjLoader/obj_loader.h"
#include "AppObjLoader/3d_resource_manager.h"
#include "AppObjLoader/3d_model.h"
#include "AppObjLoader/avatar_obj.h"
#include "AppObjLoader/3d_dynamic_object.h"

C_3D_RESOURCE_MANAGER* resource_manager = new C_3D_RESOURCE_MANAGER;
C_OBJ_LOADER* loader = new C_OBJ_LOADER;
C_3D_MODEL* avatar = NULL;
C_AVATAR_OBJ* clone_avatar = NULL;

//test object data
C_3D_MODEL* test_object = NULL;
C_3D_DYNAMIC_OBJECT* dynamic_object = NULL;
//

extern string AppResPath;

OTestCArm::OTestCArm(float size)
{
    (void)size;

    angulation_ = 0.0f;
    rotation_ = 0.0f;
    dra_ = 0.0f;
    quat_ = OQuaternion(0, 0, 0, 1);

    test_obj_pos_ = OVector3(0, 0, 0);
    test_obj_rot_ = OQuaternion(0, 0, 0, 1);

    std::string name = "avatar";
    //"cube.obj"
    //"PmiAvatar.obj"
    //"uh60.obj"
    //"Rubik.obj"
    //"av_table.obj"
    //"av_carm.obj"
    //"2cubes.obj"
    //"ncube.obj"
    //"NPmiAvatar.obj"
    //"PivotPmiAvatar.obj"
    //"NPivotPmiAvatar.obj"
    //"sdr.obj"

    //avatar
    std::string path = AppResPath + "NPivotPmiAvatar.obj";
    avatar = loader->parse_obj_file(path.c_str(), resource_manager, name);
    printf("obj file loaded");

    //test object
    path = AppResPath + "sdr.obj";
    test_object =  loader->parse_obj_file(path.c_str(), resource_manager, "test_object");
    dynamic_object = new C_3D_DYNAMIC_OBJECT;
    dynamic_object->clone(test_object);
    delete test_object;
    test_object = NULL;

    clone_avatar = new C_AVATAR_OBJ;
    clone_avatar->clone(avatar);
    delete avatar;
    avatar = NULL;
    clone_avatar->init();
    //
}

OTestCArm::~OTestCArm()
{
    delete clone_avatar;
    delete dynamic_object;
    delete loader;
    delete resource_manager;
}

void OTestCArm::Draw()
{
   clone_avatar->matrix() = quat_.ToMatrix();
   dynamic_object->Position() = test_obj_pos_;
   dynamic_object->Rotation() = test_obj_rot_.ToMatrix();

   //avatar
   glColor4f(0.1, 0.3, 0.7, 1.0);
   clone_avatar->draw();

   //test-object
   glColor4f(0.7, 0.3, 0.1, 1.0);
   dynamic_object->draw(true);

   return;
}

float& OTestCArm::Angulation()
{
    return angulation_;
}

float& OTestCArm::Rotation()
{
    return rotation_;
}

float& OTestCArm::Dra()
{
    return dra_;
}

void OTestCArm::ComputeQuat()
{
    float ang = deg2rad(angulation_);
    float rot = deg2rad(rotation_);
    float dra = deg2rad(dra_);

    float hcos_ang = cosf(0.5f * ang);
    float hsin_ang = sinf(0.5f * ang);

    float hcos_rot = cosf(0.5f * rot);
    float hsin_rot = sinf(0.5f * rot);

    float hcos_dra = cosf(0.5f * dra);
    float hsin_dra = sinf(0.5f * dra);

    OQuaternion q_rot = OQuaternion(hsin_rot, 0, 0, hcos_rot);
    OQuaternion q_ang = OQuaternion(0, hsin_ang, 0, hcos_ang);
    OQuaternion q_dra = OQuaternion(0, 0, hsin_dra, hcos_dra);

    //quat_ = q_ang * q_rot * q_dra;
    quat_ = q_rot * q_ang * q_dra;
}

void OTestCArm::UpdateLTestObjPos(const OVector3 &translation)
{
    OQuaternion qtr(translation, 1);
    qtr = test_obj_rot_ * qtr * test_obj_rot_.Transpose();
    OVector3 global_translation = qtr.V3();
    test_obj_pos_ = test_obj_pos_ + global_translation;
}

void OTestCArm::UpdateLTestObjRot(const OVector3 &axis, const float &angle)
{
    float ang_rad = deg2rad(angle);
    float hcos = cosf(0.5f * ang_rad);
    float hsin = sinf(0.5f * ang_rad);
    OQuaternion lq(hsin * axis, hcos);

    test_obj_rot_ = test_obj_rot_ * lq;
}
