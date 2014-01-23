#ifndef VRPMAPEDITORQT_H
#define VRPMAPEDITORQT_H

#include <QtGui/QMainWindow>
#include "ui_GLTestsApp.h"
#include <QVector>
#include "AppTestShader/ShaderWidget.h"
#include "AppTestCArm/carmwidget.h"

class GLTestsApp : public QMainWindow
{
	Q_OBJECT

public:
	GLTestsApp(QWidget *parent = 0, Qt::WFlags flags = 0);
	~GLTestsApp();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

protected slots:
        void OnViewShaderEditor();
        void OnViewCArmWidget();
        void OnStatesBaseState();
        void OnStatesTestShader();
        void OnStatesTestCArm();

protected:
	void closeEvent(QCloseEvent * event);

    void keyReleaseEvent(QKeyEvent *event);

        QGLWidget* GLWidget();

private:
        Ui::GLTestsAppClass	ui_;
        QActionGroup*           action_group_;
        OShaderWidget		shader_widget_;
        CarmWidget          carm_widget_;
};

#endif // VRPMAPEDITORQT_H
