#include "ccentralwidget.h"

CCentralWidget::CCentralWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
		
	ui.glwidget->mParent = this;
}

CCentralWidget::~CCentralWidget()
{

}

void CCentralWidget::UpClicked()
{
	
}

void CCentralWidget::DownClicked()
{
	
}

void CCentralWidget::LeftClicked()
{
	
}

void CCentralWidget::RightClicked()
{
	
}

void CCentralWidget::StartTimer(bool show)
{
	ui.glwidget->StartTimer(show);
}

void CCentralWidget::StopTimer()
{
	ui.glwidget->StopTimer();
}