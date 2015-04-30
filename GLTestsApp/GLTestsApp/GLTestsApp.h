#ifndef VRPMAPEDITORQT_H
#define VRPMAPEDITORQT_H

#include <QMainWindow>
#include "ui_GLTestsApp.h"
#include <QVector>
#include <QMap>
#include "AppTestShader/ShaderWidget.h"

class GLTestsApp : public QMainWindow
{
	Q_OBJECT

public:
    GLTestsApp(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~GLTestsApp();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

    void SetBaseState();

protected slots:
        void OnViewShaderEditor();
        void OnStatesBaseState();
        void OnStatesTestShader();
        void OnStatesTestCArm();

        void onActionToggled(bool checked);

protected:
	void closeEvent(QCloseEvent * event);

    void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);

    QOpenGLWidget *GLWidget();

private:
    void setMenuStyles();

private:
        Ui::GLTestsAppClass	ui_;
        QActionGroup*           action_group_;
        OShaderWidget		shader_widget_;

        QMap<QObject*, QString> styles_map_;
};

#endif // VRPMAPEDITORQT_H
