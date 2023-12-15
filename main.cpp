#include "stdafx.h"
#include "Visualizer.h"
// #include "Renderer.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    //QCoreApplication::setApplicationName("Qt QOpenGLWidget Stereoscopic Rendering Example");
    //QCoreApplication::setOrganizationName("QtProject");
    //QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    //QSurfaceFormat format;
    //format.setDepthBufferSize(24);
    //format.setStencilBufferSize(8);

    //format.setStereo(true);

    //QSurfaceFormat::setDefaultFormat(format);

    Visualizer mw;
    mw.show();
    return a.exec();
}
