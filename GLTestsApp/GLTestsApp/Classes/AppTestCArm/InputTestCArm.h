#ifndef INPUTTESTCARM_H
#define INPUTTESTCARM_H

#include "InputBaseState.h"

class OInputTestCArm : public OInputBaseState
{
    friend class OInputMgr;

    virtual void OnLeftClick(QPoint, void* data = NULL);
    virtual void OnMouseDrag(QPoint, QPoint, void* data = NULL);
    virtual void OnMouseMove(QPoint, void* data = NULL);
    virtual void OnMouseWheel(short, void* data = NULL);

    virtual void OnLeftDown(QPoint, void* data = NULL);

    virtual void OnKeyRelease(int key, void* data = NULL);

protected:
    OInputTestCArm();
    ~OInputTestCArm();
};

#endif // INPUTTESTCARM_H
