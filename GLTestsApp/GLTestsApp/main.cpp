#include "GLTestsApp.h"
#include <QApplication>

#include "AppObjLoader/3d_model.h"
#include "AppObjLoader/obj_loader.h"

#define APPRESPATH "d:/Organized_Work_2014[gitr]/QtProjects/ObjLoader/Resources/"

std::string AppResPath = APPRESPATH;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	GLTestsApp w;
	w.resize(QSize(1024, 768));
	w.show();
	
	return a.exec();
}
