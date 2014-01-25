#include "InputTestCArm.h"
#include "AppTestCArm.h"
#include "GLCamera.h"

OInputTestCArm::OInputTestCArm()
{

}

OInputTestCArm::~OInputTestCArm()
{

}

void OInputTestCArm::OnLeftClick(QPoint p, void* data)
{
    (void)p;
    if(!data) {
        return;
    }
}

void OInputTestCArm::OnMouseDrag(QPoint p, QPoint p_start, void* data)
{
    if(!data) {
        return;
    }

    OGL3DCamera* camera = ((OAppTestCArm::tDataForInput*)data)->camera;

    static QPoint point = p_start;
    if(fabs(p.x() - p_start.x() - 0.0f) < 2 && fabs(p.y() - p_start.y() - 0.0f) < 2) {
        point = p_start;
    }

    camera->Pitch(-(p.y() - point.y() - 0.0f));
    camera->Yaw(-(p.x() - point.x() - 0.0f));

    point = p;
}

void OInputTestCArm::OnMouseMove(QPoint p, void* data)
{
    (void)p;
    if(!data) {
        return;
    }
}

void OInputTestCArm::OnMouseWheel(short zDelta, void* data)
{
    if(!data) {
        return;
    }

    OGL3DCamera* camera = ((OAppTestCArm::tDataForInput*)data)->camera;

    const float dist = 8.0f;

    if(zDelta > 0) {
        camera->Translate(dist);

    } else {
        camera->Translate(-dist);

    }
}


void OInputTestCArm::OnLeftDown(QPoint, void* /*data*/)
{

}

void OInputTestCArm::OnKeyRelease(int key, void *data)
{
    if(!data) {
        return;
    }

    float dt = 3.0f;

    OTestCArm* c_arm = ((OAppTestCArm::tDataForInput*)data)->c_arm;
    switch(key) {
        case 0:
            c_arm->Rotation() -= dt;
            break;
        case 1:
            c_arm->Rotation() += dt;
            break;
        case 2:
            c_arm->Angulation() += dt;
            break;
        case 3:
            c_arm->Angulation() -= dt;
            break;
        case 4:
            c_arm->Dra() -= dt;
            break;
        case 5:
            c_arm->Dra() += dt;
            break;
    }
}

void OInputTestCArm::OnKeyPress(int key, void* data)
{

}
