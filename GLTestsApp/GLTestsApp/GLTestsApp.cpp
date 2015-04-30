#include "GLTestsApp.h"
#include "AppBaseState.h"
#include "InputMgr.h"

#include <QStyleFactory>

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

    qApp->setStyle("Fusion");
    setMenuStyles();

    QFile styleSheetFile(":/GLTestsApp/darkorange.stylesheet");
    styleSheetFile.open(QIODevice::ReadOnly);
    QString styleSheetString(styleSheetFile.readAll());
    styleSheetFile.close();
    qApp->setStyleSheet(styleSheetString);
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

void GLTestsApp::closeEvent(QCloseEvent * /*event*/)
{
	QApplication::quit();
}

void GLTestsApp::OnViewShaderEditor()
{
        shader_widget_.show();
}

void GLTestsApp::OnStatesBaseState()
{
    QOpenGLWidget* gl_widget = this->GLWidget();
    if(APPMNGR.GetStateId() == OAppManager::APP_BASE_STATE || gl_widget == NULL) {
       return;
    }
    ui_.actionShader_Editor->setVisible(false);
    QSize sz = gl_widget->size();
    float aspect = sz.width() * 1.0f / sz.height();

    APPMNGR.ChangeState(OAppManager::APP_BASE_STATE);
    INPUTMGR->ChangeState(INPUT_BASE);

    APPMNGR.GetState()->Init(&aspect);
    gl_widget->repaint();
}

void GLTestsApp::OnStatesTestShader()
{
    QOpenGLWidget* gl_widget = this->GLWidget();
    if(APPMNGR.GetStateId() == OAppManager::APP_TEST_SHADER || gl_widget == NULL) {
       return;
    }
    ui_.actionShader_Editor->setVisible(true);
    QSize sz = gl_widget->size();
    float aspect = sz.width() * 1.0f / sz.height();

    APPMNGR.ChangeState(OAppManager::APP_TEST_SHADER);
    INPUTMGR->ChangeState(INPUT_BASE);

    APPMNGR.GetState()->Init(&aspect);
    gl_widget->update();
}

void GLTestsApp::OnStatesTestCArm()
{
    QOpenGLWidget* gl_widget = this->GLWidget();
    if(APPMNGR.GetStateId() == OAppManager::APP_TEST_C_ARM || gl_widget == NULL) {
       return;
    }
     ui_.actionShader_Editor->setVisible(false);
     QSize sz = gl_widget->size();
     float aspect = sz.width() * 1.0f / sz.height();

     APPMNGR.ChangeState(OAppManager::APP_TEST_C_ARM);
     INPUTMGR->ChangeState(INPUT_TEST_C_ARM);

     APPMNGR.GetState()->Init(&aspect);
     gl_widget->update();
}

QOpenGLWidget* GLTestsApp::GLWidget()
{
    return dynamic_cast<QOpenGLWidget*>(this->centralWidget());
}

void GLTestsApp::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) {
        return;
    }
    INPUTMGR->OnKeyRelease(event->key());
}

void GLTestsApp::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) {
        return;
    }
    INPUTMGR->OnKeyPress(event->key());
}

void GLTestsApp::setMenuStyles()
{
    QString currentStyle = qApp->style()->objectName();
    QStringList styles = QStyleFactory::keys();
    QMenu* menuStyles= ui_.menuStyles;
    QActionGroup* styleActions = new QActionGroup(this);
    foreach (QString styleString, styles) {
        QAction* a = new QAction(styleString, this);
        a->setCheckable(true);
        styles_map_[a] = styleString;
        if(styleString.toLower() == currentStyle.toLower()) {
            a->setChecked(true);
        }
        styleActions->addAction(a);
        menuStyles->addAction(a);
        Q_ASSERT(connect(a, &QAction::toggled, this, &GLTestsApp::onActionToggled));
    }
}

void GLTestsApp::onActionToggled(bool checked)
{
    QObject* sender = this->sender();
    if(sender == nullptr) {
        return;
    }

    if(checked) {
        QString styleString = styles_map_[sender];
        if(!styleString.isEmpty()) {
            qApp->setStyle(styleString);
        }
    }
}

void GLTestsApp::SetBaseState()
{
    ui_.actionTest_CArm->setChecked(true);
    OnStatesTestCArm();
}
