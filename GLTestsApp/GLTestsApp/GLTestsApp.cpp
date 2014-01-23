#include "GLTestsApp.h"
#include "AppBaseState.h"
#include "InputMgr.h"

GLTestsApp::GLTestsApp(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	this->setBaseSize(QSize(1024, 768));
        ui_.setupUi(this);
	
        connect(ui_.actionShader_Editor, SIGNAL(triggered(bool)), this, SLOT(OnViewShaderEditor()));
        ui_.actionShader_Editor->setVisible(false);

	this->setWindowTitle("GLTestsApp");

        action_group_ = new QActionGroup(this);
        action_group_->addAction(ui_.actionBase_State);
        action_group_->addAction(ui_.actionTest_Shader);
        action_group_->addAction(ui_.actionTest_CArm);

        connect(ui_.actionBase_State, SIGNAL(triggered()), this, SLOT(OnStatesBaseState()));
        connect(ui_.actionTest_Shader, SIGNAL(triggered()), this, SLOT(OnStatesTestShader()));
        connect(ui_.actionTest_CArm, SIGNAL(triggered()), this, SLOT(OnStatesTestCArm()));
}

GLTestsApp::~GLTestsApp()
{
	
}

QSize GLTestsApp::minimumSizeHint() const
{
	return QSize(1024, 768);
}

QSize GLTestsApp::sizeHint() const
{
	return QSize(1024, 768);
}

void GLTestsApp::closeEvent(QCloseEvent * event)
{
	QApplication::quit();
}

void GLTestsApp::OnViewShaderEditor()
{
        shader_widget_.show();
}

void GLTestsApp::OnStatesBaseState()
{
    QGLWidget* gl_widget = this->GLWidget();
    if(APPMNGR.GetStateId() == OAppManager::APP_BASE_STATE || gl_widget == NULL) {
       return;
    }
    ui_.actionShader_Editor->setVisible(false);
    QSize sz = gl_widget->size();
    float aspect = sz.width() * 1.0f / sz.height();

    APPMNGR.ChangeState(OAppManager::APP_BASE_STATE);
    INPUTMGR->ChangeState(INPUT_BASE);

    APPMNGR.GetState()->Init(&aspect);
    ((CGLWidget*)gl_widget)->updateGL();
}

void GLTestsApp::OnStatesTestShader()
{
    QGLWidget* gl_widget = this->GLWidget();
    if(APPMNGR.GetStateId() == OAppManager::APP_TEST_SHADER || gl_widget == NULL) {
       return;
    }
    ui_.actionShader_Editor->setVisible(true);
    QSize sz = gl_widget->size();
    float aspect = sz.width() * 1.0f / sz.height();

    APPMNGR.ChangeState(OAppManager::APP_TEST_SHADER);
    INPUTMGR->ChangeState(INPUT_BASE);

    APPMNGR.GetState()->Init(&aspect);
    ((CGLWidget*)gl_widget)->updateGL();
}

void GLTestsApp::OnStatesTestCArm()
{
    QGLWidget* gl_widget = this->GLWidget();
    if(APPMNGR.GetStateId() == OAppManager::APP_TEST_C_ARM || gl_widget == NULL) {
       return;
    }
     ui_.actionShader_Editor->setVisible(false);
     QSize sz = gl_widget->size();
     float aspect = sz.width() * 1.0f / sz.height();

     APPMNGR.ChangeState(OAppManager::APP_TEST_C_ARM);
     INPUTMGR->ChangeState(INPUT_TEST_C_ARM);

     APPMNGR.GetState()->Init(&aspect);
     ((CGLWidget*)gl_widget)->updateGL();
}

QGLWidget* GLTestsApp::GLWidget()
{
    return (QGLWidget*)this->centralWidget();
}

void GLTestsApp::keyReleaseEvent(QKeyEvent *event)
{
    INPUTMGR->OnKeyRelease(event->key());
}
