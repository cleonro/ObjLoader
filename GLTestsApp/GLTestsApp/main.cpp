#include "GLTestsApp.h"
#include <QApplication>
#include <QDebug>

#include "AppObjLoader/3d_model.h"
#include "AppObjLoader/obj_loader.h"

//#define APPRESPATH "/home/catalin/Work_Projects/Git_repositories/ObjLoader/Resources/"
//std::string AppResPath = APPRESPATH;

std::string AppResPath = APPRESPATH;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << AppResPath.c_str();
    //a.setStyle("fusion");
	GLTestsApp w;
	w.resize(QSize(1024, 768));
	w.show();
	
	return a.exec();
}
