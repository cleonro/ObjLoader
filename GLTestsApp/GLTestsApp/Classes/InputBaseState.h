#pragma once

#include <QPoint>

//input states are created and managed by Input Manager, so their constructors and destructors are protected

class OInputMgr;

class OInputBaseState
{

public:
	friend class OInputMgr;
	virtual void OnLeftClick(QPoint, void* data = NULL);
	virtual void OnMouseDrag(QPoint, QPoint, void* data = NULL);
	virtual void OnMouseMove(QPoint, void* data = NULL);
// 	virtual void OnRightClick(QPoint, void* data = NULL);
 	virtual void OnMouseWheel(short, void* data = NULL);

	virtual void OnLeftDown(QPoint, void* data = NULL);
	//virtual void OnRightDown(QPoint, void* data = NULL);
    virtual void OnKeyRelease(int key, void* data = NULL);
    virtual void OnKeyPress(int key, void* data = NULL);

protected:
	OInputBaseState(void);
    virtual ~OInputBaseState(void);

};

/*
class InputWheelState : public InputBaseState
{
protected:
	friend class InputMgr;
	InputWheelState();
	~InputWheelState();
	unsigned int id_; // shows which control is used;
public:
	virtual void OnMouseDrag(CPoint, CPoint);
};
*/
