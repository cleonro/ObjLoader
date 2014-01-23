#include "InputMgr.h"

#include "AppBaseState.h"
#include "AppTestCArm/InputTestCArm.h"

OInputMgr::OInputMgr()
{
	//state_ = NULL;
	state_ = new OInputBaseState;

	//auxiliary information, default values;
	drag_ = false;
}

OInputMgr::~OInputMgr()
{
	if(state_) {
		delete state_;
	}
}

OInputMgr* OInputMgr::GetInstance()
{
	static OInputMgr instance;
	return &instance;
}

void OInputMgr::ChangeState(eInputStates new_type)
{
	if(state_) {
		delete state_;
	}
	state_type_ = new_type;
	
	switch(state_type_) {
		case INPUT_BASE:
				state_ = new OInputBaseState;
			break;
        case INPUT_TEST_C_ARM:
                state_ = new OInputTestCArm;
            break;

		default:
			break;
	}
}

void OInputMgr::OnLButtonDown(QPoint point)
{
	drag_ = true;
	pnt_ = point;
	state_->OnLeftDown(point, APPMNGR.GetDataForInput());
}

void OInputMgr::OnLButtonUp(QPoint point)
{
	drag_ = false;
	state_->OnLeftClick(point);
}

void OInputMgr::OnMouseMove(QPoint point)
{
	if(drag_) {
		state_->OnMouseDrag(point, pnt_, APPMNGR.GetDataForInput());
	} else {
		state_->OnMouseMove(point, APPMNGR.GetDataForInput());
	}
}

void OInputMgr::OnMouseWheel(short zDelta, QPoint pt)
{
	state_->OnMouseWheel(zDelta, APPMNGR.GetDataForInput());
}

// void OInputMgr::OnRButtonUp(UINT nFlags, CPoint point)
// {
// 	state_->OnRightClick(point, APPMNGR.GetDataForInput());
// }
// 
// void OInputMgr::OnRButtonDown(UINT nFlags, CPoint point)
// {
// 	state_->OnRightDown(point, APPMNGR.GetDataForInput());
// }

void OInputMgr::OnKeyRelease(int key)
{
    void* data = APPMNGR.GetDataForInput();
    if(key == Qt::Key_Left) {
        state_->OnKeyRelease(0, data);
    }
    if(key == Qt::Key_Right) {
        state_->OnKeyRelease(1, data);
    }
    if(key == Qt::Key_Up) {
        state_->OnKeyRelease(2, data);
    }
    if(key == Qt::Key_Down) {
        state_->OnKeyRelease(3, data);
    }
    if(key == Qt::Key_A) {
        state_->OnKeyRelease(4, data);
    }
    if(key == Qt::Key_S) {
        state_->OnKeyRelease(5, data);
    }
}
