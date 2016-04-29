#include "GLTestsApp.h"
#include <QApplication>
#include <QDebug>
//#ifdef __APPLE__
//#include <QSurfaceFormat>
//#endif

#include "AppObjLoader/3d_model.h"
#include "AppObjLoader/obj_loader.h"

//#define APPRESPATH "/home/catalin/Work_Projects/Git_repositories/ObjLoader/Resources/"
//std::string AppResPath = APPRESPATH;

std::string AppResPath = APPRESPATH;

int main(int argc, char *argv[])
{
//#ifdef __APPLE__
//    QSurfaceFormat surfaceFormat;
//    surfaceFormat.setVersion(4, 1);
//    surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
//    //surfaceFormat.setSamples(4);
//    surfaceFormat.setRenderableType(QSurfaceFormat::OpenGL);
//    //surfaceFormat.setSwapBehavior(QSurfaceFormat::TripleBuffer);
//    surfaceFormat.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
//    QSurfaceFormat::setDefaultFormat(surfaceFormat);
//#endif

    QApplication a(argc, argv);
    qDebug() << AppResPath.c_str();
    //a.setStyle("fusion");
	GLTestsApp w;
	w.resize(QSize(1024, 768));
	w.show();
    w.SetBaseState();
	return a.exec();
}
