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

C_3D_RESOURCE_MANAGER* resource_manager = new C_3D_RESOURCE_MANAGER;
C_OBJ_LOADER* loader = new C_OBJ_LOADER;
C_3D_MODEL* avatar = NULL;
C_AVATAR_OBJ* clone_avatar = NULL;
//

OTestCArm::OTestCArm(float size)
{
    inner_ray_ = size;
    outer_ray_ = 1.8f * inner_ray_;

    inner_ring_ = new OSpecialMesh(50, 50, inner_ray_, inner_ray_ * 0.025f);
    outer_ring_ = new OSpecialMesh(50, 50, outer_ray_, outer_ray_ * 0.025f);
    float cyl_sz = outer_ray_ - inner_ray_;
    rod_ = new OSpecialMesh(50, 50, cyl_sz, cyl_sz * 0.05f);

    angulation_ = 0.0f;
    rotation_ = 0.0f;
    dra_ = 0.0f;
    quat_ = OQuaternion(0, 0, 0, 1);

    //test-remove
    string name = "avatar";
    //avatar = loader->parse_obj_file("d:\\cube.obj", resource_manager, name);
    //avatar = loader->parse_obj_file("d:\\PmiAvatar.obj", resource_manager, name);
    //avatar = loader->parse_obj_file("d:\\uh60.obj", resource_manager, name);
    //avatar = loader->parse_obj_file("d:\\Rubik.obj", resource_manager, name);
    //avatar = loader->parse_obj_file("d:\\av_table.obj", resource_manager, name);
    //avatar = loader->parse_obj_file("d:\\av_carm.obj", resource_manager, name);
    //avatar = loader->parse_obj_file("d:\\2cubes.obj", resource_manager, name);
    //avatar = loader->parse_obj_file("d:\\ncube.obj", resource_manager, name);
    //avatar = loader->parse_obj_file("d:\\NPmiAvatar.obj", resource_manager, name);
    //avatar = loader->parse_obj_file("d:\\PivotPmiAvatar.obj", resource_manager, name);
    //avatar = loader->parse_obj_file("d:\\NPivotPmiAvatar.obj", resource_manager, name);
    avatar = loader->parse_obj_file("d:/sdr.obj", resource_manager, name);
    printf("obj file loaded");

    clone_avatar = new C_AVATAR_OBJ;
    clone_avatar->clone(avatar);
    delete avatar;
    avatar = NULL;
    clone_avatar->init();
    //
}

OTestCArm::~OTestCArm()
{
    delete inner_ring_;
    delete outer_ring_;
    delete rod_;

    //test-remove
    delete clone_avatar;
    delete loader;
    delete resource_manager;
    //
}

void OTestCArm::Draw()
{
   OQuaternion q(quat_.X(), quat_.Y(), quat_.Z(), quat_.W());
   clone_avatar->matrix() = q.ToMatrix();
   clone_avatar->draw();
   return;

   glPushMatrix();
   outer_ring_->DrawMesh(OSpecialMesh::THORUS);

   //glRotatef(angulation_, 0.0f, 1.0f, 0.0f);
   //glRotatef(rotation_, 1.0f, 0.0f, 0.0f);
   //glRotatef(dra_, 0, 0, 1);

   ////ComputeQuat();
   OMatrix4 orient = quat_.ToMatrix();
   glMultMatrixf(orient.GetSafeM());

   DrawAxes(2.4f * inner_ray_);

   glPopMatrix();
   glPushMatrix();
   float temp_dra = dra_;
   dra_ = 0.0f;
   ComputeQuat();
   orient = quat_.ToMatrix();
   glMultMatrixf(orient.GetSafeM());

  // glRotatef(angulation_, 0, 1, 0);
  // glRotatef(rotation_, 1, 0, 0);
  // glRotatef(dra_, 0, 0, 1);

   inner_ring_->DrawMesh(OSpecialMesh::THORUS);
   glTranslatef(-inner_ray_, 0.0f, 0.0f);
   rod_->DrawMesh(OSpecialMesh::CYLINDER);
   dra_ = temp_dra;
   glPopMatrix();

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
