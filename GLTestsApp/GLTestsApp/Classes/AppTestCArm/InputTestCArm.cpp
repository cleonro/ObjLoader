//test - search another solution
#include <QApplication>
//

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

    (void)key;
    ((OAppTestCArm::tDataForInput*)data)->key_op_type = -1;
}

void OInputTestCArm::OnKeyPress(int key, void* data)
{
    if(!data) {
        return;
    }

    ((OAppTestCArm::tDataForInput*)data)->key_op_type = key;
    if(qApp->keyboardModifiers() & Qt::ShiftModifier) {
        ((OAppTestCArm::tDataForInput*)data)->shift_modif = true;
    } else {
        ((OAppTestCArm::tDataForInput*)data)->shift_modif = false;
    }
}
