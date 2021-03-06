#include "GLWidget.h"
#include <QMouseEvent>

#include "AppBaseState.h"
#include "InputMgr.h"
#include <QGLContext>

CGLWidget::CGLWidget(QWidget *parent) : QGLWidget(parent)
{
	this->setMouseTracking(true);
	cx = 0;
	cy = 0;
	
	timerCounter = 0;
	
	hiddenWidget = NULL;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
}


CGLWidget::~CGLWidget()
{
	delete timer;
	if(hiddenWidget) {
		delete hiddenWidget;
		hiddenWidget = NULL;
	}
}

void CGLWidget::OnTimer()
{
	updateGL();
}

void CGLWidget::StartTimer()
{
	timerCounter++;
	if(timerCounter == 1) {
		timer->start(1000.0 / 60.0);
	}
}

void CGLWidget::StopTimer()
{
	timerCounter--;
	if(timerCounter == 0) {
		timer->stop();
		updateGL();
	}
}

QSize CGLWidget::minimumSizeHint() const
{
	return QSize(50, 50);
}

QSize CGLWidget::sizeHint() const
{
	return QSize(800, 800);
}

void CGLWidget::initializeGL()
{
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

 	glEnable(GL_DEPTH_TEST);
 	glDepthFunc(GL_LESS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_TEXTURE_2D);

	glPixelZoom(1.0,1.0);

	QGLFormat format = this->context()->format();
	hiddenWidget = new QGLWidget(/*format,*/ NULL, this);

	StartTimer();
}

void CGLWidget::paintGL()
{
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
        OAppBaseState* state = APPMNGR.GetState();
        if(state == NULL) {
            return;
        }

        state->Update();
        state->Draw();

	//this->renderText(0, 0, 0, "Test text");
}

void CGLWidget::resizeGL(int width, int height)
{
	cx = width;
	cy = height;

	glViewport( 0, 0, cx, cy); 

	//3d camera
        OAppBaseState* state = APPMNGR.GetState();
        if(state == NULL) {
            return;
        }
        OGL3DCamera* camera = &(state->GetCamera());
	OVector4 persp = camera->GetPerspective();
	persp[3] = (cx + 0.0f) / (cy + 0.0f);
	camera->SetPerspective(persp);
}

void CGLWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		QPoint point = event->pos();
		
		int y = (-(cy + 0.0f) / (cy- 1.0f) * (point.y() + 0.0f) + (cy + 0.0f) / 2.0f);
		int x = ((cx + 0.0f) / (cx- 1.0f) * (point.x() + 0.0f) - (cx + 0.0f) / 2.0f);
		point.setY(y);
		point.setX(x);

		INPUTMGR->OnLButtonDown(point);
	}

	if(event->button() == Qt::RightButton) {
		StartTimer();
	}
}

void CGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint point = event->pos();

	int y = (-(cy + 0.0f) / (cy- 1.0f) * (point.y() + 0.0f) + (cy + 0.0f) / 2.0f);
	int x = ((cx + 0.0f) / (cx- 1.0f) * (point.x() + 0.0f) - (cx + 0.0f) / 2.0f);
	point.setY(y);
	point.setX(x);

	INPUTMGR->OnMouseMove(point);
	updateGL();
}

void CGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		QPoint point = event->pos();

		int y = (-(cy + 0.0f) / (cy- 1.0f) * (point.y() + 0.0f) + (cy + 0.0f) / 2.0f);
		int x = ((cx + 0.0f) / (cx- 1.0f) * (point.x() + 0.0f) - (cx + 0.0f) / 2.0f);
		point.setY(y);
		point.setX(x);

		INPUTMGR->OnLButtonUp(point);
	}
}

void CGLWidget::wheelEvent(QWheelEvent *event)
{
	QPoint point = event->pos();

	int y = (-(cy + 0.0f) / (cy- 1.0f) * (point.y() + 0.0f) + (cy + 0.0f) / 2.0f);
	int x = ((cx + 0.0f) / (cx- 1.0f) * (point.x() + 0.0f) - (cx + 0.0f) / 2.0f);
	point.setY(y);
	point.setX(x);

	int delta = event->delta();

	INPUTMGR->OnMouseWheel( delta, point);

	updateGL();
}

void CGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    INPUTMGR->OnKeyRelease(event->key());
}
