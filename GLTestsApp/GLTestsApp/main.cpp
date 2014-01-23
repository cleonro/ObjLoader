#include "GLTestsApp.h"
#include <QApplication>

#include "AppObjLoader/3d_model.h"
#include "AppObjLoader/obj_loader.h"

int main(int argc, char *argv[])
{
    //test obj_loader
    //C_OBJ_LOADER* loader = new C_OBJ_LOADER;
    //loader->parse_obj_file("d:\\temp\\GLObjViewer\\Content\\Models\\cube.obj");
    //delete loader;
    //

    QApplication a(argc, argv);

	GLTestsApp w;
	
	w.resize(QSize(1024, 768));

    //w.setWindowOpacity(0.5);

	w.show();
	
	return a.exec();
}
