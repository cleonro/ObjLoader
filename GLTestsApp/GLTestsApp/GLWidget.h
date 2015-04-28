#pragma once

#include <QGLWidget>
#include <QTimer>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class CGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	CGLWidget(QWidget *parent = 0);
	~CGLWidget();

	//?
	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void StartTimer();
	void StopTimer();
		
    QOpenGLWidget* hiddenWidget;
			
protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

	void mousePressEvent(QMouseEvent *event);
 	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
	
	int cx;//size x
	int cy;//size y
	QTimer* timer;
	int timerCounter;
	
protected slots:
	void OnTimer();

};

